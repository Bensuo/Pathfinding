
#ifndef DIJKSTRAPATHFINDER_HPP
#define DIJKSTRAPATHFINDER_HPP

#include <Pathfinder/IPathfinder.hpp>
#include <unordered_map>
#include <queue>

using VisitedMap = std::unordered_map<GraphNodePtr, GraphNodePtr>;

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
    static Path GetPath(VisitedMap& came_from, const GraphNodePtr& start, GraphNodePtr& goal);

};

#endif // DIJKSTRAPATHFINDER_HPP
