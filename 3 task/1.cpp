#include <iostream>
#include <vector>


using namespace std;

class TGraph {
private:
    vector<vector<int>> AdjMatrix = {};
    int NumVertex = 0;

public:
    void ReadGraph() {
        cin >> NumVertex;
        AdjMatrix.resize(NumVertex, vector<int>(NumVertex));
        for (int i = 0; i < NumVertex; i++) {
            for (int j = 0; j < NumVertex; j++) {
                cin >> AdjMatrix[i][j];
            }
        }
    }

    vector<vector<int>> FloydAlg() const {
        auto dist = AdjMatrix;
        for (int k = 0; k < NumVertex; ++k) {
            for (int i = 0; i < NumVertex; ++i) {
                for (int j = 0; j < NumVertex; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        return dist;
    }
};

int main() {
    TGraph graph;
    graph.ReadGraph();
    auto shortDist = graph.FloydAlg();
    for (size_t i = 0; i < shortDist.size(); i++) {
        for (size_t j = 0; j < shortDist.size(); j++) {
            cout << shortDist[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}