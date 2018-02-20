#include "Graph/Graph.hpp"

void Graph::AddNode(const NodeIndex id, const glm::vec2& pos)
{
    m_nodes.push_back(std::make_shared<GraphNode>(id, pos));
}

void Graph::AddSingleLink(const NodeIndex from, const NodeIndex to, const Weight weight)
{
    auto f = m_nodes[from];
    const auto t = m_nodes[to];
    f->AddLink(GraphLink(f, t, weight));
}

void Graph::AddDoubleLink(const NodeIndex from, const NodeIndex to, const Weight weight)
{
    AddSingleLink(from, to, weight);
    AddSingleLink(to, from, weight);
}

GraphNodeWeakPtr Graph::GetNode(const NodeIndex node_index) const
{
    return m_nodes[node_index];
}

std::size_t Graph::Size() const
{
    return m_nodes.size();
}

