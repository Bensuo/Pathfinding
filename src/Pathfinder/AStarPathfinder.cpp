#include "AStarPathfinder.hpp"
#include "Graph/Graph.hpp"
#include <unordered_map>
#include <queue>
#include <functional>
#include <glm/glm.hpp>

using Cost = int;
using NodeQueue = std::priority_queue<std::pair<Cost, GraphNodePtr>, std::vector<std::pair<Cost, GraphNodePtr>>, std::greater<>>;

Path AStarPathfinder::FindPath(const Graph& graph, const NodeIndex start, const NodeIndex goal) const
{
	Path result;

	std::unordered_map<GraphNodePtr, Cost> cost_so_far;
	std::unordered_map<GraphNodePtr, GraphNodePtr> came_from;
	NodeQueue nodes;

	auto start_node = graph.GetNode(start).lock();
    const auto end_node = graph.GetNode(goal).lock();

	nodes.emplace(0, start_node);
	came_from[start_node] = start_node;
	cost_so_far[start_node] = 0;

	while (!nodes.empty())
	{
	    const auto current = nodes.top().second;
		nodes.pop();

		if (current == end_node)
		{
			break;
		}
		for (const auto& link : current->GetLinks())
		{
			auto next = link.GetTo().lock();
		    const auto new_cost = cost_so_far[current] + link.GetWeight();
			if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
			    auto p = new_cost + Heuristic(next, end_node);
				nodes.emplace(p, next);
				came_from[next] = current;
			}
		}
	}

	auto current = end_node;
    return GetPath(came_from, start_node, current);
}

Path AStarPathfinder::GetPath(VisitedMap& came_from, const GraphNodePtr& start, GraphNodePtr& goal) const
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

int AStarPathfinder::Heuristic(const GraphNodeWeakPtr& current, const GraphNodeWeakPtr& goal) const
{
	return distance(current.lock()->GetPosition(), goal.lock()->GetPosition());
}