/*
    Search test client
*/

#include <iostream>
#include <fstream>

#include "./include/graph.hpp"
#include "./include/dfs.hpp"

int main(int argc, char* argv[])
{
    std::ifstream in(argv[1]);

    Graph g(in);
    const size_t s = std::stoi(argv[2]);

    DFS search(g, s);

    for(size_t i=0; i<g.V(); i++)
        if(search.isMarked(i))
            std::cout << i << " ";
    
    std::cout << '\n';

    if(search.count() != g.V())
        std::cout << "NOT ";

    std::cout << "connected\n";

    in.close();

    return 0;
}