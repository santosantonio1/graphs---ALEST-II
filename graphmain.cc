/*
    Graph test client
*/

#include "./include/graph.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    std::ifstream in(argv[1]);

    Graph g(in);

    std::cout << g.toString() << std::endl;

    in.close();

    return 0;
}