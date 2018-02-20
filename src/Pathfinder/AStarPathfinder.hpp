
#ifndef ASTARPATHFINDER_HPP
#define ASTARPATHFINDER_HPP

#include <Pathfinder/IPathfinder.hpp>
#include <memory>
#include <Graph/Graph.hpp>

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
    * \brief FindPath Attempt to find the shortest path between the nodes at \p start and \p goal
    * \param graph The graph you want to search.
    * \param start The index of the start node.
    * \param goal The index of the end node.
    * \return If the path exits, a deque of node indices. If the path does not exist, an empty deque.
    */
    Path FindPath(const Graph& graph, int start, int goal) const override;

private:
    static Path GetPath(VisitedMap& came_from, const GraphNodePtr& start_node, GraphNodePtr& current);

    int Heuristic(std::weak_ptr<GraphNode> from, std::weak_ptr<GraphNode> goal) const;
};

#endif // ASTARPATHFINDER_HPP
