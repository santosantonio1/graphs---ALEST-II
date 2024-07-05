/*
    Connected Components class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 04/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __CONNECTED_COMPONENTS_HPP__
#define __CONNECTED_COMPONENTS_HPP__

#include "graph.hpp"

// Computes how many connected components are there in the graph g
class CC
{
    public:
        CC(const Graph& g)
        {
            idx.resize(g.V());
            marked.resize(g.V());

            for(size_t s=0; s<g.V(); s++)
                if(!marked[s]) {
                    dfs(g, s);
                    c++;
                }
        }

        bool connected(const size_t v, const size_t w) const {
            return idx[v] == idx[w];
        }

        size_t id(const size_t v) const {
            return idx[v];
        }

        size_t count() const {
            return c;
        }
    private:
        // Separates the nodes into groups (components), giving each 
        // node a component number
        std::vector<size_t> idx;

        // Marked nodes.
        std::vector<bool> marked;
        
        // Component number.
        size_t c=0;

        // DFS uses a time and space complexity of O(V+E) to support 
        // O(1) performance for connectivity queries in the graph
        void dfs(const Graph& g, const size_t v)
        {
            marked[v] = true;
            idx[v] = c;
            for(const size_t w : g.adj_to(v))
                if(!marked[w]) dfs(g, w);
        }
};

#endif