#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <vector>
#include <chrono>

using namespace std;

class TaskScheduler {
private:
    using Task = pair<time_t, function<void()>>;
    struct Compare {
        bool operator()(const Task& lhs, const Task& rhs) {
            return lhs.first > rhs.first;
        }
    };
    priority_queue<Task, std::vector<Task>, Compare> Tasks;
    mutex M;
    condition_variable Cv;
    thread Worker;
    atomic<bool> Stop;

public:
    TaskScheduler() : Stop(false) {
        Worker = thread(&TaskScheduler::Run, this);
    }

    ~TaskScheduler() {
        Stop = true;
        Cv.notify_one();
        Worker.join();
    }

    void Add(function<void()> task, time_t timestamp) {
        lock_guard<mutex> lock(M);
        Tasks.emplace(timestamp, task);
        Cv.notify_one();
    }

private:
    void Run() {
        unique_lock<mutex> lock(M);
        while (true) {
            Task currentTask;
            if (Tasks.empty()) {
                Cv.wait(lock);
            } else {
                Cv.wait_for(lock, chrono::seconds(Tasks.top().first - time(nullptr)));
            }
            if (Stop) {
                return;
            }
            currentTask = Tasks.top();
            auto now = time(nullptr);
            if (currentTask.first <= now) {
                thread t(currentTask.second);
                t.detach();
                Tasks.pop();
            }
        }
    }
};