#include "AStarPathfinder.hpp"
#include "Graph/Graph.hpp"
#include <unordered_map>
#include <queue>
#include <functional>
#include <glm/glm.hpp>

using NodeQueue = std::priority_queue<std::pair<int, GraphNodePtr>, std::vector<std::pair<int, GraphNodePtr>>, std::greater<>>;

Path AStarPathfinder::FindPath(const Graph& graph, const int start, const int goal) const
{
	Path result;

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

Path AStarPathfinder::GetPath(VisitedMap& came_from, const GraphNodePtr& start_node, GraphNodePtr& current)
{
    Path result;

    result.push_back(current->GetID());

    while (current != start_node)
    {
        current = came_from[current];
        result.push_front(current->GetID());
    }
    return result;
}

int AStarPathfinder::Heuristic(const GraphNodeWeakPtr& from, const GraphNodeWeakPtr& goal) const
{
	return distance(from.lock()->GetPosition(), goal.lock()->GetPosition());
}
