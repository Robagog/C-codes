#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class TGraph {
private:
    using TEdge = pair<uint64_t, uint32_t>;
    
    uint32_t NumVertex = 0;
    vector<vector<TEdge>> Cities = {};

public:
    void ReadGraph() {
        cin >> NumVertex;
        uint32_t NumRoads;
        cin >> NumRoads;
        Cities.resize(NumVertex); 
        for (uint32_t i = 0; i < NumRoads; ++i) {
            uint32_t j, k, s;
            cin >> j >> k >> s;
            Cities[j - 1].emplace_back(s, k - 1);
            Cities[k - 1].emplace_back(s, j - 1);
        }
    }

    int64_t Dijkstra(uint32_t start, uint32_t end) const {
        vector<uint64_t> distances(NumVertex, numeric_limits<uint64_t>::max());
        distances[start] = 0;
        priority_queue<TEdge, vector<TEdge>, greater<TEdge>> pq;
        pq.emplace(0, start);
        while (!pq.empty()) {
            auto [cost, node] = pq.top();
            pq.pop();
            if (node == end) {
                return distances[end];
            }
            if (cost > distances[node]) {
                continue;
            }
            for (auto [edgeCost, to] : Cities[node]) {
                uint64_t newCost = cost + edgeCost;
                if (newCost < distances[to]) {
                    distances[to] = newCost;
                    pq.emplace(newCost, to);
                }
            }
        }
        return -1;
    }
};

int main() {
    TGraph graph;
    graph.ReadGraph();
    uint32_t start, end;
    cin >> start >> end;
    --start;
    --end;
    cout << graph.Dijkstra(start, end);
    return 0;
}