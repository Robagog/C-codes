#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class TGraph {
private:
    int NumRoutes;
    int NumSquares;
    vector<vector<int>> Routes;
    vector<vector<int>> AdjacencyList;
public:
    TGraph(int NumRoutes, int NumSquares)
        : NumRoutes(NumRoutes)
        , NumSquares(NumSquares)
        , Routes()
        , AdjacencyList()
    {
        Routes.resize(NumRoutes);
        AdjacencyList.resize(NumSquares);
    }
    void Add_route() {
        for (int i = 0; i < NumRoutes; i++) {
            int k;
            cin >> k;
            vector<int> route(k + 1);
            for (int j = 0; j <= k; j++) {
                cin >> route[j];
                route[j] --;
            }
            Routes[i] = route;
        }
    }
    void Build_graph() {
        for (const auto& route : Routes) {
            for (int i = 0; i < route.size() - 1; i++) {
                AdjacencyList[route[i]].push_back(route[i + 1]);
            }
        }
    }
    vector<int> Find_new_route() const {
        vector<int> new_route;
        vector<vector<int>> visitedList = AdjacencyList;
        int edjes = 0;
        for (const auto& i : AdjacencyList) {
            edjes += i.size();
        }
        Dfs(0, new_route, visitedList);
        if (new_route.size() != edjes)
        new_route.push_back(1);
        return new_route;
    }
private:
    void Dfs(int node, vector<int>& new_route, vector<vector<int>>& visitedList) const {
        new_route.push_back(node + 1);
        for (unsigned int i = 0; i < visitedList[node].size(); i++) {
            if (visitedList[visitedList[node][i]].size() != 0 ) {
                int next = visitedList[node][i];
                visitedList[node].erase(i + visitedList[node].cbegin());
                Dfs(next, new_route, visitedList);
            }
        }
    }
};

int main() {
    int num_routes, num_squares;
    cin >> num_routes >> num_squares;
    TGraph graph(num_routes, num_squares);
    graph.Add_route();
    graph.Build_graph();
    vector<int> new_route = graph.Find_new_route();
    for (int i = 0; i < new_route.size(); i++) {
        cout << new_route[i] << " ";
    }
    return 0;
}