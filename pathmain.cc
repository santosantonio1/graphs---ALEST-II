/*
    Search paths test client
*/

#include <iostream>
#include <fstream>

#include "./include/graph.hpp"
#include "./include/bfs_path.hpp"
#include "./include/dfs_path.hpp"

int main(int argc, char* argv[])
{
    std::ifstream in(argv[1]);

    Graph g(in);
    const size_t s = std::stoi(argv[2]);

    // DFS_PATHS search(g, s);
    BFS_PATHS search(g, s);

    for(size_t i=0; i<g.V(); i++)
    {
        std::cout << s << " to " << i << ": ";
        if(search.hasPathTo(i)) {
            for(const size_t x : search.pathTo(i))
                if(x == s)  std::cout << x;
                else    std::cout << "-" << x;
        }
        std::cout << '\n';
    }

    in.close();

    return 0;
}