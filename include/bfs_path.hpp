/*
    Breadth First Search paths class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 04/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __BREADTH_FIRST_SEARCH_PATHS_HPP__
#define __BREADTH_FIRST_SEARCH_PATHS_HPP__

#include "graph.hpp"
#include <queue>
#include <algorithm>

// Paths created using BFS
class BFS_PATHS
{
    public:
        BFS_PATHS(const Graph& g, const size_t s)
        {
            marked.resize(g.V());
            edgeTo.resize(g.V());
            this->s = s;

            bfs(g, s);
        }

        bool hasPathTo(const size_t v) const {
            return marked[v];
        }

        std::vector<size_t> pathTo(const size_t v) const {
            if(!hasPathTo(v)) return std::vector<size_t>{};

            std::vector<size_t> path;
            for(size_t x=v; x!=s; x = edgeTo[x])
                path.push_back(x);
            
            path.push_back(s);

            // Careful, start node is last element in path vector
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

        void bfs(const Graph& g, const size_t s)
        {
            std::queue<size_t> q;
            marked[s] = true;
            q.push(s);
            
            while(!q.empty())
            {
                const size_t v = q.front();
                q.pop();
                for(const size_t w : g.adj_to(v))
                {
                    if(!marked[w]) {
                        edgeTo[w] = v;
                        marked[w] = true;
                        q.push(w);
                    }
                }
            }
        }
};

#endif