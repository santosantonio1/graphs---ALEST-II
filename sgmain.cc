/*
    Symbol Graph (Oracle of Bacon) test client
*/

#include "./include/symbol_graph.hpp"
#include "./include/bfs_path.hpp"

#include <iostream>
#include <algorithm>

int main(int argc, char* argv[])
{
    SymbolGraph sg(argv[1], argv[2]);

    Graph g = *sg.G();

    std::string source = argv[3];

    if(!sg.contains(source)) {
        std::cout << source << " not in database.\n";
        return 0;
    }

    size_t s = sg.index(source);
    BFS_PATHS bfs(g, s);

    std::string line;

    while(getline(std::cin, line))
    {
        if(sg.contains(line))
        {
            size_t t = sg.index(line);
            if(bfs.hasPathTo(t)) {
                for(const auto v : bfs.pathTo(t))
                    std::cout << "      " << sg.name(v) << '\n';
            } else {
                std::cout << "Not connected.\n";
            }   
        }
        else std::cout << "Not in database.\n";
    }

    return 0;
}