#include <Graph/DotParser.hpp>
#include <Pathfinder/DijkstraPathfinder.hpp>
#include <iostream>
#include <sstream>
#include <Pathfinder/AStarPathfinder.hpp>
#include <Timer/Timer.hpp>

void PrintPath(const IPathfinder& pathfinder, const Graph& graph, int start_node, int end_node)
{
	Timer timer(true);
    auto path = pathfinder.FindPath(graph, start_node, end_node);

	std::cout << "Time (milliseconds): " << timer << " ms" << std::endl;
	std::cout << "Path: ";
    while (!path.empty())
    {
		std::cout << path.front();
        path.pop_front();

		if (!path.empty())
		{
			std::cout << ",";
		}
		else
		{
			std::cout << std::endl;
		}
    }
}

int GetInput()
{
	auto result = 0;

	bool invalid_input = true;
	while (invalid_input)
	{
		std::string line;
		std::getline(std::cin, line);
		std::istringstream is(line);
		char null_character = '\0';
		invalid_input = (!(is >> result) || (is >> std::ws && is.get(null_character)));
	}

	return result;
}

int main(int argc, char* argv[])
{
	std::string dotfile = "graph.dot";

	DotParser parser;
	std::cout << "Parsing graph file: " << dotfile << std::endl;
	std::cout << std::endl;
	const auto graph = parser.Read(dotfile);

	std::cout << "Enter start node:" << std::endl;
	int start_node = GetInput();
	std::cout << std::endl;

	std::cout << "Enter end node:" << std::endl;
	int end_node = GetInput();
	std::cout << std::endl;

    std::cout << "A* Pathfinder results:" << std::endl;
    PrintPath(AStarPathfinder{}, graph, start_node, end_node);
	std::cout << std::endl;

    std::cout << "Dijkstra Pathfinder results:" << std::endl;
    PrintPath(DijkstraPathfinder{}, graph, start_node, end_node);
	std::cout << std::endl;

    std::cin.get();
}