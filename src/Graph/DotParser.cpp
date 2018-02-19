#include "DotParser.hpp"
#include <fstream>
#include <sstream>

	DotParser::DotParser()
	{

	}

	DotParser::~DotParser()
	{

	}

	Graph DotParser::Read(const std::string& filename)
	{
		Graph graph;
		std::ifstream dot_in(filename);
		std::string line;
		while (std::getline(dot_in, line))
		{
			if (line == "") continue;
			std::string token = line.substr(0, line.find('['));
			std::string args = line.substr(line.find('['), line.size());
			size_t pos = token.find('--');
			if (pos == std::string::npos)
			{
				//Token is a vertex
				//Read the vertex ID
				int id = std::stoi(token);
				int x = std::stoi(args.substr(args.find("[pos=\"") + 6, args.find(',') - 1));
				int y = std::stoi(args.substr(args.find(',') + 1, args.find("\"]")-2));
                graph.AddNode(id, { x, y });
			}
			else
			{
				//Token is edge
				//Get the IDs of the two points of the edge
				int first = std::stoi(token.substr(0, pos));
				int second = std::stoi(token.substr(pos + 2, token.size()));
				int weight = std::stoi(args.substr(args.find("label=\"")+7, args.find("\"]")-2));
				graph.AddDoubleLink(first, second, weight);
			}
		}
		return std::move(graph);
	}
