#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


class TGraph {
private:
    vector<std::vector<int>> AdjacencyList;
    vector<std::vector<int>> ReverseAdjacencyList;
public:
    TGraph(int numVertices)
        : AdjacencyList(numVertices)
        , ReverseAdjacencyList(numVertices)
    {}

    void AddEdge(int source, int destination) {
        AdjacencyList[source].push_back(destination);
        ReverseAdjacencyList[destination].push_back(source);
    }
    
    vector<int> FindStrongConnectivity() const {
        vector<bool> visited(AdjacencyList.size(), false);
        stack<int> dfsStack = {};
        vector<int> componentId(AdjacencyList.size(), -1);
        for (unsigned int i = 0; i < AdjacencyList.size(); i++) {
            if (!visited[i]) {
                Dfs(i, visited, dfsStack);
            }
        }
        fill(visited.begin(), visited.end(), false);
        int component = 0;
        while (!dfsStack.empty()) {
            int vertex = dfsStack.top();
            dfsStack.pop();

            if (!visited[vertex]) {
                component++;
                ReverseDfs(vertex, component, visited, componentId);
            }
        }
        return componentId;
    }

private:
    void ReverseDfs(int vertex, int component, vector<bool>& visited, vector<int>& componentId) const {
        visited[vertex] = true;
        componentId[vertex] = component;
        for (const auto& neighbor : ReverseAdjacencyList[vertex]) {
            if (!visited[neighbor]) {
                ReverseDfs(neighbor, component, visited, componentId);
            }
        }
    }

    void Dfs(int vertex, vector<bool>& visited, stack<int>& dfsStack) const {
        visited[vertex] = true;
        for (const auto& neighbor : AdjacencyList[vertex]) {
            if (!visited[neighbor]) {
                Dfs(neighbor, visited, dfsStack);
            }
        }
        dfsStack.push(vertex);
    }
};

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;
    TGraph graph(numVertices);
    for (int i = 0; i < numEdges; i++) {
        int source, destination;
        cin >> source >> destination;
        source--;
        destination--;
        graph.AddEdge(source, destination);
    }
    vector<int> components = graph.FindStrongConnectivity();
    int numComponents = 0;
    for (unsigned int i = 0; i < components.size(); i++) {
        numComponents = max(numComponents, components[i]);
    }
    cout << numComponents << endl;
    for (unsigned int i = 0; i < components.size(); i++) {
        cout << components[i] << " ";
    }
    return 0;
}