#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;


class TGraph {
private:
    int NumVertex = 0;
    vector<pair<int, int>> Cities = {};
    vector<vector<pair<int, int>>> Edges = {};

public:
    void ReadGraph() {
        cin >> NumVertex;
        Cities.resize(NumVertex);
        for (int i = 0; i < NumVertex; ++i) {
            cin >> Cities[i].first >> Cities[i].second;
        }
        int numSpecialRoads = 0;
        cin >> numSpecialRoads;
        Edges.resize(NumVertex);
        for (int i = 0; i < numSpecialRoads; ++i) {
            int j, k, s;
            cin >> j >> k >> s;
            Edges[j - 1].emplace_back(k - 1, s);
            Edges[k - 1].emplace_back(j - 1, s);
        }
    }

    double Dijkstra(int start, int end) const {
        vector<bool> marked(NumVertex, false);
        vector<bool> visited(NumVertex, false);
        vector<double> distances(NumVertex, 1e20);
        distances[start] = 0;
        for (int i = 0; i < NumVertex; ++i) {
            int node = end;
            for (int j = 0; j < NumVertex; ++j) {
                if (!visited[j] && distances[j] <= distances[node]) {
                    node = j;
                }        
            }
            double cost = distances[node];
            if (node == end) {
                return cost;
            }
            visited[node] = true;
            for (const auto& [nodeTo, edgeCost] : Edges[node]) {
                double newCost = cost + edgeCost;
                marked[nodeTo] = true;
                if (newCost < distances[nodeTo]) {
                    distances[nodeTo] = newCost;
                }
            }
            for (int k = 0; k < NumVertex; ++k) {
                if (marked[k] || visited[k]) {
                    continue;
                }
                double newCost = cost + Dist(Cities[node], Cities[k]);
                if (newCost < distances[k]) {
                    distances[k] = newCost;
                }
            }
            fill(marked.begin(), marked.end(), false); 
        }
        return -1;
    }

private:
    double Dist(const pair<int, int>& a, const pair<int, int>& b) const {
        double dx = a.first - b.first;
        double dy = a.second - b.second;
        return sqrt(pow(dx, 2.0)  + pow(dy, 2.0));
    }
};

int main() {
    TGraph graph;
    graph.ReadGraph();
    int start, end;
    cin >> start >> end;
    --start;
    --end;
    cout << setprecision(6) << fixed << graph.Dijkstra(start, end);
    return 0;
}