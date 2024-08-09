#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class TGraph {
private:
    vector<vector<int>> AdjacencyList;
    vector<int> Exits;
public:
    TGraph(int numVertices)
        : AdjacencyList(numVertices)
        , Exits()
    {}

    void AddEdge(int source, int destination) {
        AdjacencyList[source].push_back(destination);
        AdjacencyList[destination].push_back(source);
    }

    static TGraph ReadGraphFromStream(istream& stream) {
        int numVertices, numEdges;
        stream >> numVertices;
        TGraph graph(numVertices);
        graph.ReadExits(stream);
        stream >> numEdges;
        for (int i = 0; i < numEdges; ++i) {
            int source, destination;
            stream >> source >> destination;
            source--;
            destination--;
            graph.AddEdge(source, destination);
        }
        return graph;
    }

    void ReadExits(istream& stream) {
        int numExits, exit;
        stream >> numExits;
        Exits.resize(numExits);
        for (int i = 0; i < numExits; i++) {
            cin >> exit;
            exit--;
            Exits[i] = exit; 
        }
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

    void GetToClosestExit() const {
        vector<int> distances = BreadthFirstSearch(Exits);
        for (const auto& dist : distances) {
            cout << dist << " ";
        }
    }
    
    vector<int> BreadthFirstSearch(const vector<int>& startVertices) const {
        vector<int> distances(AdjacencyList.size(), -1);
        queue<int> queue;
        for (const auto& startVertex : startVertices) {
            distances[startVertex] = 0;
            queue.push(startVertex);
        }
        while (!queue.empty()) {
            int currentVertex = queue.front();
            queue.pop();
            for (const auto& neighbor : AdjacencyList[currentVertex]) {
                if (distances[neighbor] == -1) {
                    distances[neighbor] = distances[currentVertex] + 1;
                    queue.push(neighbor);
                }
            }
        }
        return distances;
    }    
};

int main() {
    TGraph graph = TGraph::ReadGraphFromStream(cin);
    //graph.PrintGraph();
    graph.GetToClosestExit();
    return 0;
}