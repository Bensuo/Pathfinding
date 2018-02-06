#pragma once
#include <string>
namespace Graph
{
	class DotParser
	{
	public:
		DotParser();
		~DotParser();

		bool Read(std::string filename);

	private:
	};
}
