#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <memory>

	class Graph
	{
		class GraphNode;
		class GraphLink
		{
		public:
			GraphLink(const std::weak_ptr<GraphNode>& from, const std::weak_ptr<GraphNode>& to, int weight)
				: m_from(from),
				m_to(to),
				m_weight(weight)
			{

			}
			std::weak_ptr<GraphNode> GetFrom()
			{
				return m_from;
			}
			std::weak_ptr<GraphNode> GetTo()
			{
				return m_to;
			}
			int GetWeight()
			{
				return m_weight;
			}
		private:
			std::weak_ptr<GraphNode> m_from;
			std::weak_ptr<GraphNode> m_to;
			int m_weight;
		};
		class GraphNode
		{
		public:
			GraphNode(int id, int x, int y)
				: m_id(id), m_x(x), m_y(y)
			{

			}
			void AddLink(const GraphLink& link)
			{
				m_links.push_back(link);
			}
			int GetID()
			{
				return m_id;
			}
		private:
			int m_id;
			int m_x;
			int m_y;
			std::vector<GraphLink> m_links;
		};
	public:
		Graph();
		~Graph();
		void AddNode(int id, int x, int y);
		void AddSingleLink(int from, int to, int weight);
		void AddDoubleLink(int from, int to, int weight);
	private:
		std::vector<std::shared_ptr<GraphNode>> m_nodes;
	};

#endif // GRAPH_HPP
