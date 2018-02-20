#include <Graph/DotParser.hpp>
#include <Pathfinder/DijkstraPathfinder.hpp>
#include <iostream>
#include <sstream>
#include <Pathfinder/AStarPathfinder.hpp>
#include <Timer/Timer.hpp>

void PrintPath(const IPathfinder& pathfinder, const Graph& graph, int start_node, int end_node)
{
    const Timer timer(true);
    auto path = pathfinder.FindPath(graph, start_node, end_node);

    std::cout << "Time: " << timer << " ms" << std::endl;
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

int GetInt(const int minimum = std::numeric_limits<int>::min(), const int maximum = std::numeric_limits<int>::max())
{
    while (std::cin)
    {
        std::cout << "Enter a valid integer between " << minimum << " and " << maximum << std::endl;

        std::string line;
        std::getline(std::cin, line);

        std::stringstream linestream(line);

        //if you can't insert the value to an integer, ask for input again
        int value;
        if (!(linestream >> value)) 
        {
            continue;
        }

        //if there are characters in the line then ask for input again
        char x;
        if (linestream >> x)
        {
            continue;
        }

        //if the value entered exceeds accepted bounds then ask for input again
        if (value > maximum || value < minimum) 
        {
            continue;
        }

        return value;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    const std::string dotfile = "graph.dot";

    DotParser parser;
    std::cout << "Parsing graph file: " << dotfile << std::endl;
    const auto graph = parser.Read(dotfile);
    const auto graph_size = graph.Size();
    std::cout << "Graph size: " << graph_size << " nodes" << std::endl;
    std::cout << std::endl;

    std::cout << "Start node:" << std::endl;
    const auto start_node = GetInt(0, graph_size - 1);
    std::cout << std::endl;

    std::cout << "End node: " << std::endl;
    const auto end_node = GetInt(0, graph_size - 1);
    std::cout << std::endl;

    std::cout << "A* Pathfinder results:" << std::endl;
    PrintPath(AStarPathfinder{}, graph, start_node, end_node);
    std::cout << std::endl;

    std::cout << "Dijkstra Pathfinder results:" << std::endl;
    PrintPath(DijkstraPathfinder{}, graph, start_node, end_node);
    std::cout << std::endl;

    std::cin.get();
}