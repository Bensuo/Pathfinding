#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <memory>
#include <glm/vec2.hpp>

class GraphNode;
using NodeIndex = int;
using Weight = int;
using GraphNodeWeakPtr = std::weak_ptr<GraphNode>;
using GraphNodePtr = std::shared_ptr<GraphNode>;

class GraphLink
{
public:
    GraphLink(const GraphNodeWeakPtr& from, const GraphNodeWeakPtr& to, Weight weight)
        : m_from(from),
        m_to(to),
        m_weight(weight)
    {

    }

    std::weak_ptr<GraphNode> GetFrom() const
    {
        return m_from;
    }

    std::weak_ptr<GraphNode> GetTo() const
    {
        return m_to;
    }

    Weight GetWeight() const
    {
        return m_weight;
    }
private:
    GraphNodeWeakPtr m_from;
    GraphNodeWeakPtr m_to;
    Weight m_weight;
};

class GraphNode
{
public:
    GraphNode(NodeIndex id, const glm::vec2& pos)
        : m_id(id), m_pos(pos)
    {}

    void AddLink(const GraphLink& link)
    {
        m_links.push_back(link);
    }

    const std::vector<GraphLink>& GetLinks() const
    {
        return m_links;
    }

    const glm::vec2& GetPosition() const
    {
        return m_pos;
    }

    NodeIndex GetID() const
    {
        return m_id;
    }
private:
    NodeIndex m_id;
    glm::vec2 m_pos;
    std::vector<GraphLink> m_links;
};

class Graph
{
public:
    Graph() = default;
    ~Graph() = default;
    Graph(const Graph& pathfinder) = default;
    Graph(Graph&& pathfinder) = default;
    Graph& operator=(const Graph& pathfinder) = default;
    Graph& operator=(Graph&& pathfinder) = default;

    void AddNode(NodeIndex id, const glm::vec2& pos);
    void AddSingleLink(NodeIndex from, NodeIndex to, Weight weight);
    void AddDoubleLink(NodeIndex from, NodeIndex to, Weight weight);

    GraphNodeWeakPtr GetNode(NodeIndex node_index) const;
    std::size_t Size() const;
private:
    std::vector<GraphNodePtr> m_nodes;
};

#endif // GRAPH_HPP
