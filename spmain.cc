/*
    Shortest path test client
*/

#include "./include/dijkstra.hpp"
#include "./include/acyclicsp.hpp"
#include "./include/floydsp.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, char* argv[])
{
    std::ifstream in(argv[1]);
    WDigraph g(in);
    const size_t s = std::stoi(argv[2]);

    //---------------------------------------------------------------
    //  Floyd-Warshall tests... doesn't prints the weights tho
    // FloydSP f(g);

    // for(size_t t=0; t<g.V(); t++)
    // {
    //     std::cout << s << " to " << t;
    //     std::cout << " " << std::setw(4) << std::setprecision(3) << f.dist_to(s, t) << ": ";
    //     if(f.hasPathTo(s, t))
    //         for(const auto a : f.pathTo(s, t))
    //             std::cout << a << " ";

    //     std::cout << '\n';
    // }

    // std::cout << '\n';

    // in.close();
    // return 0;
    //---------------------------------------------------------------

    // Dijkstra sp(g, s);
    AcylicSP sp(g, s);

    for(size_t t=0; t<g.V(); t++)
    {
        std::cout << s << " to " << t;
        std::cout << " " << std::setw(4) << std::setprecision(3) << sp.dist_to(t) << ": ";
        if(sp.hasPathTo(t))
            for(const auto& E : sp.pathTo(t))
                std::cout << E.str() << "    ";

        std::cout << '\n';
    }

    return 0;
}