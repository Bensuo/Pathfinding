#include "IDAStarPathfinder.hpp"
#include <functional>
#include <queue>
#include <stack>
#include <glm/detail/func_geometric.inl>

using NodeQueue = std::priority_queue<std::pair<int, GraphNodePtr>, std::vector<std::pair<int, GraphNodePtr>>, std::greater<>>;
Path IDAStarPathfinder::FindPath(const Graph &graph, int start, int goal) const
{
	Path result;
	int threshold = 0;
	bool goal_found = false;
	std::unordered_map<GraphNodePtr, int> cost_so_far;
	std::unordered_map<GraphNodePtr, GraphNodePtr> came_from;
	

	auto start_node = graph.GetNode(start).lock();
	const auto end_node = graph.GetNode(goal).lock();
	
	while (!goal_found)
	{
		came_from.clear();
		cost_so_far.clear();
		NodeQueue nodes;
		nodes.emplace(0, start_node);
		came_from[start_node] = start_node;
		cost_so_far[start_node] = 0;
		while (!nodes.empty())
		{
			const auto current = nodes.top().second;
			nodes.pop();
			int min = INT_MAX;
			if (cost_so_far[current] + Heuristic(current, end_node) > threshold)
			{
				threshold = cost_so_far[current] + Heuristic(current, end_node);
				break;
			}
			if (current == end_node)
			{
				goal_found = true;
				break;
			}
			
			for (const auto& link : current->GetLinks())
			{
				auto next = link.GetTo().lock();
				const auto new_cost = cost_so_far[current] + link.GetWeight();
				if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
				{
					cost_so_far[next] = new_cost;
					int temp = new_cost + Heuristic(next, end_node);
					nodes.emplace(temp,next);
					came_from[next] = current;
					if (temp<min)
					{
						min = temp;
					}
				}
			}
			if (min > threshold)
			{
				threshold = min;
				break;
			}
		}
	}
	auto current = end_node;
	return GetPath(came_from, start_node, current);
}

Path IDAStarPathfinder::GetPath(VisitedMap &came_from, const GraphNodePtr &start_node, GraphNodePtr &current)
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
int IDAStarPathfinder::Heuristic(const GraphNodeWeakPtr &from, const GraphNodeWeakPtr &goal) const
{
	return distance(from.lock()->GetPosition(), goal.lock()->GetPosition());
}
