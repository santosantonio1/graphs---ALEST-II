/*
    Lazy Prim minimum spanning tree implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __LAZY_PRIM_MST_HPP__
#define __LAZY_PRIM_MST_HPP__

#include "wgraph.hpp"
#include <queue>

// Prim: orders all the edges by using a MinPQ.
// Clearly, if the node is not in the tree yet then the edge to it will be minimum.
class LazyPrimMST
{
    public:
        LazyPrimMST(const WGraph& g)
        {
            marked.resize(g.V());
            visit(g, 0);

            while(!pq.empty())
            {
                const Edge e = pq.top();
                pq.pop();

                const size_t v = e.either(), w = e.other(v);
                if(marked[v] && marked[w]) continue;

                mst.push_back(e);
                
                if(!marked[v]) visit(g, v);
                if(!marked[w]) visit(g, w);
            }
        }

        std::vector<Edge> edges() const {
            return mst;
        }

        double weight() const {
            double w = 0.0;
            for(const auto& E : mst)
                w += E.weight();

            return w;
        }

    private:
        // Marked the vertex if its already on the tree.
        std::vector<bool> marked;
      
        // Tree itself.
        std::vector<Edge> mst;

        // MinPQ
        std::priority_queue<
            Edge,
            std::vector<Edge>,
            std::greater<Edge>
        > pq;

        // Visits all the edges and insert them into pq.
        void visit(const WGraph& g, const size_t v)
        {
            marked[v] = true;
            for(const Edge& e : g.adj_to(v))
                if(!marked[e.other(v)]) pq.push(e);
        }
};

#endif