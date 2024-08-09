#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;


class TGraph {
private:
    vector<std::vector<int>> AdjacencyList;
    vector<int> NLower;

public:
    TGraph(int numSoldiers) 
        : AdjacencyList(numSoldiers)
        , NLower(numSoldiers, 0)
    {}

    void AddEdge(int source, int destination) {
        AdjacencyList[source].push_back(destination);
        NLower[destination]++;
    }

    void PrintGraph() const {
        for (unsigned int i = 0; i < AdjacencyList.size(); ++i) {
            cout << "Vertex " << i << ": ";
            for (const auto& neighbor : AdjacencyList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> Ordering() const {
        vector<int> nLower = NLower;
        queue<int> queue;
        for (unsigned int i = 0; i < nLower.size(); i++) {
            if (nLower[i] == 0) {
                queue.push(i);
            }
        }
        vector<int> ordering;
        while (!queue.empty()) {
            int currentSoldier = queue.front();
            queue.pop();
            ordering.push_back(currentSoldier + 1);
            for (const auto& neighbor : AdjacencyList[currentSoldier]) {
                nLower[neighbor]--;
                if (nLower[neighbor] == 0) {
                    queue.push(neighbor);
                }
            }
        }
        return ordering;
    }
};

int main() {
    unsigned int numSoldiers, numPairs;
    cin >> numSoldiers >> numPairs;
    TGraph graph(numSoldiers);
    for (unsigned int i = 0; i < numPairs; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph.AddEdge(a, b);
    }
    //graph.PrintGraph();
    vector<int> ordering = graph.Ordering();
    if (ordering.size() < numSoldiers) {
        cout << "No";
    } else {
        cout << "Yes" << endl;
        for (const auto& soldier : ordering) {
            cout << soldier << " ";
        } 
    }
    return 0;
}