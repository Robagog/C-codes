#include <iostream>
#include <vector>

using namespace std;

class THeap {
private:
    vector<int> Arr = {};  

public:
    void Insert(int value) {
        Arr.push_back(value);
        int i = Arr.size() - 1;
        while (i > 0 && Arr[(i - 1) / 2] < Arr[i]) {
            swap(Arr[i], Arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void Remove() {
        if (Arr.empty()) {
            return;
        }
        swap(Arr[0], Arr[Arr.size() - 1]);
        Arr.pop_back();
        Heapify(Arr.size(), 0);
    }

    int GetMax() const {
        if (Arr.empty()) {
            return -1;
        } else {
            return Arr[0];
        }
    }

private:
    void Heapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && Arr[left] > Arr[largest])
            largest = left;

        if (right < n && Arr[right] > Arr[largest])
            largest = right;

        if (largest != i) {
            swap(Arr[i], Arr[largest]);
            Heapify(n, largest);
        }
    }
};

void HeapSort(vector<int>& arr) {
    THeap heap;
    for (size_t i = 0; i < arr.size(); i++) {
        heap.Insert(arr[i]);
    }
    for (int i = arr.size() - 1; i >= 0; i--) {
        arr[i] = heap.GetMax();
        heap.Remove();
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    HeapSort(arr);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}