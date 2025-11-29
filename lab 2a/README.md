# Dijkstra's Shortest Path Algorithm

This program implements Dijkstra's algorithm to find the shortest path from a source vertex to all other vertices in a weighted graph.

## Algorithm Overview

Dijkstra's algorithm is a greedy algorithm that solves the single-source shortest path problem for a graph with non-negative edge weights. It maintains a set of vertices whose shortest distance from the source is known and repeatedly selects the vertex with the minimum distance to expand.

### Time Complexity
- **With Priority Queue (Min-Heap)**: O((V + E) log V)
- **V** = Number of vertices
- **E** = Number of edges

### Space Complexity
- O(V) for distance array, parent array, and visited array

## Features

- ✅ **Priority Queue Optimization**: Uses min-heap for efficient vertex selection
- ✅ **Path Reconstruction**: Shows the complete path from source to each destination
- ✅ **Step-by-Step Execution**: Displays algorithm execution in real-time
- ✅ **Flexible Input**: Supports both predefined and custom graphs
- ✅ **Network Routing Application**: Example graph simulates network routing scenario

## Compilation

```bash
g++ -o dijkstra.exe dijkstra.cpp
```

## Usage

### Run the Program

```bash
./dijkstra.exe
```

### Option 1: Predefined Example Graph

The program includes a predefined graph with 6 vertices representing a network topology:

```
Graph Structure:
Vertex 0: (1, w:4) (2, w:2)
Vertex 1: (2, w:1) (3, w:5)
Vertex 2: (3, w:8) (4, w:10)
Vertex 3: (4, w:2) (5, w:6)
Vertex 4: (5, w:3)
Vertex 5:
```

**Visual Representation:**
```
    0 ---4--- 1
    |       / |
    2     1   5
    |   /     |
    2 ---8--- 3 ---6--- 5
    |         |       /
   10         2     3
    |         |   /
    4 --------+--
```

### Option 2: Custom Graph

You can create your own graph by:
1. Specifying the number of vertices
2. Specifying the number of edges
3. Entering each edge as: `source destination weight`

## Example Output

```
========================================
  Dijkstra's Shortest Path Algorithm  
========================================

Choose an option:
1. Use predefined example graph
2. Create custom graph
Enter choice: 1

Using predefined example graph (6 vertices):

=== Graph Structure ===

Vertex 0: (1, w:4) (2, w:2)
Vertex 1: (2, w:1) (3, w:5)
Vertex 2: (3, w:8) (4, w:10)
Vertex 3: (4, w:2) (5, w:6)
Vertex 4: (5, w:3)
Vertex 5:

Enter source vertex (0-5): 0

=== Dijkstra's Algorithm Execution ===

Visiting vertex 0 (distance: 0)
  Updated distance to vertex 1: 4 (via 0)
  Updated distance to vertex 2: 2 (via 0)
Visiting vertex 2 (distance: 2)
  Updated distance to vertex 1: 3 (via 2)
  Updated distance to vertex 3: 10 (via 2)
  Updated distance to vertex 4: 12 (via 2)
Visiting vertex 1 (distance: 3)
  Updated distance to vertex 3: 8 (via 1)
Visiting vertex 3 (distance: 8)
  Updated distance to vertex 4: 10 (via 3)
  Updated distance to vertex 5: 14 (via 3)
Visiting vertex 4 (distance: 10)
  Updated distance to vertex 5: 13 (via 4)
Visiting vertex 5 (distance: 13)

=== Shortest Path Results ===

Source Vertex: 0

Destination  Distance    Path
--------------------------------------------------
0           0           0
1           3           0 -> 2 -> 1
2           2           0 -> 2
3           8           0 -> 2 -> 1 -> 3
4           10          0 -> 2 -> 1 -> 3 -> 4
5           13          0 -> 2 -> 1 -> 3 -> 4 -> 5
```

## Algorithm Steps

1. **Initialize**: Set distance to source as 0 and all other distances as infinity
2. **Create Priority Queue**: Add source vertex with distance 0
3. **Main Loop**:
   - Extract vertex with minimum distance from priority queue
   - Mark it as visited
   - For each adjacent vertex:
     - If new path is shorter, update distance and parent
     - Add to priority queue
4. **Path Reconstruction**: Use parent array to reconstruct shortest paths

## Applications

- **Network Routing**: Finding optimal routes in computer networks
- **GPS Navigation**: Shortest path in road networks
- **Social Networks**: Finding degrees of separation
- **Game Development**: Pathfinding for NPCs
- **Flight Planning**: Cheapest flight routes

## Graph Representation

The program uses an **adjacency list** representation:
- Each vertex maintains a list of edges
- Each edge stores destination vertex and weight
- Efficient for sparse graphs

## Key Data Structures

1. **Priority Queue (Min-Heap)**: Efficiently selects vertex with minimum distance
2. **Distance Array**: Stores shortest distance from source to each vertex
3. **Parent Array**: Stores parent of each vertex in shortest path tree
4. **Visited Array**: Tracks processed vertices

## Limitations

- Works only with **non-negative edge weights**
- For negative weights, use Bellman-Ford algorithm
- For all-pairs shortest paths, use Floyd-Warshall algorithm

## Testing

### Test Case 1: Source Vertex 0
Expected shortest distances:
- 0 → 0: 0
- 0 → 1: 3 (via 2)
- 0 → 2: 2
- 0 → 3: 8 (via 2 → 1)
- 0 → 4: 10 (via 2 → 1 → 3)
- 0 → 5: 13 (via 2 → 1 → 3 → 4)

### Test Case 2: Custom Graph
Try creating a simple triangle graph:
```
Vertices: 3
Edges: 3
Edge 1: 0 1 1
Edge 2: 1 2 2
Edge 3: 0 2 4
Source: 0
```

Expected result:
- 0 → 0: 0
- 0 → 1: 1
- 0 → 2: 3 (via 1, not direct path of 4)

## License

This is educational code for learning graph algorithms and network routing concepts.
