#include <Pathfinder/DijkstraPathfinder.hpp>
#include <vector>
#include <Graph/Graph.hpp>
#include <queue>
#include <unordered_map>
#include <functional>

using Cost = int;
using NodeQueue = std::priority_queue<std::pair<Cost, GraphNodePtr>, std::vector<std::pair<Cost, GraphNodePtr>>, std::greater<>>;

Path DijkstraPathfinder::FindPath(const Graph& graph, const NodeIndex start, const NodeIndex goal) const
{
    std::unordered_map<GraphNodePtr, int> cost_so_far;
    std::unordered_map<GraphNodePtr, GraphNodePtr> came_from;
    NodeQueue nodes;

    auto start_node = graph.GetNode(start).lock();
    const auto end_node = graph.GetNode(goal).lock();

    nodes.emplace(0, start_node);
    came_from[start_node] = start_node;
    cost_so_far[start_node] = 0;

    while (!nodes.empty()) 
    {
        auto current = nodes.top().second;
        nodes.pop();

        if (current == end_node)
        {
            return GetPath(came_from, start_node, current);
        }

        auto neigbours = current->GetLinks();

        for (const auto& next : neigbours) {
            auto next_node = next.GetTo().lock();
            auto new_cost = cost_so_far[current] + next.GetWeight();
            if (!cost_so_far.count(next.GetTo().lock()) || new_cost < cost_so_far[next.GetTo().lock()]) {
                cost_so_far[next_node] = new_cost;
                came_from[next_node] = current;
                nodes.emplace(new_cost, next_node);
            }
        }
    }

    return {};
}

Path DijkstraPathfinder::GetPath(VisitedMap& came_from, const GraphNodePtr& start, GraphNodePtr& goal)
{
    Path result;

    result.push_back(goal->GetID());

    while (goal != start)
    {
        goal = came_from[goal];
        result.push_front(goal->GetID());
    }
    return result;
}