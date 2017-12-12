
// This class represents a directed graph using adjacency list
// representation
//
// Based on
// http://www.geeksforgeeks.org/find-if-there-is-a-path-between-two-vertices-in-a-given-graph/
//

#include <list>
#include <map>

class Graph
{
    std::map<int,std::list<int> > adj;    // adjacency lists
public:
    void addEdge(int v, int w); // function to add an edge to graph
    bool isReachable(int s, int d);
};
