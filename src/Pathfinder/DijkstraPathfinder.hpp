
#ifndef DIJKSTRAPATHFINDER_HPP
#define DIJKSTRAPATHFINDER_HPP

#include "IPathfinder.hpp"

class DijkstraPathfinder : public IPathfinder
{
public:
    DijkstraPathfinder() = default;
    virtual ~DijkstraPathfinder() = default;
    DijkstraPathfinder(const DijkstraPathfinder& pathfinder) = default;
    DijkstraPathfinder(DijkstraPathfinder&& pathfinder) = default;
    DijkstraPathfinder& operator=(const DijkstraPathfinder& pathfinder) = default;
    DijkstraPathfinder& operator=(DijkstraPathfinder&& pathfinder) = default;

    /**
    * \brief FindPath Attempt to find the shortest path between the nodes at \p start_index and \p end_index
    * \param graph The graph you want to search.
    * \param start_index The index of the start node.
    * \param end_index The index of the end node.
    * \return If the path exits, a deque of node indices. If the path does not exist, an empty deque.
    */
    PathResult FindPath(const Graph& graph, int start_index, int end_index) const override;
};

#endif // DIJKSTRAPATHFINDER_HPP
