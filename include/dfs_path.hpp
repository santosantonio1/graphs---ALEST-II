/*
    Depth First Search paths class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 04/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __DEPTH_FIRST_SEARCH_PATHS_HPP__
#define __DEPTH_FIRST_SEARCH_PATHS_HPP__

#include "graph.hpp"
#include <algorithm>

// Paths created using DFS
class DFS_PATHS
{
    public:
        DFS_PATHS(const Graph& g, const size_t s)
        {
            this->s = s;
            marked.resize(g.V());
            edgeTo.resize(g.V());
        
            dfs(g, s);
        }

        bool hasPathTo(const size_t v) const {
            return marked[v];
        }
        
        std::vector<size_t> pathTo(const size_t v) const {
            if(!hasPathTo(v)) return std::vector<size_t>{};

            std::vector<size_t> path;
            for(size_t i=v; i!=s; i=edgeTo[i])
                path.push_back(i);
            
            path.push_back(s);

            // Careful, start node is last element in path vector.
            std::reverse(
                path.begin(),
                path.end()
            );
            return path;
        }
    private:
        std::vector<bool> marked;
        std::vector<size_t> edgeTo;

        // Source node
        size_t s;

        void dfs(const Graph& g, const size_t v)
        {
            marked[v] = true;
            for(const size_t w : g.adj_to(v))
            {
                if(!marked[w]) {
                    edgeTo[w] = v;
                    dfs(g, w);
                }
            }
        }
};

#endif