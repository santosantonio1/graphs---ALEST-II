/*
    Undirected and unweighted edge implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __WEIGHTED_UNDIRECTED_EDGE_HPP__
#define __WEIGHTED_UNDIRECTED_EDGE_HPP__

#include <sstream>

// Weighted and undirected edge
class Edge
{
    public:
        Edge(const size_t v, 
              const size_t u, 
              const double w)
        {
            this->v = v;
            this->u = u;
            this->w = w;
        }

        double weight() const {
            return w;
        }

        size_t either() const {
            return v;
        }

        size_t other(const size_t vertex) const {
            return (vertex == v) ? u : v;
        }

        bool operator<(const Edge& that) const {
            return w < that.weight();
        }

        bool operator<=(const Edge& that) const {
            return w <= that.weight();
        }
        
        bool operator>(const Edge& that) const {
            return w > that.weight();
        }

        bool operator>=(const Edge& that) const {
            return w >= that.weight();
        }
        
        bool operator==(const Edge& that) const {
            return w == that.weight();
        }

        bool operator!=(const Edge& that) const {
            return w != that.weight();
        }

        std::string str() const {
            std::stringstream ss;
            ss << v << "-" << u << ' '<< w;
            return ss.str();  
        }
    private:
        size_t v, u;
        double w;
};

#endif