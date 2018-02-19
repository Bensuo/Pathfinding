#pragma once
#include <string>
#include "Graph.hpp"

class DotParser
	{
	public:
		DotParser();
		~DotParser();

		Graph Read(std::string filename);

	private:
	};

