/*
    Simple undirected and weighted graph implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __WEIGHTED_UNDIRECTED_GRAPH_HPP__
#define __WEIGHTED_UNDIRECTED_GRAPH_HPP__

#include "edge.hpp"

#include <fstream>
#include <vector>
#include <forward_list>

// Weighted undirected graph class
class WGraph
{
    public:
        WGraph(const size_t nv)
        {
            v = nv;
            e = 0;
            adj.resize(v);
        }

        //---------------------------
        //  Expects:
        // number_vertices 
        // number_edges
        // node_1 node_2 weight
        // ...
        WGraph(std::ifstream& in)
        {
            size_t ne;
            in >> v;
            in >> ne;
            adj.resize(v);

            for(size_t i=0; i<ne; i++)
            {
                size_t a, b;
                double w;
                in >> a >> b >> w;
                
                addEdge(Edge{a,b,w});
            }
        }

        // Adds a weighted and undirected edge
        // O(1)
        void addEdge(const Edge& E)
        {
            const size_t v = E.either(), u = E.other(v);
            adj[v].push_front(E);
            adj[u].push_front(E);
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

        // Edges leaving v
        auto adj_to(const size_t v) const {
            return adj[v];
        }

        // Edges of the graph
        std::vector<Edge> edges() const {
            std::vector<Edge> b;
            for(size_t i=0; i<v; i++)
            {
                for(const Edge& E : adj[i])
                    if(E.other(i) > i) b.push_back(E);
            }

            return b;
        }

        // Graphviz str()
        std::string str() const {
            std::stringstream ss;
            ss << "graph G {\n"; 
            for(size_t i=0; i<v; i++)
            {
                for(const Edge& w : adj[i])
                    ss << "   " << i << "--" << w.other(i) 
                       << "[weight=" << w.weight() <<"]\n";
            }
            ss << "}\n";
            return ss.str();
        }

    private:
        // Number of vertices and edges
        size_t v, e;

        // O(V + E) space complexity
        std::vector<std::forward_list<Edge>> adj;
};

#endif