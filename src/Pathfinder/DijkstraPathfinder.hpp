
#ifndef DIJKSTRAPATHFINDER_HPP
#define DIJKSTRAPATHFINDER_HPP

#include <Pathfinder/IPathfinder.hpp>
#include <unordered_map>
#include <queue>
#include <functional>

using Cost = int;
using CostMap = std::unordered_map<GraphNodePtr, Cost>;
using VisitedMap = std::unordered_map<GraphNodePtr, GraphNodePtr>;
using NodeQueue = std::priority_queue<std::pair<Cost, GraphNodePtr>, std::vector<std::pair<Cost, GraphNodePtr>>, std::greater<>>;

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
    * \param start The index of the start node.
    * \param goal The index of the end node.
    * \return If the path exits, a deque of node indices. If the path does not exist, an empty deque.
    */
    Path FindPath(const Graph& graph, int start, int goal) const override;
private:
    static Path GetPath(VisitedMap& came_from, const GraphNodePtr& start_node, GraphNodePtr& current);

};

#endif // DIJKSTRAPATHFINDER_HPP
