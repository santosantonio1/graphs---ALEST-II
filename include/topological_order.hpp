/*
    Topological Sort class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024
*/

#ifndef __TOPOLOGICAL_ORDER_HPP__
#define __TOPOLOGICAL_ORDER_HPP__

#include "wdigraph.hpp"

// Postorder topological sort class
class Topological
{
    public:
        Topological(const WDigraph& g)
        {
            marked.resize(g.V());

            for(size_t i=0; i<g.V(); i++)
                if(!marked[i]) dfs(g, i);
        }

        // reverse Topological order (postorder)
        std::vector<size_t> reverseOrder() const {
            return std::vector<size_t>{
                _order.rbegin(),
                _order.rend()
            };
        }

        // Topological order (postorder)
        std::vector<size_t> order() const {
            return _order;
        }
        
    private:
        std::vector<size_t> _order;

        // Marked nodes
        std::vector<bool> marked;
        
        void dfs(const WDigraph& g, const size_t v)
        {
            marked[v] = true;

            for(const DEdge& e : g.adj_to(v))
                if(!marked[e.to()])
                    dfs(g, e.to());

            _order.push_back(v);
        }
};

#endif