
// This class represents a directed graph using adjacency list
// representation
//
// Based on
// http://www.geeksforgeeks.org/find-if-there-is-a-path-between-two-vertices-in-a-given-graph/
//

#include <list>
#include <map>
#include <set>

template<typename T>
class Graph
{
    std::map<T,std::list<T> > adj;    // adjacency lists
public:
    void addEdge(T v, T w); // function to add an edge to graph
    bool isReachable(T s, T d);
};

template<typename T>
void Graph<T>::addEdge(T v, T w) {
    adj[v].push_back(w); // Add w to v’s list.
}

// A BFS based function to check whether d is reachable from s.
template<typename T>
bool Graph<T>::isReachable(T s, T d) {
    // Base case
    if (s == d) return true;

    // Mark all the vertices as not visited
    std::set<T> visited;

    // Create a queue for BFS
    std::list<T> queue;

    // Mark the current node as visited and enqueue it
    visited.insert( s );
    queue.push_back( s );

    while (!queue.empty()) {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        queue.pop_front();

        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for ( auto i = adj[s].begin(); i != adj[s].end(); ++i) {
            // If this adjacent node is the destination node, then 
            // return true
            if (*i == d) return true;

            // Else, continue to do BFS
            if ( visited.find( *i ) == visited.end() ) {
                visited.insert( *i );
                queue.push_back( *i );
            }
        }
    }

    // If BFS is complete without visiting d
    return false;
}

