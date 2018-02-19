#include "AStarPathfinder.hpp"
#include "Graph/Graph.hpp"
#include <unordered_map>
#include <queue>
#include <functional>
#include <glm/glm.hpp>

typedef std::priority_queue<std::pair<int, std::shared_ptr<GraphNode>>, std::vector<std::pair<int, std::shared_ptr<GraphNode>>>, std::greater<std::pair<int, std::shared_ptr<GraphNode>>>> NodeQueue;
PathResult AStarPathfinder::FindPath(const Graph& graph, int start_index, int end_index) const
{
	PathResult result;
	std::unordered_map<std::shared_ptr<GraphNode>, int> cost_so_far;
	std::unordered_map<std::shared_ptr<GraphNode>, std::shared_ptr<GraphNode>> came_from;
	NodeQueue nodes;
	auto start_node = graph.GetNode(start_index).lock();
	auto end_node = graph.GetNode(end_index).lock();
	nodes.emplace(0, start_node);
	came_from[start_node] = start_node;
	cost_so_far[start_node] = 0;
	while (!nodes.empty())
	{
		auto current = nodes.top().second;
		nodes.pop();

		if (current == end_node)
		{
			break;
		}
		for (auto link : current->GetLinks())
		{
			auto next = link.GetTo().lock();
			int new_cost = cost_so_far[current] + link.GetWeight();
			if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
				int p = new_cost + Heuristic(next, end_node);
				nodes.emplace(p, next);
				came_from[next] = current;
			}
		}
	}
	auto current = end_node;
	result.push_back(current->GetID());
	while (current != start_node)
	{
		current = came_from[current];
		result.push_front(current->GetID());
	}
    return result;
}

int AStarPathfinder::Heuristic(std::weak_ptr<GraphNode> from, std::weak_ptr<GraphNode> goal) const
{
	return glm::distance(from.lock()->GetPosition(), goal.lock()->GetPosition());
}
