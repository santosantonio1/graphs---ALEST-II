/*
    Dijkstra shortest path class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __DIJKSTRA_HPP__
#define __DIJKSTRA_HPP__

#include "wdigraph.hpp"
#include "idxpq.hpp"

#include<limits>
#include<algorithm>

// Shortest path dijkstra
class Dijkstra
{
    public:
        Dijkstra(const WDigraph& g, const size_t s)
        {
            edgeTo.resize(g.V());
            distTo.resize(g.V());
            pq = new IndexPQ<double>(g.V());

            std::fill(
                distTo.begin(),
                distTo.end(),
                std::numeric_limits<double>::infinity()
            );
            
            distTo[s] = 0.0;
            pq->push(s, 0.0);
            while(!pq->empty())
                relax(g, pq->pop());
        }

        ~Dijkstra()
        {
            delete pq;
            edgeTo.clear();
            // for(size_t i=0; i<edgeTo.size(); i++)
            //     if(edgeTo[i]) delete edgeTo[i];
        }

        double dist_to(const size_t v) const {
            return distTo[v];
        }

        bool hasPathTo(const size_t v) const {
            return distTo[v] < std::numeric_limits<double>::infinity();
        }

        auto pathTo(const size_t v) const {
            if(!hasPathTo(v)) return std::vector<DEdge>{};
            
            std::vector<DEdge> path;
            for(auto e=edgeTo[v]; e!=nullptr; e=edgeTo[e->from()])
                path.push_back(*e);

            std::reverse(
                path.begin(),
                path.end()
            );

            return path;
        }
    private:
        std::vector<DEdge*> edgeTo;
        std::vector<double> distTo;
        IndexPQ<double> *pq;

        void relax(const WDigraph& g, const size_t v)
        {
            for(const DEdge& e : g.adj_to(v))
            {
                const size_t w = e.to();
                if(distTo[w] > distTo[v] + e.weight())
                {
                    distTo[w] = distTo[v] + e.weight();

                    if(!edgeTo[w]) {
                        // Perhaps a move constructor would be nice...
                        edgeTo[w] = new DEdge{
                            e.from(),
                            e.to(),
                            e.weight()
                        };
                    } else {
                        *edgeTo[w] = e;
                    }
                    if(pq->contains(w)) pq->change(w, distTo[w]);
                    else    pq->push(w, distTo[w]);
                }
            }
        }
};

#endif