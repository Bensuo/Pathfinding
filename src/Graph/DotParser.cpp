#include "DotParser.hpp"
#include <fstream>
#include <sstream>
namespace Graph
{
	DotParser::DotParser()
	{

	}

	DotParser::~DotParser()
	{

	}

	bool DotParser::Read(std::string filename)
	{
		std::ifstream dot_in(filename);
		std::string line;
		while (std::getline(dot_in, line))
		{
			std::string token = line.substr(0, line.find('['));
			std::string args = line.substr(line.find('['), line.size());
			size_t pos = token.find('--');
			if (pos == std::string::npos)
			{
				//Token is a vertex
				//Read the vertex ID
				int id = std::stoi(token);
			
			}
			else
			{
				//Token is edge
				//Get the IDs of the two points of the edge
				int first = std::stoi(token.substr(0, pos));
				int second = std::stoi(token.substr(pos + 1, token.size()));
			}
		}
		return false;
	}

}