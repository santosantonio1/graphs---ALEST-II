/*
    Connected Components test client
*/

#include "./include/cc.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{   
    std::ifstream in(argv[1]);

    Graph g(in);
    CC cc(g);

    const size_t M = cc.count();

    std::vector<std::forward_list<size_t>> components(g.V());

    for(size_t v=0; v<g.V(); v++)
        components[cc.id(v)].push_front(v);

    for(size_t i=0; i<g.V(); i++)
    {
        for(const size_t v : components[i])
            std::cout << v << " ";

        if(!components[i].empty()) std::cout << '\n';
    }

    in.close();

    return 0;
}