
#ifndef IPATHFINDER_HPP
#define IPATHFINDER_HPP

#include <deque>
#include <Graph/Graph.hpp>

using Path = std::deque<NodeIndex>;

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
     * \brief FindPath Attempt to find the shortest path between the nodes at \p start and \p goal
     * \param graph The graph you want to search
     * \param start The index of the start node
     * \param goal The index of the end node
     * \return If the path exits, a deque of node indices. If the path does not exist, an empty deque
     */
    virtual Path FindPath(const Graph& graph, NodeIndex start, NodeIndex goal) const = 0;
};

#endif // IPATHFINDER_HPP
