#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>
#include <string>

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
    
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

// Structure to represent a routing table entry
struct RoutingEntry {
    int destination;
    int nextHop;
    int cost;
    string path;
};

class OSPFRouter {
private:
    int vertices;
    vector<vector<Edge>> adjacencyList;
    
    // Helper function to build path string
    string buildPath(const vector<int>& parent, int dest) {
        if (parent[dest] == -1) {
            return to_string(dest);
        }
        return buildPath(parent, parent[dest]) + " -> " + to_string(dest);
    }
    
    // Helper function to find next hop
    int findNextHop(const vector<int>& parent, int source, int dest) {
        if (dest == source) return source;
        if (parent[dest] == -1) return -1; // No path
        
        // Trace back to find the first hop from source
        int current = dest;
        while (parent[current] != source && parent[current] != -1) {
            current = parent[current];
        }
        
        if (parent[current] == source) {
            return current;
        }
        return -1;
    }
    
public:
    OSPFRouter(int v) : vertices(v) {
        adjacencyList.resize(v);
    }
    
    // Add a directed edge
    void addEdge(int source, int destination, int weight) {
        adjacencyList[source].push_back(Edge(destination, weight));
    }
    
    // Run Dijkstra's algorithm from a specific source
    vector<RoutingEntry> computeRoutingTable(int source) {
        vector<int> distance(vertices, INF);
        vector<int> parent(vertices, -1);
        vector<bool> visited(vertices, false);
        
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        
        distance[source] = 0;
        pq.push(Node(source, 0));
        
        // Dijkstra's algorithm
        while (!pq.empty()) {
            int u = pq.top().vertex;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            for (const Edge& edge : adjacencyList[u]) {
                int v = edge.destination;
                int weight = edge.weight;
                
                if (!visited[v] && distance[u] != INF && 
                    distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                    pq.push(Node(v, distance[v]));
                }
            }
        }
        
        // Build routing table
        vector<RoutingEntry> routingTable;
        for (int i = 0; i < vertices; i++) {
            if (i != source) {
                RoutingEntry entry;
                entry.destination = i;
                entry.cost = distance[i];
                entry.nextHop = findNextHop(parent, source, i);
                
                if (distance[i] != INF) {
                    entry.path = buildPath(parent, i);
                } else {
                    entry.path = "No path";
                }
                
                routingTable.push_back(entry);
            }
        }
        
        return routingTable;
    }
    
    // Display routing table in OSPF format
    void displayRoutingTable(int routerID, const vector<RoutingEntry>& table) {
        cout << "\n================================================================\n";
        cout << "          OSPF ROUTING TABLE FOR ROUTER " << routerID << "\n";
        cout << "================================================================\n\n";
        
        cout << left << setw(15) << "Destination" 
             << setw(12) << "Next Hop" 
             << setw(10) << "Cost"
             << "Path\n";
        cout << string(70, '-') << "\n";
        
        for (const RoutingEntry& entry : table) {
            cout << left << setw(15) << ("Router " + to_string(entry.destination));
            
            if (entry.nextHop == -1) {
                cout << setw(12) << "-"
                     << setw(10) << "INF"
                     << entry.path << "\n";
            } else {
                cout << setw(12) << ("Router " + to_string(entry.nextHop))
                     << setw(10) << entry.cost
                     << entry.path << "\n";
            }
        }
        cout << "\n";
    }
    
    // Display the network topology (Link State Database)
    void displayLinkStateDatabase() {
        cout << "\n================================================================\n";
        cout << "              LINK STATE DATABASE (LSDB)\n";
        cout << "================================================================\n\n";
        
        cout << "Network Topology (Adjacency Information):\n\n";
        
        for (int i = 0; i < vertices; i++) {
            cout << "Router " << i << " neighbors: ";
            if (adjacencyList[i].empty()) {
                cout << "None";
            } else {
                for (size_t j = 0; j < adjacencyList[i].size(); j++) {
                    const Edge& edge = adjacencyList[i][j];
                    cout << "Router " << edge.destination 
                         << " (cost: " << edge.weight << ")";
                    if (j < adjacencyList[i].size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    // Generate routing tables for all routers
    void generateAllRoutingTables() {
        cout << "\n================================================================\n";
        cout << "        OSPF LINK STATE ROUTING - ROUTING TABLES\n";
        cout << "================================================================\n";
        
        // Display Link State Database first
        displayLinkStateDatabase();
        
        cout << "Generating routing tables for all routers using Dijkstra's SPF...\n";
        cout << "(Shortest Path First algorithm)\n";
        
        // Generate and display routing table for each router
        for (int router = 0; router < vertices; router++) {
            vector<RoutingEntry> table = computeRoutingTable(router);
            displayRoutingTable(router, table);
        }
    }
    
    int getVertexCount() const {
        return vertices;
    }
};

int main() {
    cout << "================================================================\n";
    cout << "    OSPF (Open Shortest Path First) Link State Routing\n";
    cout << "================================================================\n";
    
    int choice;
    cout << "\nChoose an option:\n";
    cout << "1. Use predefined network (same as lab 2a)\n";
    cout << "2. Create custom network\n";
    cout << "Enter choice: ";
    cin >> choice;
    
    if (choice == 1) {
        cout << "\nUsing predefined network topology (6 routers):\n";
        
        OSPFRouter network(6);
        
        // Add edges - same network as lab 2a
        network.addEdge(0, 1, 4);
        network.addEdge(0, 2, 2);
        network.addEdge(1, 2, 1);
        network.addEdge(1, 3, 5);
        network.addEdge(2, 3, 8);
        network.addEdge(2, 4, 10);
        network.addEdge(3, 4, 2);
        network.addEdge(3, 5, 6);
        network.addEdge(4, 5, 3);
        
        // Generate routing tables for all routers
        network.generateAllRoutingTables();
        
        // Summary
        cout << "\n================================================================\n";
        cout << "                         SUMMARY\n";
        cout << "================================================================\n\n";
        cout << "[*] Link State Database (LSDB) flooded to all routers\n";
        cout << "[*] Each router ran Dijkstra's SPF algorithm independently\n";
        cout << "[*] Routing tables computed based on complete network topology\n";
        cout << "[*] Next-hop information determined for optimal forwarding\n\n";
        
    } else if (choice == 2) {
        int vertices, edges;
        cout << "\nEnter number of routers: ";
        cin >> vertices;
        
        OSPFRouter network(vertices);
        
        cout << "Enter number of links: ";
        cin >> edges;
        
        cout << "\nEnter links (source destination cost):\n";
        for (int i = 0; i < edges; i++) {
            int src, dest, cost;
            cout << "Link " << (i + 1) << ": ";
            cin >> src >> dest >> cost;
            network.addEdge(src, dest, cost);
        }
        
        network.generateAllRoutingTables();
        
        cout << "\n================================================================\n";
        cout << "                         SUMMARY\n";
        cout << "================================================================\n\n";
        cout << "[*] Custom network topology configured\n";
        cout << "[*] OSPF routing tables generated for all " << vertices << " routers\n";
        cout << "[*] Link State Routing protocol simulation complete\n\n";
        
    } else {
        cout << "Invalid choice!\n";
        return 1;
    }
    
    return 0;
}
