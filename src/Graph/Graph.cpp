#include "Graph/Graph.hpp"

void Graph::AddNode(int id, const glm::vec2& pos)
{
    m_nodes.push_back(std::make_shared<GraphNode>(id, pos));
}

void Graph::AddSingleLink(const int from, const int to, const int weight)
{
    auto f = m_nodes[from];
    const auto t = m_nodes[to];
    f->AddLink(GraphLink(f, t, weight));
}

void Graph::AddDoubleLink(const int from, const int to, const int weight)
{
    AddSingleLink(from, to, weight);
    AddSingleLink(to, from, weight);
}

GraphNodeWeakPtr Graph::GetNode(const int node_index) const
{
    return m_nodes[node_index];
}

std::size_t Graph::Size() const
{
    return m_nodes.size();
}

