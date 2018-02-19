#include "Graph/Graph.hpp"

void Graph::AddNode(int id, const glm::vec2& pos)
{
	m_nodes.push_back(std::make_shared<GraphNode>(id, pos));
}

void Graph::AddSingleLink(int from, int to, int weight)
{
	auto f = m_nodes[from];
	auto t = m_nodes[to];
	f->AddLink(GraphLink(f, t, weight));
}

void Graph::AddDoubleLink(int from, int to, int weight)
{
	AddSingleLink(from, to, weight);
	AddSingleLink(to, from, weight);
}

GraphNodePtr Graph::GetNode(const int node_index) const
{
    return m_nodes[node_index];
}

