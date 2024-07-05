/*
    Union Find class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __UNION_FIND_HPP__
#define __UNION_FIND_HPP__

#include <vector>

class UF
{
    public:
        UF(const size_t n)
        {
            c = n;
            parent.resize(n);
            rank.resize(n);
            for(size_t i=0; i<n; i++) {
                parent[i] = i;

                // All sets start with 0 height.
                rank[i] = 0;
            }
        }

        // While finding, fix the parents.
        size_t find(size_t p)
        {
            // 
            while(p != parent[p]) {
                parent[p] = parent[parent[p]];
                p = parent[p];
            }

            return p;
        }

        // Number of disjoint sets.
        size_t count() const {
            return c;
        }
    
        // Two sets are connected if and only if they have the same root.
        bool connected(size_t p, size_t q) {
            return find(p) == find(q);
        }

        // UNION
        // note: union word is reserved in c++
        void u(size_t p, size_t q)
        {
            // This way, we increase one's rank by 1 or 0.
            size_t rootP = find(p);
            size_t rootQ = find(q);

            // Same set -> do nothing
            if(rootP == rootQ) return;

            // rank(set) <- max(set1, set2) + 1
            if(rank[rootP] < rank[rootQ]) 
                parent[rootP] = rootQ;
            else if(rank[rootP] > rank[rootQ]) 
                    parent[rootQ] = rootP;
            else {
                parent[rootQ] = rootP;
                rank[rootP]++;
            }

            // Decrease the number of disjoint sets.
            c--;
        }


    private:

        // parent: root of the set that contains i.
        // rank: "height" of the set.
        std::vector<size_t> parent, rank;
        
        // Number of disjoint sets.
        size_t c;
};

#endif