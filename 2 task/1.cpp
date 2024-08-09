#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class TGraph {
private:
    vector<vector<int>> Matrix = {};
    int NumVertex = 0;
    int Vertex = 0;

public:
    void ReadFromStream(istream& stream) {
        stream >> NumVertex >> Vertex;
        Vertex--;
        Matrix.resize(NumVertex, vector<int>(NumVertex));
        for (int i = 0; i < NumVertex; i++) {
            for (int j = 0; j < NumVertex; j++) {
                stream >> Matrix[i][j];
            }
        }
    }

    void WriteMatrix(ostream& stream) const {
        for (int i = 0; i < NumVertex; i++) {
            for (int j = 0; j < NumVertex; j++) {
                stream << Matrix[i][j] << " ";
            }
            stream << endl;
        }
    }

    int GetConnectedComponent() const {
        vector<int> visited(NumVertex, 0);
        DepthFirstSearch(Vertex, visited);
        return accumulate(visited.begin(), visited.end(), 0);
    }

private:
    void DepthFirstSearch(int node, vector<int>& visited) const {
        visited[node] = 1;
        for (int i = 0; i < NumVertex; i++) {
            if (Matrix[node][i] > 0 && visited[i] == 0) {
                DepthFirstSearch(i, visited);
            }
        }
    }
};




int main() {
    TGraph graph;
    graph.ReadFromStream(cin);
    cout << graph.GetConnectedComponent();
    return 0;
}