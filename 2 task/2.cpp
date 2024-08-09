#include <iostream>
#include <vector>

using namespace std;

class TGraph {
private:
    vector<vector<int>> Matrix = {};
    int NumVertex = 0;

public:
    void ReadFromStream(istream& stream) {
        stream >> NumVertex;
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

    bool HasCycle() const {
        vector<int> visited(NumVertex, 0);
        bool cycle = false;
        for (int i = 0; i < NumVertex; i++) {
            if (visited[i] == 0) {
                 DepthFirstSearch(i, visited, cycle);
            }
        }
        if (cycle) {
            return true;
        }
        return false;
    }

private:
    void DepthFirstSearch(int node, vector<int>& visited, bool& cycle) const {
        visited[node] = 1;
        for (int i = 0; i < NumVertex; i++) {
            if (Matrix[node][i] > 0) {
                if (visited[i] == 0) {
                    DepthFirstSearch(i, visited, cycle);
                } else if (visited[i] == 1) {
                    cycle = true;
                }
            }
        }
        visited[node] = 2;
    }
};

int main() {
    TGraph graph;
    graph.ReadFromStream(cin);
    cout << graph.HasCycle();
    return 0;
}