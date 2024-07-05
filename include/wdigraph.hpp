/*
    Weighted digraph implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __WEIGHTED_DIRECTED_GRAPH_HPP__
#define __WEIGHTED_DIRECTED_GRAPH_HPP__

#include "dedge.hpp"

#include <vector>
#include <forward_list>
#include <fstream>
#include <sstream>

// Weighted directed graph class
class WDigraph
{
    public:
        WDigraph(const size_t nv)
        {
            v = nv;
            e = 0;
            adj.resize(nv);
        }

        WDigraph(std::ifstream& in)
        {
            size_t ne;
            in >> v;
            in >> ne;
            adj.resize(v);
            for(size_t i=0; i<ne; i++)
            {
                size_t to, from;
                double w;
                in >> to >> from >> w;
                addEdge(DEdge{to, from, w});    
            }
        }

        // O(1)
        void addEdge(const DEdge& E)
        {
            adj[E.from()].push_front(E);
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

        auto edges() const {
            std::vector<DEdge> b;
            for(size_t i=0; i<v; i++)
            {
                for(const DEdge& e : adj[i])
                    b.push_back(e);
            }
            return b;
        }

        // Graphviz str()
        std::string str() const {
            std::stringstream ss;
            ss << "digraph G {\n";
            for(size_t i=0; i<v; i++)
            {
                for(const auto& E : adj[i])
                    ss << "   " << E.from() << "->" << E.to() << '\n'
                       << "[weight=" << E.weight() << "]\n";
            }
            ss << "}\n";

            return ss.str();
        }
    private:
        // Number of vertices and edges
        size_t v, e;

        // O(V + E) space complexity
        std::vector<std::forward_list<DEdge>> adj;
};

#endif