/*
    Eager Prim minimum spanning tree implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __EAGER_PRIM_MST_HPP__
#define __EAGER_PRIM_MST_HPP__

#include "wgraph.hpp"
#include "idxpq.hpp"

#include <limits>

// Prim's algorithm finds edges to connect vertices to the MST.
class PrimMST
{
    public:
        PrimMST(const WGraph& g)
        {
            distTo.resize(g.V());
            marked.resize(g.V());
            edgeTo.resize(g.V());

            std::fill(
                distTo.begin(),
                distTo.end(),
                std::numeric_limits<double>::infinity()
            );
        
            pq = new IndexPQ<double>(g.V());
            distTo[0] = 0.0;
            pq->push(0, 0.0);
        
            while(!pq->empty())
            {
                const size_t min = pq->pop();
                visit(g, min);
            }
        }

        ~PrimMST()
        {
            delete pq;
            for(size_t i=0; i<edgeTo.size(); i++)
                // if(!edgeTo[i]) delete edgeTo[i];
                if(edgeTo[i]) delete edgeTo[i];
        }

        // Return mst's edges.
        std::vector<Edge> edges() const {
            std::vector<Edge> mst;
            for(size_t i=0; i<edgeTo.size(); i++)
            {
                if(edgeTo[i])
                    mst.push_back(*edgeTo[i]);
            }
            return mst;
        }

        double weight() const {
            double w = 0.0;
            for(const auto& E : edgeTo)
                if(E != nullptr)
                    w += E->weight();

            return w;
        }
    private:
        std::vector<double> distTo;
        // Marks the vertex if he is already in the tree.
        std::vector<bool> marked;
        std::vector<Edge*> edgeTo;

        IndexPQ<double> *pq;

        // Instead of adding unnecessary edges, just updates the ones in the priority queue.
        void visit(const WGraph& g, const size_t v)
        {
            marked[v] = true;
            for(const Edge& e : g.adj_to(v))
            {
                const size_t w = e.other(v);
                if(marked[w]) continue;
                if(e.weight() < distTo[w])
                {   
                    if(!edgeTo[w]) {
                        edgeTo[w] = new Edge{
                            e.either(),
                            e.other(e.either()), 
                            e.weight()
                        };
                    } else { 
                        *edgeTo[w] = e;
                    }
                    // *edgeTo[w] = e;
                    distTo[w] = e.weight();
                    if(pq->contains(w)) pq->change(w, distTo[w]);
                    else pq->push(w, distTo[w]);
                }
            }
        }
};

#endif