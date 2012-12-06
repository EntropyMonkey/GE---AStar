#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

template <typename T>
class Graph
{
public:
	virtual ~Graph()
	{
		nodes.clear();
	}

protected:
	std::vector<T*> nodes;
};

#endif
