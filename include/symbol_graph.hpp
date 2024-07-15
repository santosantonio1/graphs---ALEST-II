/*
    Symbol Graph (Oracle of Bacon) class implementation
    author: Antônio dos Santos
    github: @santosantonio1
    version: 05/07/2024

    Based on Algorithms 4th edition, by Robert Sedgewick and Kevin Wayne
*/

#ifndef __SYMBOL_GRAPH_HPP__
#define __SYMBOL_GRAPH_HPP__

#include "graph.hpp"
// #include <ranges>
#include <unordered_map>
#include <algorithm>

// Symbol Graph class
class SymbolGraph
{
    public:
        SymbolGraph(const std::string filename,
                    const std::string delimiter)
        {
            std::ifstream in(filename);
            std::string line;
    
            //------------------------------------------------------------------
            //  For the curious people... make sure to have gcc 14.1+ version
            // and use an appropriate makefile. Also, include <ranges>
            //
            // Maps keys in a hashmap
            // while(std::getline(in, line))
            // {
            //     auto split = std::views::split(line, delimiter);
            //     for(const auto& s : split)
            //     {
            //         const std::string tmp{s.begin(), s.end()};
            //         if(!idx.contains(tmp)) {
            //             idx.insert(std::pair{tmp, idx.size()});
            //         }
            //     }
            // }
    
            // Maps keys using a hashmap
            while(std::getline(in, line))
            {   
                // First split the input...
                const auto split = split_input(line, delimiter);
    
                for(const std::string s : split)
                {
                    if(idx.find(s) == idx.end()) {
                        idx.insert(
                            std::pair<std::string, size_t>{s, idx.size()}
                        );
                    }
                }
            }
    
            in.close();
    
            // Create keys vector
            keys.resize(idx.size());
            for(const auto& p : idx) {
                keys[idx.at(p.first)] = p.first;
            }
    
            g = new Graph(idx.size());
            in.open(filename);
    
            bool title;
            size_t tidx;
    
            //-----------------------------------------------        
            //  Again, just for curiosity...
            //
            // Create connections in the graph.
            // while(std::getline(in, line))
            // {
            //     title = true;
            //     auto split = std::views::split(line, delimiter);
    
            //     for(const auto& s : split)
            //     {
            //         // First name is always a title.
            //         if(title) {
            //             tidx = idx.at(std::string{s.begin(), s.end()});
            //             title = false;
            //         } else {
            //             // Connect performers to movies.
            //             g->addEdge(tidx, idx.at(std::string{s.begin(), s.end()}));
            //         }
            //     }
            // }
    
            // Create connections in the graph
            while(std::getline(in, line))
            {
                const auto split = split_input(line, delimiter);
    
                tidx = idx.at(split[0]);
    
                for(size_t i=1; i<split.size(); i++)
                {
                    g->addEdge(tidx, idx.at(split[i]));
                }
            }
    
            in.close();
        }
    
        ~SymbolGraph()
        {
            delete g;
        }
    
        bool contains(const std::string s) const {
            return idx.find(s) != idx.end();
        }
    
        size_t index(const std::string s) const {
            return idx.at(s);
        }
    
        std::string name(const size_t v) const {
            return keys[v];
        }
    
        const Graph* G() {
            return g;
        }

    private:
        // Keys table
        std::unordered_map<std::string, size_t> idx;
        std::vector<std::string> keys;
        Graph* g;

        // Splits the input
        std::vector<std::string> split_input(const std::string input,
                                             const std::string delimiter) const 
        {
            std::vector<std::string> split;
            size_t beg = 0, end = 0;
            while((end = input.find(delimiter, beg)) != std::string::npos)
            {   
                split.push_back(
                    input.substr(
                        beg,
                        end - beg
                    )
                );
                beg = end + 1;
            }
            return split;
        }

};

#endif
