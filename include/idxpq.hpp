/*
    Index generic priority queue implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __INDEX_PRIORITY_QUEUE_HPP__
#define __INDEX_PRIORITY_QUEUE_HPP__

#include <vector>
#include <sstream>

// By default, behaves like a MinPQ
template<
    typename Key, 
    typename Compare = std::greater<Key>
> class IndexPQ
    {
        public:
        IndexPQ(const size_t nmax)
        {
            N = 0;
            keys.resize(nmax+1);
            heap.resize(nmax+1);
            idx.resize(nmax+1);

            std::fill(idx.begin(), idx.end(), 0);            
        }
        
        void push(const size_t k, const Key& key)
        {
            if(contains(k)) return;

            idx[k] = ++N;
            heap[N] = k;
            keys[k] = key;
            swim(N);
        }

        size_t pop()
        {
            if(N==0) return 0;
            const size_t t = heap[1];
            swap(1, N--);
            sink(1);

            idx[t] = 0;

            return t;
        }

        void change(const size_t k, const Key& key)
        {
            if(!contains(k)) return;

            keys[k] = key;
            swim(idx[k]);
            sink(idx[k]);
        }

        void increaseKey(const size_t i, const Key& key)
        {
            if(
                !contains(i)    ||
                cmp(keys[i], key)
            ) return;

            keys[i] = key;
            sink(idx[i]);
        }

        void decreaseKey(const size_t i, const Key& key)
        {
            if(
                !contains(i)    ||
                !cmp(keys[i], key)
            ) return;

            keys[i] = key;
            swim(idx[i]);
        }

        bool contains(const size_t k) const {
            return idx[k] != 0;
        }

        bool empty() const {
            return N == 0;
        }

        size_t size() const {
            return N;
        }

        size_t top() const {
            return heap[1];
        }

        Key topKey() const {
            return keys[heap[1]];
        }

        auto begin() const {
            return ++heap.begin();
        }

        auto cbegin() const {
            return ++heap.cbegin();
        }

        auto rbegin() const {
            return heap.rbegin();
        }

        auto end() const {
            return heap.end();
        }

        auto cend() const{
            return heap.cend();
        }

        auto rend() const{
            return ++heap.cend();
        }

        std::string str_k() const {
            std::stringstream ss;
            for(const Key& k : keys)
                ss << k << " ";

            ss << '\n';
            return ss.str();
        }

        size_t operations() const {
            return op;
        }

        private:
            size_t N;
            std::vector<size_t> heap, idx;
            std::vector<Key> keys;

            size_t op = 0;

            bool cmp(const size_t i, const size_t j) const {
                return Compare{}(keys[heap[i]], keys[heap[j]]);
            }

            void swap(const size_t i, const size_t j)
            {
                size_t tmp = heap[i];
                    heap[i] = heap[j];
                    heap[j] = tmp;

                idx[heap[i]] = i;
                idx[heap[j]] = j;
            }

            void swim(size_t k)
            {
                while(k > 1 && cmp(k/2, k)) 
                {
                    op++;
                    swap(k, k/2);
                    k = k/2;
                }
            }

            void sink(size_t k)
            {
                while(2*k <= N)
                {
                    op++;
                    size_t j = 2*k;
                    if(j<N && cmp(j, j+1)) j++;
                    if(!cmp(k, j)) break;

                    swap(k, j);
                    k = j;
                }
            }
    };

#endif