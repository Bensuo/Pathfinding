#include <Graph/DotParser.hpp>
#include <fstream>
#include <sstream>

DotParser::DotParser()
= default;

DotParser::~DotParser()
= default;

Graph DotParser::Read(const std::string& filename) const
{
    Graph graph;
    std::ifstream dot_in(filename);
    std::string line;
    while (std::getline(dot_in, line))
    {
        if (line.empty()) continue;
        auto token = line.substr(0, line.find('['));
        auto args = line.substr(line.find('['), line.size());
        const auto pos = token.find("--");
        if (pos == std::string::npos)
        {
            //Token is a vertex
            //Read the vertex ID
            const auto id = std::stoi(token);
            const auto x = std::stoi(args.substr(args.find("[pos=\"") + 6, args.find(',') - 1));
            const auto y = std::stoi(args.substr(args.find(',') + 1, args.find("\"]") - 2));
            graph.AddNode(id, { x, y });
        }
        else
        {
            //Token is edge
            //Get the IDs of the two points of the edge
            const auto first = std::stoi(token.substr(0, pos));
            const auto second = std::stoi(token.substr(pos + 2, token.size()));
            const auto weight = std::stoi(args.substr(args.find("label=\"") + 7, args.find("\"]") - 2));
            graph.AddDoubleLink(first, second, weight);
        }
    }
    return graph;
}