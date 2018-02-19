
#ifndef ASTARPATHFINDER_HPP
#define ASTARPATHFINDER_HPP

#include "IPathfinder.hpp"
#include <memory>
#include "Graph/Graph.hpp"

class AStarPathfinder : public IPathfinder
{
public:
    AStarPathfinder() = default;
    virtual ~AStarPathfinder() = default;
    AStarPathfinder(const AStarPathfinder& pathfinder) = default;
    AStarPathfinder(AStarPathfinder&& pathfinder) = default;
    AStarPathfinder& operator=(const AStarPathfinder& pathfinder) = default;
    AStarPathfinder& operator=(AStarPathfinder&& pathfinder) = default;

    /**
    * \brief FindPath Attempt to find the shortest path between the nodes at \p start_index and \p end_index
    * \param graph The graph you want to search.
    * \param start_index The index of the start node.
    * \param end_index The index of the end node.
    * \return If the path exits, a deque of node indices. If the path does not exist, an empty deque.
    */
    PathResult FindPath(const Graph& graph, int start_index, int end_index) const override;
private:
	int Heuristic(std::weak_ptr<GraphNode> from, std::weak_ptr<GraphNode> goal) const;
};

#endif // ASTARPATHFINDER_HPP
