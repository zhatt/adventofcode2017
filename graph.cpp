
#include <set>

#include "graph.h"

using namespace std;

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Add w to v’s list.
}
 
// A BFS based function to check whether d is reachable from s.
bool Graph::isReachable(int s, int d) {
    // Base case
    if (s == d)
        return true;

    // Mark all the vertices as not visited
    set<int> visited;

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited.insert( s );
    queue.push_back(s);

    // it will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;

    while (!queue.empty()) {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        queue.pop_front();

        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i) {
            // If this adjacent node is the destination node, then 
            // return true
            if (*i == d) return true;

            // Else, continue to do BFS
            if ( visited.find( *i ) == visited.end() ) {
                visited.insert( *i );
                queue.push_back(*i);
            }
        }
    }

    // If BFS is complete without visiting d
    return false;
}
 
