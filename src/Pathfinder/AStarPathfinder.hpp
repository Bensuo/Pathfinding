
#ifndef ASTARPATHFINDER_HPP
#define ASTARPATHFINDER_HPP

#include <Pathfinder/IPathfinder.hpp>
#include <memory>
#include <Graph/Graph.hpp>
#include <unordered_map>
#include <queue>

using VisitedMap = std::unordered_map<GraphNodePtr, GraphNodePtr>;

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
     * \param graph The graph you want to search
     * \param start The index of the start node
     * \param goal The index of the end node
     * \return If the path exits, a deque of node indices. If the path does not exist, an empty deque
     */
    Path FindPath(const Graph& graph, NodeIndex start, NodeIndex goal) const override;

private:
    /**
     * \brief Construct the final path from the start to the goal
     * \param came_from All the visited nodes in the graph
     * \param start The start node
     * \param goal The goal node
     * \return The final path from \p start to \p goal
     */
    Path GetPath(VisitedMap& came_from, const GraphNodePtr& start, GraphNodePtr& goal) const;

    /**
     * \brief Calculate the estimated distance between the a given node and the goal
     * \param current The current node
     * \param goal The goal node
     * \return The estimated distance between \p current and \p goal
     */
    int Heuristic(const GraphNodeWeakPtr& current, const GraphNodeWeakPtr& goal) const;
};

#endif // ASTARPATHFINDER_HPP