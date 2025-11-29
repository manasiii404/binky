#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>

using namespace std;

#define INF INT_MAX

// Structure to represent a graph edge
struct Edge {
    int destination;
    int weight;
    
    Edge(int dest, int w) : destination(dest), weight(w) {}
};

// Structure to represent a node in priority queue
struct Node {
    int vertex;
    int distance;
    
    Node(int v, int d) : vertex(v), distance(d) {}
    
    // Comparator for priority queue (min-heap based on distance)
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

class Graph {
private:
    int vertices;
    vector<vector<Edge>> adjacencyList;
    
public:
    Graph(int v) : vertices(v) {
        adjacencyList.resize(v);
    }
    
    // Add an edge to the graph
    void addEdge(int source, int destination, int weight) {
        adjacencyList[source].push_back(Edge(destination, weight));
        // For undirected graph, uncomment the line below:
        // adjacencyList[destination].push_back(Edge(source, weight));
    }
    
    // Dijkstra's algorithm implementation
    void dijkstra(int source) {
        // Initialize distances to all vertices as infinite
        vector<int> distance(vertices, INF);
        vector<int> parent(vertices, -1);
        vector<bool> visited(vertices, false);
        
        // Priority queue to store vertices with their distances
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        
        // Distance to source is 0
        distance[source] = 0;
        pq.push(Node(source, 0));
        
        cout << "\n=== Dijkstra's Algorithm Execution ===\n\n";
        
        while (!pq.empty()) {
            // Get vertex with minimum distance
            int u = pq.top().vertex;
            pq.pop();
            
            // Skip if already visited
            if (visited[u]) continue;
            
            visited[u] = true;
            cout << "Visiting vertex " << u << " (distance: " << distance[u] << ")\n";
            
            // Update distances to adjacent vertices
            for (const Edge& edge : adjacencyList[u]) {
                int v = edge.destination;
                int weight = edge.weight;
                
                // Relaxation step
                if (!visited[v] && distance[u] != INF && 
                    distance[u] + weight < distance[v]) {
                    
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                    pq.push(Node(v, distance[v]));
                    
                    cout << "  Updated distance to vertex " << v 
                         << ": " << distance[v] << " (via " << u << ")\n";
                }
            }
        }
        
        // Print results
        printResults(source, distance, parent);
    }
    
    // Print the shortest paths and distances
    void printResults(int source, const vector<int>& distance, const vector<int>& parent) {
        cout << "\n=== Shortest Path Results ===\n\n";
        cout << "Source Vertex: " << source << "\n\n";
        cout << left << setw(12) << "Destination" 
             << setw(12) << "Distance" 
             << "Path\n";
        cout << string(50, '-') << "\n";
        
        for (int i = 0; i < vertices; i++) {
            cout << left << setw(12) << i;
            
            if (distance[i] == INF) {
                cout << setw(12) << "INF" << "No path\n";
            } else {
                cout << setw(12) << distance[i];
                printPath(parent, i);
                cout << "\n";
            }
        }
    }
    
    // Recursively print the path from source to destination
    void printPath(const vector<int>& parent, int vertex) {
        if (parent[vertex] == -1) {
            cout << vertex;
            return;
        }
        
        printPath(parent, parent[vertex]);
        cout << " -> " << vertex;
    }
    
    // Display the graph
    void displayGraph() {
        cout << "\n=== Graph Structure ===\n\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << i << ": ";
            for (const Edge& edge : adjacencyList[i]) {
                cout << "(" << edge.destination << ", w:" << edge.weight << ") ";
            }
            cout << "\n";
        }
    }
};

int main() {
    cout << "========================================\n";
    cout << "  Dijkstra's Shortest Path Algorithm  \n";
    cout << "========================================\n";
    
    int choice;
    cout << "\nChoose an option:\n";
    cout << "1. Use predefined example graph\n";
    cout << "2. Create custom graph\n";
    cout << "Enter choice: ";
    cin >> choice;
    
    if (choice == 1) {
        // Example graph from network routing scenario
        cout << "\nUsing predefined example graph (6 vertices):\n";
        
        Graph g(6);
        
        // Add edges (source, destination, weight)
        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 2);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 8);
        g.addEdge(2, 4, 10);
        g.addEdge(3, 4, 2);
        g.addEdge(3, 5, 6);
        g.addEdge(4, 5, 3);
        
        g.displayGraph();
        
        int source;
        cout << "\nEnter source vertex (0-5): ";
        cin >> source;
        
        if (source >= 0 && source < 6) {
            g.dijkstra(source);
        } else {
            cout << "Invalid source vertex!\n";
        }
        
    } else if (choice == 2) {
        int vertices, edges;
        cout << "\nEnter number of vertices: ";
        cin >> vertices;
        
        Graph g(vertices);
        
        cout << "Enter number of edges: ";
        cin >> edges;
        
        cout << "\nEnter edges (source destination weight):\n";
        for (int i = 0; i < edges; i++) {
            int src, dest, weight;
            cout << "Edge " << (i + 1) << ": ";
            cin >> src >> dest >> weight;
            g.addEdge(src, dest, weight);
        }
        
        g.displayGraph();
        
        int source;
        cout << "\nEnter source vertex (0-" << (vertices - 1) << "): ";
        cin >> source;
        
        if (source >= 0 && source < vertices) {
            g.dijkstra(source);
        } else {
            cout << "Invalid source vertex!\n";
        }
        
    } else {
        cout << "Invalid choice!\n";
        return 1;
    }
    
    return 0;
}
