/*
    Kruskal minimum spanning tree implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __KRUSKAL_MST_HPP__
#define __KRUSKAL_MST_HPP__

#include "wgraph.hpp"
#include "unionfind.hpp"
#include <queue>

// Kruskal's algorithm finds edges to connect trees.
class KruskalMST
{
    public:
        KruskalMST(const WGraph& g)
        {
            // MinPQ
            std::priority_queue<
                Edge,
                std::vector<Edge>,
                std::greater<Edge>
            > pq;

            for(const Edge& e : g.edges())
                pq.push(e);

            // With Union-Find, we won't create cycles in the MST.
            UF uf(g.V());

            // Tree size should be g.V()-1 because its formed by the edges.
            // With V vertices, there will be V-1 edges in the MST.
            while(!pq.empty() && mst.size() < g.V()-1)
            {
                Edge e = pq.top();
                pq.pop();

                const size_t v = e.either(), w = e.other(v);
                if(uf.connected(v, w)) continue;
                uf.u(v, w);
                mst.push_back(e);
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
        // Tree itself.
        std::vector<Edge> mst;
};

#endif