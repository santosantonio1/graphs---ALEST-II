/*
    Minimum spanning tree test client
*/

#include "./include/lazyprim.hpp"
#include "./include/prim.hpp"
#include "./include/kruskal.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    std::ifstream in(argv[1]);

    WGraph g(in);

    // LazyPrimMST mst(g);
    // PrimMST mst(g);
    KruskalMST mst(g);

    for(const auto& e : mst.edges())
        std::cout << e.str() << '\n';


    std::cout << mst.weight() << '\n';

    in.close();

    return 0;
}