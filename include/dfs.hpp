/*
    Depth First Search class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 04/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __DEPTH_FIRST_SEARCH_HPP__
#define __DEPTH_FIRST_SEARCH_HPP__

#include "graph.hpp"

// Depth First Search class
class DFS
{
    public:
        DFS(const Graph& g, const size_t s)
        {
            marked.resize(g.V());
            // O(V + E)
            dfs(g, s);
        }

        // Number of nodes reachable from source 
        size_t count() const {
            return c;
        }

        bool isMarked(const size_t v) const {
            return marked[v];
        }
    private:
        // Marked nodes
        std::vector<bool> marked;

        // Node count
        size_t c = 0;

        void dfs(const Graph& g, const size_t v)
        {
            marked[v] = true;
            c++;
            for(const size_t w : g.adj_to(v))
                if(!marked[w]) 
                    dfs(g, w);
        }
};

#endif