/*
    Acylic shortest path class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __ACYLIC_SHORTEST_PATH_HPP__
#define __ACYLIC_SHORTEST_PATH_HPP__

#include "topological_order.hpp"

#include <limits>

class AcylicSP
{
    public:
        AcylicSP(const WDigraph& g, const size_t s)
        {
            _edgeTo.resize(g.V());
            _distTo.resize(g.V());

            for(size_t i=0; i<g.V(); i++)
                std::fill(
                    _distTo.begin(),
                    _distTo.end(),
                    std::numeric_limits<double>::infinity()
                );

            _distTo[s] = 0.0;
            Topological top(g);
            for(const size_t i : top.reverseOrder())
                relax(g, i);
        }

        ~AcylicSP()
        {
            // Or _edgeTo.clear()...
            for(size_t i=0; i<_edgeTo.size(); i++)
                if(_edgeTo[i]) delete _edgeTo[i];
        }

        double dist_to(const size_t v) const {
            return _distTo[v];
        }

        bool hasPathTo(const size_t v) const {
            return _distTo[v] < std::numeric_limits<double>::infinity();
        }

        auto pathTo(const size_t v) const {
            if(!hasPathTo(v)) return std::vector<DEdge>{};

            std::vector<DEdge> path;
            for(auto e=_edgeTo[v]; e!=nullptr; e=_edgeTo[e->from()])
                path.push_back(*e);

            std::reverse(
                path.begin(),
                path.end()
            );

            return path;                
        }
    private:
        std::vector<DEdge*> _edgeTo;
        std::vector<double> _distTo;

        void relax(const WDigraph& g, const size_t v)
        {
            for(const DEdge& e : g.adj_to(v))
            {
                const size_t w = e.to();
                if(_distTo[w] > _distTo[v] + e.weight())
                {
                    _distTo[w] = _distTo[v] + e.weight();
                    
                    if(!_edgeTo[w]) {
                        _edgeTo[w] = new DEdge{
                            e.from(),
                            e.to(),
                            e.weight()
                        };
                    } else {
                        *_edgeTo[w] = e;
                    }
                }
            }
        }
};

#endif