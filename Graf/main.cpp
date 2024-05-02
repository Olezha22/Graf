#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

struct Edge {
    int to;
    int weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

class Graph {
private:
    vector<vector<Edge>> adjList;
    int n;

public:
    Graph(int n) : n(n), adjList(n) {}

    void addEdge(int from, int to, int weight) {
        if (from > n || to > n) {
            cout << "Error: You are trying to add not existing edge\n";
            return;
        }
        adjList[from].push_back(Edge(to, weight));
    }

    void removeEdge(int from, int to) {
        if (from >= n || to >= n) {
            cout << "Error: You are trying to remove not existing edge\n";
            return;
        }

        auto& edges = adjList[from];
        edges.erase(
            remove_if(edges.begin(), edges.end(), [to](const Edge& e) {
                return e.to == to;
                }),
            edges.end()
                    );
    }

    void dijkstra(int source) {
        vector<int> dist(n, INT_MAX);
        set<pair<int, int>> active_vertices;

        dist[source] = 0;
        active_vertices.insert({ 0, source });

        while (!active_vertices.empty()) {
            int v = active_vertices.begin()->second;
            active_vertices.erase(active_vertices.begin());

            for (const Edge& e : adjList[v]) {
                if (dist[e.to] > dist[v] + e.weight) {
                    active_vertices.erase({ dist[e.to], e.to });
                    dist[e.to] = dist[v] + e.weight;
                    active_vertices.insert({ dist[e.to], e.to });
                }
            }
        }

        cout << "The shortest distances from vertice " << source << " are:" << endl;
        for (int i = 0; i < n; i++) {
            if (dist[i] == INT_MAX)
                cout << "Vertice " << i << ": infinity" << endl;
            else
                cout << "Vertice " << i << ": " << dist[i] << endl;
        }
    }

    void print() {
        cout << "Graph: " << endl;
        cout << "Vertices: ";
        for (int i = 0; i < n; i++) {
            cout << i << " ";
        }

        cout << "\nEdges: \n";
        for (int i = 0; i < n; i++) {
            for (const Edge& e : adjList[i]) {
                
                cout << "Edge #" << i+1 << " => From: " << i << " To: " << e.to << " Weight: " << e.weight << endl;
            }
        }
    }

    int getWeight(int from, int to) {
        for (const Edge& e : adjList[from]) {
            if (e.to == to) {
                return e.weight;
            }
        }
        cout << "Error: Edge is not found\n";
    }

    vector<pair<int, int>> findEdgesByWeight(int weight) {
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; i++) {
            for (const Edge& e : adjList[i]) {
                if (e.weight == weight) {
                    edges.push_back({ i, e.to });
                }
            }
        }
        return edges;
    }

    void findShortestPath(int source, int target) {
        vector<int> dist(n, numeric_limits<int>::max());
        vector<int> prev(n, -1);
        set<pair<int, int>> active_vertices;

        dist[source] = 0;
        active_vertices.insert({ 0, source });

        while (!active_vertices.empty()) {
            int v = active_vertices.begin()->second;
            active_vertices.erase(active_vertices.begin());

            for (const Edge& e : adjList[v]) {
                if (dist[e.to] > dist[v] + e.weight) {
                    active_vertices.erase({ dist[e.to], e.to });
                    dist[e.to] = dist[v] + e.weight;
                    prev[e.to] = v;
                    active_vertices.insert({ dist[e.to], e.to });
                }
            }
        }

        if (dist[target] == numeric_limits<int>::max()) {
            cout << "There is no path from vertex " << source << " to vertex " << target << endl;
            return;
        }

        stack<int> path;
        int current = target;
        while (current != -1) {
            path.push(current);
            current = prev[current];
        }

        cout << "Shortest path from vertex " << source << " to vertex " << target << ": ";
        while (!path.empty()) {
            cout << path.top() << " ";
            path.pop();
        }
        cout << endl;
        cout << "Shortest distance: " << dist[target] << endl;
    }
};

int main() {
    int n = 5;
    Graph g(n);

    g.addEdge(1, 0, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 4);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 1);
    g.addEdge(4, 3, 1);

    g.findShortestPath(1, 3);

    return 0;
}
