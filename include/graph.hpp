/*
    Simple undirected and unweighted graph implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <vector>
#include <fstream>
#include <sstream>
#include <forward_list>

// Undirected and unweighted graph
class Graph
{
    public:
        Graph(const size_t nv)
        {
            v = nv;
            adj.resize(nv);
        }
        
        //---------------------------
        //  Expects:
        // number_vertices 
        // number_edges
        // node_1 node_2
        // ...
        Graph(std::ifstream& in)
        {
            size_t ne;
            in >> v;
            in >> ne;
            adj.resize(v);
            for(size_t i=0; i<ne; i++) 
            {
                size_t u, w;
                in >> u >> w;
                addEdge(u, w);
            }
        }

        // Adds an unweighted and undirected edge
        // O(1)
        void addEdge(const size_t u, const size_t w)
        {
            adj[u].push_front(w);
            adj[w].push_front(u);
            e++;
        }

        // Number of vertices
        size_t V() const {
            return v;
        }

        // Number of edges
        size_t E() const {
            return e;
        }

        // Nodes adjacent to v
        // std::vector<size_t> 
        auto adj_to(const size_t v) const {
            return adj[v];
        }

        // Graphviz str()
        std::string str() const {
            std::stringstream ss;
            ss << "graph G {\n"; 
            for(size_t i=0; i<v; i++)
            {
                for(const size_t w : adj[i])
                    ss << "   " << i << "--" << w << '\n';
            }
            ss << "}\n";
            return ss.str();
        }

        // Book's str()
        std::string toString() const {
            std::stringstream ss;
            ss << v << " vertices, " << e << " edges\n";
            for(size_t i=0; i<v; i++)
            {
                ss << i << ": ";
                for(const size_t w : adj[i])
                    ss << w << " ";
                
                ss << '\n';
            }
            return ss.str();
        }

        size_t self_loops() const {
            size_t count = 0;
            for(size_t i=0; i<v; i++)
            {
                for(const size_t w : adj[i])
                    if(i==w) count++;
            }

            // Each edge counted twice...
            return count/2;
        }

    private:
        // Number of vertices and edges
        size_t v, e=0;

        // O(V + E) space complexity
        std::vector<std::forward_list<size_t>> adj;
};

#endif