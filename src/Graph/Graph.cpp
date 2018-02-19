#include "Graph/Graph.hpp"
Graph::Graph() {}
Graph::~Graph() {}
void Graph::AddNode(int id, int x, int y)
{
	m_nodes.push_back(std::make_shared<GraphNode>(id, x, y));
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

