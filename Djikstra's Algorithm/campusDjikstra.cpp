/*
    Written by Damian Kulec
    03/21/21
    This program shows an implementation of Djikstra's Algorithm
    Initially, I created an undirected graph to represent my school's campus (Northeastern University)
    All possible graph node connections, and the weights of their edges are stored in a separate .txt file
    This program first reads in the .txt file, then prompts the user to input what their starting position and their destination
    THe program then determines the optimal path from point A to point B, displaying the path that needs to be taken and the total distance
*/

#include <iostream>
#include <cstdlib>
#include <fstream>

#define infinity 9999
#define MAX_INT 100

using namespace std;

/* Function used to implement dijkstra's algorithm
 Iterates through each node to find the shortests distance. If dist[x] <= the current minimum value, then the shortest path is updated to the new, smaller value.
 Returns the index of the node with the shortest path */
int minDistance(int dist[], bool shortestpath[]) {
    int min = 0;
    int min_index;
    for(int x = 0; x < 22; x++) {
        if((shortestpath[x] == false) && (dist[x] <= min)) {
            min = dist[x];
            min_index = x;
        }
    }
    return min_index;
}

// The main function for implementing dijkstra's algorithm
void dijkstra(int G[22][22],int n,int startnode, int endnode) {
    int cost[22][22], dist[22], pred[22];
    int visited[22], count, min_dist, nextnode, i, j;
    // Nested for-loops copy the adjacency matrix to a new 2D matrix, cost[][], but all 0's are written as infinity (9999)
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(G[i][j] == 0)
                cost[i][j] = infinity;
            else
                cost[i][j]= G[i][j];
        }
    }
    // This for loop populates the arrays dist[], which holds the weights of edges between nodes, and pred[] which holds the predecessors of the nodes. Also populates visited[] array with 0's. If a node becomes visited, we switch that index in the array to a 1.
    for(i = 0; i < n; i++) {
        dist[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    dist[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    // The while loop helps establish the shortest path from each node to the start node
    while(count < n-1) {
        min_dist = infinity;
        for(i = 0; i < n; i++) {
            if(dist[i] < min_dist && !visited[i]) {
                min_dist = dist[i];
                nextnode = i;
            }
        }
        visited[nextnode] = 1;
        for(i = 0; i < n; i++) {
            if(!visited[i])
                if(min_dist + cost[nextnode][i] < dist[i]) {
                    dist[i] = min_dist + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        }
        count++;
    }
    // The final portion displays information to the user. It shows the shortest path taken, and the total distance
    cout << "\nPath = " << endnode;
    j = endnode;
    do {
        j = pred[j];
        cout<<" <- "<<j;
    }while(j != startnode);
    cout << "\nDistance to node " << endnode << " = " << dist[endnode] << endl;
}

int main() {
    ifstream inf;
    int count = 0;
    string vertex1, vertex2;
    int num_vertex, distance;
    int index1, index2;
    // Open text file
    inf.open("/Users/damiankulec/Desktop/EECE7205-HW5/campusGraph.txt");
    if (inf.fail())
    {
        cerr << "Error: Could not open input file\n";
        exit(1);
    }
    //activate the exception handling of inf stream
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    // This first inf command reads the first number (# of verticies)
    inf >> num_vertex;
    int adj_matrix[22][22];
    // We fill the adjacency matrix with 0's
    for(int x = 0; x < num_vertex; x++) {
        for(int y = 0; y < num_vertex; y++) {
            adj_matrix[x][y] = 0;
        }
    }
    // vertex_dir[] is an array that will store every unique node in order of appearance
    string vertex_dir[num_vertex];
    // We then read the first line of code and populate the first elements of both matrices
    inf >> vertex1 >> vertex2 >> distance;
    vertex_dir[0] = vertex1;
    vertex_dir[1] = vertex2;
    adj_matrix[0][1] = distance;
    adj_matrix[1][0] = distance;
    count = 1;
    // The two bool variables below help determine whether a vertex being read from the file has already been used previously or not. The index of the vertices in the directory will represent the relevant indices on the adjacency matrix
    bool check_v1 = false, check_v2 = false;
    while (count < MAX_INT) {
        check_v1 = false;
        check_v2 = false;
        try {
            inf >> vertex1 >> vertex2 >> distance;
            for(int x = 0; x <= count; x++) {
                // Checks through the directory to see if the vertex has been used already. If true, then that index will be used to write the distance into the adjacency matrix
                if(vertex1 == vertex_dir[x]) {
                    index1 = x;
                    check_v1 = true;
                }
                if(vertex2 == vertex_dir[x]) {
                    index2 = x;
                    check_v2 = true;
                }
            }
            // If a vertex read from the file does not appear in the directory, then it is populated at the end of the directory
            if(check_v1 == false) {
                count++;
                vertex_dir[count] = vertex1;
                index1 = count;
            }
            if(check_v2 == false) {
                count++;
                vertex_dir[count] = vertex2;
                index2 = count;
            }
            // Writes the edge weight to the adjacency matrix
            adj_matrix[index1][index2] = distance;
            adj_matrix[index2][index1] = distance;
        }
        catch (std::ifstream::failure e) {
            break;
        }
    }
    
    inf.close();
    
    int startnode, endnode;
    // Displays the vert4ex directory for user to know which nodes represents which building or intersection
    cout << "\nList of All Nodes " << endl;
    for(int x = 0; x < num_vertex; x++) {
        cout << "Node " << x << ": " << vertex_dir[x] << endl;
    }
    
    // Asks user to input the desired start and end nodes
    cout << endl << "Pick your starting node: ";
    cin >> startnode;
    cout << "Pick your finishing node: ";
    cin >> endnode;
    
    // Call the dijkstra function
    dijkstra(adj_matrix, 22, startnode, endnode);
    
    return 0;
}

