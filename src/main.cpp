#include <Graph/DotParser.hpp>
#include <Pathfinder/DijkstraPathfinder.hpp>
#include <iostream>
#include <sstream>
#include <Pathfinder/AStarPathfinder.hpp>
#include <Timer/Timer.hpp>
#include "Pathfinder/IDAStarPathfinder.hpp"

/**
 * \brief Use \p pathfinder to find the shortest path in \p graph between nodes \p start and \p goal
 * \param pathfinder The pathfinder you want to use
 * \param graph The graph you want to search
 * \param start The index of the starting position
 * \param goal The index of the goal position
 */
void TestPathfinder(const IPathfinder& pathfinder, const Graph& graph, const NodeIndex start, const NodeIndex goal)
{
    const Timer timer(true);
    auto path = pathfinder.FindPath(graph, start, goal);

    // print time taken to execute the pathfinding algorithm
    std::cout << "Time: " << timer << " ms" << std::endl;

    // pop every nodeindex from the deque and print
    std::cout << "Path: ";
    while (!path.empty())
    {
        std::cout << path.front();
        path.pop_front();

        // take a comman between each nodeindex until the last element
        if (!path.empty())
        {
            std::cout << ",";
        }
        // take a new line once we reach the last element
        else
        {
            std::cout << std::endl;
        }
    }
}

/**
 * \brief Get a valid integer value from the standard input stream
 * \param minimum The minimum integer value allowed
 * \param maximum The maximum integer value allowed
 * \return A validated integer
 */
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
    const auto start = GetInt(0, graph_size - 1);
    std::cout << std::endl;

    std::cout << "Goal node: " << std::endl;
    const auto goal = GetInt(0, graph_size - 1);
    std::cout << std::endl;

    std::cout << "Dijkstra Pathfinder results:" << std::endl;
    TestPathfinder(DijkstraPathfinder{}, graph, start, goal);
    std::cout << std::endl;

    std::cout << "A* Pathfinder results:" << std::endl;
    TestPathfinder(AStarPathfinder{}, graph, start, goal);
    std::cout << std::endl;

	std::cout << "IDA* Pathfinder results:" << std::endl;
	TestPathfinder(IDAStarPathfinder{}, graph, start, goal);
	std::cout << std::endl;

    std::cin.get();
}