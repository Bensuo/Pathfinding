#include "Graph\DotParser.hpp"
int main(int argc, char* argv[])
{
	Graph::DotParser parser;
	parser.Read("graph.dot");
}