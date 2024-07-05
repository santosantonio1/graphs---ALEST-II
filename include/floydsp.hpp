/*
    Floyd Warshall shortest path class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024
*/

#ifndef __FLOYD_WARSHALL_SHORTEST_PATH_HPP__
#define __FLOYD_WARSHALL_SHORTEST_PATH_HPP__

#include "wdigraph.hpp"

#include <algorithm>
#include <limits>

// Floyd-Warshall shortest path class
class FloydSP
{
    public:
        FloydSP(const WDigraph& refg)
        {   
            v = refg.V();
            _pathTo.resize(refg.V());
            _weightTo.resize(refg.V());
            for(size_t i=0; i<refg.V(); i++) _pathTo[i].resize(refg.V());
            for(size_t i=0; i<refg.V(); i++) _weightTo[i].resize(refg.V());

            // Matrices initializations
            for(size_t src=0; src<refg.V(); src++)
            {
                for(size_t tgt=0; tgt<refg.V(); tgt++)
                {
                    _pathTo[src][tgt] = (src == tgt) ? src : -1;
                    _weightTo[src][tgt] = (src == tgt) ? 0 : std::numeric_limits<double>::infinity();
                }
            }

            // Setting up matrice's initial states (based on refg edges)
            for(const auto& e : refg.edges())
            {
                _pathTo[e.from()][e.to()] = e.from();
                _weightTo[e.from()][e.to()] = e.weight();
            }

            // Floyd-Warshall running...
            for(size_t k=0; k<refg.V(); k++)
            {
                for(size_t i=0; i<refg.V(); i++)
                {
                    for(size_t j=0; j<refg.V(); j++)
                    {
                        if(_weightTo[i][j] > _weightTo[i][k] + _weightTo[k][j])
                        {
                            _weightTo[i][j] = _weightTo[i][k] + _weightTo[k][j];
                            _pathTo[i][j] = _pathTo[k][j];
                        }
                    }
                }
            }
        }

        auto pathTo(size_t u, size_t v) const {

            if(_pathTo[u][v]<0) return std::vector<size_t>{};

            std::vector<size_t> path;

            path.push_back(v);
            while(u!=v)
            {
                v = _pathTo[u][v];
                path.push_back(v);
            }

            std::reverse(
                path.begin(),
                path.end()
            );
            
            return path;
        }

        bool hasPathTo(const size_t u, const size_t v) const {
            return _pathTo[u][v]>=0;
        }

        double dist_to(const size_t u, const size_t v) const {
            return _weightTo[u][v];
        }

    private:
        size_t v;
        std::vector<std::vector<int>> _pathTo;
        std::vector<std::vector<double>> _weightTo;
};

#endif