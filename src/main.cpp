#include "Graph\DotParser.hpp"
#include "Pathfinder/AStarPathfinder.hpp"
#include "Pathfinder/DijkstraPathfinder.hpp"
#include <iostream>

void PrintPath(const IPathfinder& pathfinder, const Graph& graph, int start_node, int end_node)
{
    auto path = pathfinder.FindPath(graph, start_node, end_node);

    while (!path.empty())
    {
        std::cout << path.front() << std::endl;
        path.pop_front();
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	DotParser parser;
	const auto graph = parser.Read("graph.dot");

    PrintPath(AStarPathfinder{}, graph, 0, 63);
    //PrintPath(DijkstraPathfinder{}, graph, 0, 10);

    std::cin.get();
}