#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

#define INF INT_MAX
#define V 21 // 20 points + index 0 (unused)

// Structure to represent location names
string locations[V] = {
    "",                          // Point 0 (unused)
    "Sports Complex",            // Point 1
    "Mosque",                    // Point 2
    "Restricted Area",           // Point 3
    "Lab 1",                     // Point 4
    "Washroom 1",                // Point 5
    "Room 1",                    // Point 6
    "Room 2",                    // Point 7
    "Room 3",                    // Point 8
    "Washroom 2",                // Point 9
    "C22",                       // Point 10
    "Room 4",                    // Point 11
    "Waiting Area",              // Point 12
    "Office",                    // Point 13
    "Finance Department",        // Point 14
    "Department",                // Point 15
    "Lab 2",                     // Point 16
    "Lab 3",                     // Point 17
    "Lab 4",                     // Point 18
    "Cafe",                      // Point 19
    "Library"                    // Point 20
};

// Adjacency matrix based on the graph image
int adjMatrix[V][V] = {
    // 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 0
    {  0,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 1
    {  0,  5,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 2
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 3
    {  0,  0,  4,  0,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  0,  0,  0,  0}, // 4
    {  0,  0,  0,  0,  5,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  0,  0,  0}, // 5
    {  0,  0,  0,  0,  0,  4,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 6
    {  0,  0,  0,  0,  0,  0,  5,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 7
    {  0,  0,  0,  0,  0,  0,  0,  4,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 8
    {  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 9
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0}, // 10
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0}, // 11
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  5,  0,  0,  0,  0,  0,  0,  0}, // 12
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  6,  0,  0,  0,  0,  0,  0}, // 13
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  5,  0,  0,  0,  0,  0}, // 14
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  4,  0,  0,  6,  0}, // 15
    {  0,  0,  0,  0,  7,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0,  6,  0,  0,  0}, // 16
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  5,  0,  0}, // 17
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  4,  0}, // 18
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0,  4,  0,  0}, // 19
    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}  // 20
};

// Structure for priority queue
struct Node {
    int distance;
    int vertex;
    
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

// Function to find shortest path using Dijkstra's algorithm
void dijkstra(int start, int end) {
    // Special case for Restricted Area
    if (start == 3 || end == 3) {
        cout << "\n========================================" << endl;
        cout << "ACCESS DENIED!" << endl;
        cout << "========================================" << endl;
        cout << "The Restricted Area (Point 3) is not accessible." << endl;
        cout << "No path exists to this location." << endl;
        cout << "========================================" << endl;
        return;
    }
    
    // Special case for Library
    if (start == 20 || end == 20) {
        cout << "\n========================================" << endl;
        cout << "LOCATION ON DIFFERENT FLOOR!" << endl;
        cout << "========================================" << endl;
        cout << "The Library (Point 20) is located on the 2nd floor." << endl;
        cout << "Please use the stairs to access the Library." << endl;
        cout << "No ground floor path available." << endl;
        cout << "========================================" << endl;
        return;
    }
    
    vector<int> dist(V, INF);
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);
    
    dist[start] = 0;
    
    priority_queue<Node, vector<Node>, greater<Node> > pq;
    Node startNode;
    startNode.distance = 0;
    startNode.vertex = start;
    pq.push(startNode);
    
    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (int v = 1; v < V; v++) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                int newDist = dist[u] + adjMatrix[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    parent[v] = u;
                    Node newNode;
                    newNode.distance = newDist;
                    newNode.vertex = v;
                    pq.push(newNode);
                }
            }
        }
    }
    
    // Print result
    if (dist[end] == INF) {
        cout << "\n========================================" << endl;
        cout << "NO PATH FOUND!" << endl;
        cout << "========================================" << endl;
        cout << "No path exists between Point " << start << " (" << locations[start] 
             << ") and Point " << end << " (" << locations[end] << ")" << endl;
        cout << "========================================" << endl;
        return;
    }
    
    // Reconstruct path
    vector<int> path;
    int current = end;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    
    // Display result
    cout << "\n========================================" << endl;
    cout << "SHORTEST PATH FOUND!" << endl;
    cout << "========================================" << endl;
    cout << "From: Point " << start << " (" << locations[start] << ")" << endl;
    cout << "To:   Point " << end << " (" << locations[end] << ")" << endl;
    cout << "\nTotal Distance: " << dist[end] << " units" << endl;
    cout << "\nPath: ";
    
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    cout << "\nDetailed Route:" << endl;
    for (size_t i = 0; i < path.size(); i++) {
        cout << "  Point " << path[i] << ": " << locations[path[i]];
        if (i < path.size() - 1) {
            cout << " (distance to next: " << adjMatrix[path[i]][path[i+1]] << " units)";
        }
        cout << endl;
    }
    cout << "========================================" << endl;
}

void displayAdjacencyMatrix() {
    cout << "\nADJACENCY MATRIX (0 = No connection):" << endl;
    cout << "      ";
    for (int i = 1; i < V; i++) {
        if (i < 10) cout << " ";
        cout << i << "  ";
    }
    cout << endl;
    
    for (int i = 1; i < V; i++) {
        if (i < 10) cout << " ";
        cout << i << "  ";
        for (int j = 1; j < V; j++) {
            if (adjMatrix[i][j] < 10) cout << " ";
            cout << adjMatrix[i][j] << "  ";
        }
        cout << endl;
    }
}

void displayLocations() {
    cout << "\n========================================" << endl;
    cout << "          LOCATION MAP" << endl;
    cout << "========================================" << endl;
    for (int i = 1; i < V; i++) {
        cout << "Point " << i;
        if (i < 10) cout << " ";
        cout << ": " << locations[i];
        if (i == 3) cout << " (Inaccessible)";
        if (i == 20) cout << " (2nd Floor)";
        cout << endl;
    }
    cout << "========================================" << endl;
}

int main() {
    int start, end;
    char choice;
    
    cout << "========================================" << endl;
    cout << "   CAMPUS NAVIGATION SYSTEM" << endl;
    cout << "========================================" << endl;
    
    do {
        displayLocations();
        
        cout << "\nEnter starting point (1-20): ";
        cin >> start;
        
        while (start < 1 || start > 20) {
            cout << "Invalid input! Please enter a point between 1 and 20: ";
            cin >> start;
        }
        
        cout << "Enter destination point (1-20): ";
        cin >> end;
        
        while (end < 1 || end > 20) {
            cout << "Invalid input! Please enter a point between 1 and 20: ";
            cin >> end;
        }
        
        if (start == end) {
            cout << "\nStart and end points are the same!" << endl;
        } else {
            dijkstra(start, end);
        }
        
        cout << "\nDo you want to:" << endl;
        cout << "  'n' - Find another path" << endl;
        cout << "  'm' - View adjacency matrix" << endl;
        cout << "  'q' - Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 'm' || choice == 'M') {
            displayAdjacencyMatrix();
            cout << "\nPress 'n' to find another path or 'q' to quit: ";
            cin >> choice;
        }
        
    } while (choice == 'n' || choice == 'N');
    
    cout << "\nThank you for using Campus Navigation System!" << endl;
    
    return 0;
}
