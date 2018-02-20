#ifndef IDASTAR_PATHFINDER_HPP
#define IDASTAR_PATHFINDER_HPP
#include "IPathfinder.hpp"
#include <unordered_map>
using VisitedMap = std::unordered_map<GraphNodePtr, GraphNodePtr>;
class IDAStarPathfinder : public IPathfinder
{
public:
	IDAStarPathfinder() = default;
	virtual ~IDAStarPathfinder() = default;
	IDAStarPathfinder(const IDAStarPathfinder& pathfinder) = default;
	IDAStarPathfinder(IDAStarPathfinder&& pathfinder) = default;
	IDAStarPathfinder& operator=(const IDAStarPathfinder& pathfinder) = default;
	IDAStarPathfinder& operator=(IDAStarPathfinder&& pathfinder) = default;

	/**
	* \brief FindPath Attempt to find the shortest path between the nodes at \p start and \p goal
	* \param graph The graph you want to search.
	* \param start The index of the start node.
	* \param goal The index of the end node.
	* \return If the path exits, a deque of node indices. If the path does not exist, an empty deque.
	*/
	Path FindPath(const Graph &graph, int start, int goal) const override;

private:
	static Path GetPath(VisitedMap& came_from, const GraphNodePtr& start_node, GraphNodePtr& current);
	int Heuristic(const GraphNodeWeakPtr& from, const GraphNodeWeakPtr& goal) const;
};

#endif // IDASTAR_PATHFINDER_HPP
