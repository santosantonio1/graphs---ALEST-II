/*
    Directed and Weighted Edge class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef ___WEIGHTED_DIRECTED_EDGE_HPP__
#define ___WEIGHTED_DIRECTED_EDGE_HPP__

#include <sstream>

// Weighted directed edge class
class DEdge
{
    public:
        DEdge(const size_t from, 
              const size_t to, 
              const double w) : f(from), t(to), w(w)
        {}

        double weight() const {
            return w;
        }

        size_t from() const {
            return f;
        }

        size_t to() const {
            return t;
        }

        bool operator<(const DEdge& that) const {
            return w < that.weight();
        }

        bool operator<=(const DEdge& that) const {
            return w <= that.weight();
        }
        
        bool operator>(const DEdge& that) const {
            return w > that.weight();
        }

        bool operator>=(const DEdge& that) const {
            return w >= that.weight();
        }
        
        bool operator==(const DEdge& that) const {
            return w == that.weight();
        }

        bool operator!=(const DEdge& that) const {
            return w != that.weight();
        }

        std::string str() const {
            std::stringstream ss;
            ss << f << "->" << t << " " << w;
            return ss.str(); 
        }
    private:
        size_t f, t;
        double w;
};

#endif