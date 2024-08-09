#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>

using namespace std;

class TGraph {
private:
    int NumVertices = 0;
    unordered_map<int, vector<pair<int, int>>> AdjacencyList = {};

public:
    void ReadGraph() {
        cin >> NumVertices;
        int numMaps;
        cin >> numMaps;
        for (int i = 1; i <= numMaps; ++i) {
            int numRoads;
            cin >> numRoads;
            for (int j = 0; j < numRoads; ++j) {
                int k, s;
                cin >> k >> s;
                --k;
                --s;
                auto AddEdge = [this, &i](int a, int b) {
                    if (AdjacencyList.find(GetKey(i, a)) == AdjacencyList.end()) {
                        AdjacencyList[GetKey(i, a)].emplace_back(GetKey(i, b), 0);
                        AdjacencyList[GetKey(i, a)].emplace_back(GetKey(0, a), 0);
                        AdjacencyList[GetKey(0, a)].emplace_back(GetKey(i, a), 1);
                    } else {
                        AdjacencyList[GetKey(i, a)].emplace_back(GetKey(i, b), 0);
                    }
                };
                AddEdge(k, s);
                AddEdge(s, k);
            }
        }
    }

    int FindTheDistance() const {
        auto distances = BreadthFirstSearch();
        int minDistance = -1;
        for (const auto& [node, dist] : distances) {
            if (GetPair(node).second == NumVertices - 1 && GetPair(node).first != 0) {
                if (minDistance > dist || minDistance == -1) {
                    minDistance = dist;
                }
            }
        }
        if (minDistance == NumVertices) {
            return -1;
        }
        return minDistance;
    }

private:
    unordered_map<int, int> BreadthFirstSearch() const {
        unordered_map<int, int> distances;
        for (const auto& [node, v] : AdjacencyList) {
            distances[node] = NumVertices;
        }
        distances[GetKey(0, 0)] = 0;
        deque<int> queue;
        queue.push_back(GetKey(0, 0));
        unordered_map<int, bool> visited;
        while (!queue.empty()) {
            int currentVertex = queue.front();
            queue.pop_front();
            if (visited[currentVertex]) {
                continue;
            }
            for (const auto& [neighbor, dist] : AdjacencyList.at(currentVertex)) {
                if (distances[neighbor] > distances[currentVertex] + dist) {
                    distances[neighbor] = distances[currentVertex] + dist;
                    if (dist == 0) {
                        queue.push_front(neighbor);
                    } else {
                        queue.push_back(neighbor);
                    }
                    
                }
            }
            visited[currentVertex] = true;
        }
        return distances;
    }   

    int GetKey(int map, int vert) const {
        return map * NumVertices + vert;
    }

    pair<int, int> GetPair(int key) const {
        return {key / NumVertices, key % NumVertices};
    }
};

int main() {
    TGraph graph;
    graph.ReadGraph();
    cout << graph.FindTheDistance();
    return 0;
}