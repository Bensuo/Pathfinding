
#ifndef IPATHFINDER_HPP
#define IPATHFINDER_HPP
#include <deque>

class Graph;
using PathResult = std::deque<int>;

class IPathfinder
{
public:
    IPathfinder() = default;
    virtual ~IPathfinder() = default;
    IPathfinder(const IPathfinder& pathfinder) = default;
    IPathfinder(IPathfinder&& pathfinder) = default;
    IPathfinder& operator=(const IPathfinder& pathfinder) = default;
    IPathfinder& operator=(IPathfinder&& pathfinder) = default;

    /**
     * \brief FindPath Attempt to find the shortest path between the nodes at \p start_index and \p end_index
     * \param graph The graph you want to search.
     * \param start_index The index of the start node.
     * \param end_index The index of the end node.
     * \return If the path exits, a deque of node indices. If the path does not exist, an empty deque.
     */
    virtual PathResult FindPath(const Graph& graph, int start_index, int end_index) = 0;
};

#endif // IPATHFINDER_HPP
