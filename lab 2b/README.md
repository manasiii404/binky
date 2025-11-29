# OSPF Link State Routing

This program implements OSPF (Open Shortest Path First) Link State Routing protocol to generate routing tables for all routers in a network.

## What is OSPF?

**OSPF (Open Shortest Path First)** is a link-state routing protocol used in IP networks. It uses Dijkstra's Shortest Path First (SPF) algorithm to build and calculate the shortest path to all known destinations.

### Key Concepts

- **Link State Database (LSDB)**: Complete topology map shared by all routers
- **SPF Algorithm**: Dijkstra's algorithm run by each router independently
- **Routing Table**: Computed table showing next-hop for each destination
- **Cost Metric**: Link weight used to determine best path

## How OSPF Works

1. **Neighbor Discovery**: Routers discover neighbors on directly connected networks
2. **Link State Advertisement (LSA)**: Each router advertises its links and costs
3. **LSDB Flooding**: LSAs are flooded throughout the network
4. **SPF Calculation**: Each router runs Dijkstra's algorithm on the complete topology
5. **Routing Table**: Each router builds its own routing table with next-hop information

## Compilation

```bash
g++ -o ospf_routing.exe ospf_routing.cpp
```

## Usage

```bash
./ospf_routing.exe
```

### Option 1: Predefined Network (Same as Lab 2a)

Uses the same 6-router network topology from lab 2a:

```
Router 0: neighbors: Router 1 (cost: 4), Router 2 (cost: 2)
Router 1: neighbors: Router 2 (cost: 1), Router 3 (cost: 5)
Router 2: neighbors: Router 3 (cost: 8), Router 4 (cost: 10)
Router 3: neighbors: Router 4 (cost: 2), Router 5 (cost: 6)
Router 4: neighbors: Router 5 (cost: 3)
Router 5: neighbors: None
```

### Option 2: Custom Network

Create your own network topology by specifying routers and links.

## Example Output

```
════════════════════════════════════════════════════════════════
    OSPF (Open Shortest Path First) Link State Routing
════════════════════════════════════════════════════════════════

Choose an option:
1. Use predefined network (same as lab 2a)
2. Create custom network
Enter choice: 1

Using predefined network topology (6 routers):

════════════════════════════════════════════════════════════════
        OSPF LINK STATE ROUTING - ROUTING TABLES
════════════════════════════════════════════════════════════════

╔════════════════════════════════════════════════════════════════╗
║              LINK STATE DATABASE (LSDB)                        ║
╚════════════════════════════════════════════════════════════════╝

Network Topology (Adjacency Information):

Router 0 neighbors: Router 1 (cost: 4), Router 2 (cost: 2)
Router 1 neighbors: Router 2 (cost: 1), Router 3 (cost: 5)
Router 2 neighbors: Router 3 (cost: 8), Router 4 (cost: 10)
Router 3 neighbors: Router 4 (cost: 2), Router 5 (cost: 6)
Router 4 neighbors: Router 5 (cost: 3)
Router 5 neighbors: None

Generating routing tables for all routers using Dijkstra's SPF...
(Shortest Path First algorithm)

╔════════════════════════════════════════════════════════════════╗
║          OSPF ROUTING TABLE FOR ROUTER 0                       ║
╚════════════════════════════════════════════════════════════════╝

Destination    Next Hop    Cost      Path
----------------------------------------------------------------------
Router 1       Router 2    3         0 -> 2 -> 1
Router 2       Router 2    2         0 -> 2
Router 3       Router 2    8         0 -> 2 -> 1 -> 3
Router 4       Router 2    10        0 -> 2 -> 1 -> 3 -> 4
Router 5       Router 2    13        0 -> 2 -> 1 -> 3 -> 4 -> 5

╔════════════════════════════════════════════════════════════════╗
║          OSPF ROUTING TABLE FOR ROUTER 1                       ║
╚════════════════════════════════════════════════════════════════╝

Destination    Next Hop    Cost      Path
----------------------------------------------------------------------
Router 0       -           INF       No path
Router 2       Router 2    1         1 -> 2
Router 3       Router 3    5         1 -> 3
Router 4       Router 3    7         1 -> 3 -> 4
Router 5       Router 3    10        1 -> 3 -> 4 -> 5

... (routing tables for all 6 routers)

╔════════════════════════════════════════════════════════════════╗
║                         SUMMARY                                ║
╚════════════════════════════════════════════════════════════════╝

✓ Link State Database (LSDB) flooded to all routers
✓ Each router ran Dijkstra's SPF algorithm independently
✓ Routing tables computed based on complete network topology
✓ Next-hop information determined for optimal forwarding
```

## Routing Table Format

Each routing table entry contains:

| Field | Description |
|-------|-------------|
| **Destination** | Target router to reach |
| **Next Hop** | First router to forward packets to |
| **Cost** | Total cost (metric) to reach destination |
| **Path** | Complete path from source to destination |

## OSPF vs Distance Vector

| Feature | OSPF (Link State) | RIP (Distance Vector) |
|---------|-------------------|----------------------|
| Algorithm | Dijkstra's SPF | Bellman-Ford |
| Knowledge | Complete topology | Only neighbor distances |
| Convergence | Fast | Slow |
| Scalability | Large networks | Small networks |
| Routing Loops | No loops | Possible (count-to-infinity) |

## Key Features

✅ **Complete Topology View**: All routers have identical LSDB  
✅ **Independent Calculation**: Each router runs SPF independently  
✅ **Next-Hop Determination**: Shows which router to forward to  
✅ **Loop-Free**: Dijkstra's algorithm guarantees loop-free paths  
✅ **Optimal Paths**: Always finds shortest path based on cost metric  

## Applications

- **Enterprise Networks**: Internal routing within organizations
- **ISP Networks**: Routing within autonomous systems
- **Data Centers**: Efficient routing in large-scale deployments
- **Campus Networks**: University and corporate campus routing

## Technical Details

### Time Complexity
- **SPF Calculation**: O((V + E) log V) per router
- **Total for all routers**: O(V × (V + E) log V)

### Space Complexity
- **LSDB Storage**: O(E) - stores all links
- **Routing Table**: O(V) per router

## Differences from Lab 2a

| Lab 2a (Dijkstra) | Lab 2b (OSPF) |
|-------------------|---------------|
| Single source shortest path | All routers compute routing tables |
| Shows paths from one router | Shows next-hop for forwarding |
| Algorithm demonstration | Routing protocol simulation |
| One routing table | Complete network routing tables |

## Testing

Run the program and verify:
1. All routers have consistent view of topology (LSDB)
2. Routing tables show correct next-hop information
3. Costs match shortest paths from lab 2a
4. Unreachable destinations show "INF" cost

## License

This is educational code for learning network routing protocols and OSPF concepts.
