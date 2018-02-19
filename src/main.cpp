#include "Graph\DotParser.hpp"
int main(int argc, char* argv[])
{
	DotParser parser;
	Graph graph = parser.Read("graph.dot");
}