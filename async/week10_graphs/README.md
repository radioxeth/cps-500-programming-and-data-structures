# Week 10 Graphs
- [Home](/README.md#cps-500-programming-and-data-structures)
- [10.1 Introduction to Graphs](#101-Introduction-To-Graphs)
- [10.2 Graph Representations](#102-graph-representations)
- [10.3 Graph Traversals](#103-graph-traversals)
- [10.4 Shortest Paths](#104-shortest-paths)
- [10.5 Minimum Spanning tree](#105-minimum-spanning-tree)


## 10.1 Introduction to Graphs
[top](#week-10-graphs)

### Graphs

- Graphs are a mathematical construct that are widely used in every day computer science.
- They model:
  - Social networks
  - computer communications
  - protein interactoin networks
  - route planning
  - goal planning
- They are common strudied in mathematics under graph theory (some overlap here)

### Graph Definitions
- A graph has two components:
  1. **vertex set** (entities, people, computers, events)
  2. **edges** (interactions between vertices) - take the form of (v<sub>1</sub>, v<sub>2</sub>), where v<sub>1</sub> and v<sub>2</sub> are verices
    - v1 and v2 called **neighbors/adjacent** when an edge exists between them
- A **directed graph** is one in which edges have a direction.
- An **undirected graph**  is one in which edges have no direction so (v<sub>1</sub>,v<sub>2</sub>) automatically implies (v<sub>2</sub>,v<sub>1</sub>) 

- A **weighted graph** is one in which edges have a real number weight associated with them.
  - weights can represent cost, distance, capacity, and so on.

### Graph Terms
- **path** a series of vertices such that they are pairwise connected by edges
  - {e,d,c,a} is a path on the right
  - {b,e,d} is not a path on the right
  <img src="./graph1.png" alt="graph 1" width="200"/>
- **cycle** a path that returns to its starting node.
  - {a,b,d,c,a} is a cycle
- node e has a **reflexive** edge

### More Definitions
- **subgraph** a subset of the vertices (and their associated edges)
  - considered a valid graph in its own right
- All edges do not have to be connected for a graph to be valid
  - in particular, a graph can be divided into one or more **connected components**
  - there can be a single graph with vertices {a,b,c,d,e,f} and two connected components {a,b,c,d} and {e,f}
  <img src="./graph2.png" alt="graph 2" width="200"/>

## 10.2 Graph Representations
[top](#week-10-graphs)

### Two main data representations
1. Adjacency matrix
2. Adjacency list

### Adjacency Matrix
- all nodes are assigned an ID between [0:N-1]
- we create the NxN matric (double array)
  - the value in matrix[i,j]=1 if there is an edge from i to j, 0 otherwise
  - alternatively, we can store a real number indicating the weight of the edge between i and j
    - with 0 or infinity representing no edge
### Example
  <img src="./graph3.png" alt="adjacency matrix example" width="400"/>
- notice that memory usage is O(N<sup>2</sup>)
- a **sparse** graph is mostly 0s
- A **dense** graph  is mostly 1s

### Performance
- most real-world graph are **sparse**, so they wast too much memory: O(N<sup>2</sup>)
- checking if an edge exists from i to j is O(1)
- to iterate over all edges of node i takes O(N)
- looking up the incoming edges for edge i takes O(N)
- certain graph calculations are easiest in the form of matrix calculations

### Adjacency Lists
- an alternative representation for graphs uses **adjacency lits**
- adjacency lists use an array of lists
- the index into the array matches the node's ID
- the list at index *i* is the set of nodes that has an edge **to**.

### Adjacency List Implementation
```C
typedef struct Edge{
    int dest;
    struct Edge*next;
} Edge;
typedef struct Graph{
    int N;
    struct Edge** adj_ist;
}
```

### Adjacency List Example
<img src="./graph4.png" alt = "adjacency list example" widght="400"/>

### Performance
- Adjacency lists use O(|N|+|E|) memory and still has memory overhead as O(|E|) for pointers in lists.
- Checking if an edge exists from i to j is O(degree(i)), typically less than N.
- To iterate over all edges of node *i* takes O(degree(i)).
- looking up incoming edges takes O(|E|)

### Which to Use?
- It depends on the problem and the graph
- Large graphs may be too large/slow to use the adjacency matrix.
- Dense graphs might be worth the trade-off for adjacency matrix.
- It depends on the problem - iterate over all edges? Do you need to do matrix calculations over a graph?

## 10.3 Graph Traversals
[top](#week-10-graphs)

- Revisit BFS and DFS on graphs
- Notice that a tree is a type of graph (directed-acyclic)
- How might the algorithm change?

### Depth-First seach
- Recall that a depth-first search alogorithm vists children nodes before it visits sibling nodes.
1. Choose an arbitrary node as a starting point i
2. See the i into a stack of vertices to explore
3. Remove i from the stack
  1. Process(i)
  2. Mark i as explored
4. Iterate over its neighbors, j(out-edges)
5. Check if j has already been explored or discovered
6. If not:
  1. Add j to the stack
  2. Mark it as explored
7. Repeat steps 3-6

### DFS Algorithm
```C
void dfs(Graph * graph){
    int visited[graph->N];
    for(int i =0; i<graph->N;i++){//need this loop for unconnected graphs
        if(!visited[i]){
            visited[i]=1;
            dfs_util(graph,i,visited);
        }
    }
}
```
### DFS Util
```C
void dfs_util(Graph* graph, int node, int* visited){
    visit(node);
    GraphNode* front = graph->array[node];
    while (front!=NULL){
        if(!visited[front->dest]){
            visited[front->dest]=1;
            dfs_util(graph,front->dest,visited);
        }
        front = front->next;
    }
}
```

### Restarting?
- Notice that we only called dfs_util from dfs once. (dfs_util was called many times from itself)
- The graph was connected an undirected.
- A directed graph might not have a path from our starting node to all other nodes.
- in this case, we need to restart the exploration

### Alternative DFS
- We can alos implement DFS using a stack.
- Seed the stack with a starting node.
- Instead of recursiely calling dfs_util on nodes, push the neighbors onto the stack
- iterate until the stack is empty by removing a node at each iteration

### Breadth-First Seach
- Breadth-first search (BFS) visits all of the sibling nodes before visiting children
- The stack implmentation of DFS is extremely similar to the BFS implementation, except that BFS uses a queue.

### BFS Algorithm
```C
void bfs(Graph * graph){
    int visited[graph->N];
    for(int i =0; i<graph->N;i++){//need this loop for unconnected graphs
        if(!visited[i]){
            visited[i]=1;
            bfs_util(graph,i,visited);
        }
    }
}
```
### BFS Util
```C
void bfs_util(Graph* graph, int node, int* visited){
    Queue q;
    enqueue(&q,node);
    while(!isEmpty(&q)){
        int node=dequeue(&q);
        GraphNode* front = graph->array[node];
        while(front!=NULL){
            if(!visited[front->dest]){
                visited[front->dest]=1;
                enqueue(&queue, front->dest);
            }
            front =front->next;
        }
    }
}
```

### BFS vs DFS
- Both need potential restarts.
- Both have O(|V|+|E|) runtimes
- DFS goes far away from the starting node.
- BFS goes out methodically layer by layer.
- Which is right?
  - Depends on your use case.

## 10.4 Shortest Paths
[top](#week-10-graphs)
### Single-Source Shortest Path
- Find the shortest paths to all target nodes from a givn source.
- There are variations:
  - **single-destination shortest path** find the shortest path from all nodes to a given point.
  - **all-pairs shortest path** find the shortest path between all pairs of nodes.

### Example
- find the shortest path from A to all other nodes
<img src="./graph5.png" width="200"/>
- There's a possibility that A cannot get to do.
  
  - D is a **source node**
    - Distance from A to D is &infin;
    - a node with no incoming edges
  - E is a **sink node**
    - a node with no outgoing edges
- There can be sink nodes that a path cannot reach

### Dijkstra's Algorithm
1. Start off by assuming that the distance is infinite from A to all other nodes.
2. Mark all nodes as unvisited
3. Select the closes unvisited neighbor.
4. Visit all neighbors of the current node, and take the smaller of the existing distance and the path through each neighbor.
5. Remove the current node from the unvisited set once all the neighbors are visited.

### Algorithms
```C
int * dijkstra(Graph* g, int source){
    int dist[g->N];
    for(int i = 0; i<N;++i){
        dist[i]=-1; //infinity
    }
    dist[source]=0;
    MinHeap *h=makeHeap(dist);
    while (!isEmpty(h)){
        int next=removeMin(h);
        GraphNode* front = g->adjList[next];
        while(front!=NULL){
            int adj = front->dest;
            int alt=dist[next]+front->weight;
            if(alt<dist[adj]||dist[adj]<0){
                dist[adj]=alt;
                decreaseValue(h,adj,alt);
            }
        }
    }
}
```

### Shortest Path Example
<img src="./graph6.png" alt="dijkstra example" width="200"/>
<img src="./graph7.png" alt="dijkstra example completed" width="200"/>

### Performance
- Time to make the heap is O(|V|)
- Reasserting the heap is log(|V|)
- total time is O((|E|+|V|)*log(|V|))
- Note: Would the previous algorithm work with negative edge weights?
  - greedy algorithm

## 10.5 Minimum Spanning Tree
[top](#week-10-graphs)
### Problem Definition
- **minimum spanning tree** Given a connected, undirected, weighted graph, find a subset of edges that:
  - Has a minimum weight subject to other constraints
  - Connects all edges (remains connected)
  - Has no cycles
- We can relax the connected requirement and find a set of trees for each onnected component called a **minimum spanning forest**

### Prim's Algorithm
- Prim's algorithm is a **greedy algorithm** that works by continuously selecting the cheapest edge to add to the minimum spanning tree
1. Initialize tree sets: reached (empty), unreached (all nodes), minimumSpanningTree (empty)
2. Choose an arbitrary node to start/seed the tree and move from unreached to reached
3. Select the minimum edge, e=(x,y) that connects a node, x, in the reached set of nodes to a node, y, in the unreached set of nodes
4. Add e to the minimum spanning tree
5. Move y from the unreached set to the reached set
6. Repeat steps 3-5 until the unreached set is empty

### Algorithm
```C
void prims(Graph*g){
    int cost[g->N];
    for (int i =0; i< g->N;i++) cost[i]=-1;//infinity
    cost[0]=0;
    MinHeap * h = makeHeap(cost);
    while(!isEmpty(h)){
        int min = removeMin(h);
        GraphNode* front = g->adjList
        while(front!=NULL){
            int adj = front->dest;
            if(cost[adj]>front->weight){
                cost[adj]=front->weight;
                decreaseKey(h,adj,front->weight);// decrease the key in the heap
            }
        }
    }
    
}
```

### Minimum Spanning Tree Example
<img src="./graph8.png" alt="prim's example" width="200"/>

- arbitrarily pick one node and set that distance to 0
- everyting else is &infin;

<img src="./graph9.png" alt="prim's example complete" width="200"/>

- all of the nodes are still connected!
- This is the minimum spanning tree, so there are other spanning trees that have a longer/higher distance

### Perfomance
- notice the similarity to Dijkstra's algorithm
- In fact, the two algorithms have the same runtime complexity to **O((|E|+|V|)*(log(|V|)))**
