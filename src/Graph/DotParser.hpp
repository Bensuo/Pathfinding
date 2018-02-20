#pragma once
#include <string>
#include <Graph/Graph.hpp>

class DotParser
{
public:
    DotParser();
    ~DotParser();

    Graph Read(const std::string& filename) const;
};

