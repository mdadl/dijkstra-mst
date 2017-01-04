//////////////////////////////////////////////////////////////////////////////////////////////
// Graph Algorithm Project for Data Structures & Algorithm
// By Mohd Adil Bin Mat Ti @ Mokti (GP04686)
/////////////////////////////////////////////////////////////////////////////////////////////
//
//
// A C / C++ program for Dijkstra's single source shortest
// path algorithm. The program is for adjacency matrix
// representation of the graph.
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> //Kruskal
using namespace std;

#include <limits.h>

// Number of vertices in the graph
#define V 8

//////////////////////////////////////////////////////////////////////////////////////////////DJIKSTRA
// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
// Function to print shortest path from source to j
// using parent array
void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j]==-1) //-1
        return;
 
    printPath(parent, parent[j]);
 
    printf("%d ", j); //j
}
 
// A utility function to print the constructed distance
// array
int printSolution(int dist[], int n, int parent[])
{
    int src = 0; //0
    printf("<<< Djikstra Algorithm >>>\n\n");
    printf("Vertex\tDistance\tPath");
    for (int i = 1; i < V; i++)
    {
        printf("\n%d -> %d \t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
}
 
// Funtion that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V];  // The output array. dist[i] will hold
                  // the shortest distance from src to i
 
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];
 
    // Parent array to store shortest path tree
    int parent[V];
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }
 
    // print the constructed distance array
    printSolution(dist, V, parent);
}

////////////////////////////////////////////////////////////////////////////////////////////////KRUSKAL
// Creating shortcut for an integer pair
typedef  pair<int, int> iPair;
 
// Structure to represent a graph
struct Graph
{
    int Vv, E;
    vector< pair<int, iPair> > edges;
 
    // Constructor
    Graph(int Vv, int E)
    {
        this->Vv = Vv;
        this->E = E;
    }
 
    // Utility function to add an edge
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }
 
    // Function to find MST using Kruskal's
    // MST algorithm
    int kruskalMST();
};
 
// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;
 
    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
 
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
 
            //every element is parent of itself
            parent[i] = i;
        }
    }
 
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
 
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
 
        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
 
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
 
 /* Functions returns weight of the MST*/
 
int Graph::kruskalMST()
{
    int mst_wt = 0; // Initialize result
 
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
 
    // Create disjoint sets
    DisjointSets ds(Vv);
 
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
 
        int set_u = ds.find(u);
        int set_v = ds.find(v);
 
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            cout << u << " - " << v << endl;
 
            // Update MST weight
            mst_wt += it->first;
 
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
 
    return mst_wt;
}

///////////////////////////////////////////////////////////////////////////////////////////////PRIM
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < V; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}
 
// A utility function to print the constructed MST stored in parent[]
int printMST(int parent[], int n, int graph[V][V])
{
   printf("<<< Prim Algorithm >>>\n\n");
   printf("Edge   Weight\n");
   for (int i = 1; i < V; i++) //i=1
      printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}
 
// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(int graph[V][V])
{
     int parent[V]; // Array to store constructed MST
     int key[V];   // Key values used to pick minimum weight edge in cut
     bool mstSet[V];  // To represent set of vertices not yet included in MST
 
     // Initialize all keys as INFINITE
     for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (int count = 0; count < V-1; count++)
     {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < V; v++)
 
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
             parent[v]  = u, key[v] = graph[u][v];
     }
 
     // print the constructed MST
     printMST(parent, V, graph);
}

// driver program to test above function
int main()
{	
    /* Let us create the example graph discussed above */
    int graph[V][V] = {{0, 32, 29, 0, 0, 60, 51, 0},
                       {32, 0, 0, 0, 0, 0, 0, 21},
                       {29, 0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 34, 18, 0, 0},
                       {0, 0, 0, 34, 0, 40, 51, 46},
                       {60, 0, 0, 18, 40, 0, 0, 0},
                       {51, 0, 0, 0, 51, 0, 0, 25},
                       {0, 21, 0, 0, 46, 0, 25, 0},
                      };
 
 	int ch = 0;

     do {
     	cout << "Graph MST Algorithm Project" << endl
		 	 << "By Mohd Adil Bin Mat Ti @ Mokti (GP04686)" << endl << endl;
     	
        cout << " 1. Djikstra Algorithm" << endl
             << " 2. Kruskal Algorithm" << endl
             << " 3. Prim Algorithm" << endl
             << " 0. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> ch;

         switch (ch) {
             case 1: {
             			system("CLS");
             			dijkstra(graph, 0); //Load djikstra algorithm
					
                    	cout << endl << endl << "Press ENTER to continue...." << endl;
                    	cin.ignore();
                    	cin.get();
                    	system("CLS");
                	}
                    
                    break;

            case 2: {
            	
            		system("CLS");
            		int Vv = 8, E = 11;
    				Graph g(Vv, E);
 
    				//  making above shown graph
    				g.addEdge(3, 5, 18);
    				g.addEdge(1, 7, 21);
    				g.addEdge(6, 7, 25);
    				g.addEdge(0, 2, 29);
    				g.addEdge(0, 1, 32);
    				g.addEdge(3, 4, 34);
    				g.addEdge(5, 4, 40);
    				g.addEdge(4, 7, 46);
    				g.addEdge(0, 6, 51);
    				g.addEdge(4, 6, 51);
    				g.addEdge(0, 5, 60);
 
    				cout << "<<< Kruskal Algorithm >>>\n";
					cout << endl << "Edges of MST are \n";
    				int mst_wt = g.kruskalMST();
 
    				cout << endl << "Weight of MST is " << mst_wt;
            		
                    cout << endl << endl << "Press ENTER to continue...." << endl;
                    cin.ignore();
                    cin.get();
                    system("CLS");
                    }
                    break;

             case 3: {
             	
            		system("CLS");
            		primMST(graph);
                    
                    cout << endl << "Press ENTER to continue...." << endl;
                    cin.ignore();
                    cin.get();
                    system("CLS");
                    }
                    break;

             default: 
			 		system("CLS"); 
				 	break;
            }
      } while (ch != 0);
 
    //return 0;
}
