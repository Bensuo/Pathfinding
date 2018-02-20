#include <Pathfinder/DijkstraPathfinder.hpp>
#include <vector>
#include <Graph/Graph.hpp>
#include <queue>
#include <unordered_map>
#include <functional>

Path DijkstraPathfinder::GeneratePath(int start, std::unordered_map<int, int> came_from, int& current)
{
    Path path;
    path.push_front(current);
    while (current != start) {
        current = came_from[current];
        path.push_front(current);
    }
    return path;
}

Path DijkstraPathfinder::FindPath(const Graph& graph, int start, int goal) const
{
    using index = int;
    using distance = int;
    using priority_element = std::pair<distance, index>;

    std::unordered_map<index, index> came_from;
    std::unordered_map<index, distance> cost_so_far;
    std::priority_queue<priority_element, std::vector<priority_element>, std::greater<>> frontier;

    frontier.emplace(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {

        auto current = frontier.top().second;
        frontier.pop();

        if (current == goal)
        {
            return GeneratePath(start, came_from, current);
        }

        auto neigbours = graph.GetNode(current).lock()->GetLinks();

        for (const auto& next : neigbours) {
            auto next_index = next.GetTo().lock()->GetID();
            auto new_cost = cost_so_far[current] + next.GetWeight();
            if (!cost_so_far.count(next_index) || new_cost < cost_so_far[next_index]) {
                cost_so_far[next_index] = new_cost;
                came_from[next_index] = current;
                frontier.emplace(new_cost, next_index);
            }
        }
    }

    return {};
}
