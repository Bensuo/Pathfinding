#include <Graph/DotParser.hpp>
#include <Pathfinder/DijkstraPathfinder.hpp>
#include <iostream>
#include <Pathfinder/AStarPathfinder.hpp>

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

    std::cout << "A* Pathfinder" << std::endl;
    PrintPath(AStarPathfinder{}, graph, 0, 63);
    std::cout << "Dijkstra Pathfinder" << std::endl;
    PrintPath(DijkstraPathfinder{}, graph, 0, 63);

    std::cin.get();
}