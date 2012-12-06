#ifndef NODE_H
#define NODE_H

#include "Link.h"

#include <vector>

// a basic node class with no links to other nodes
template <typename T>
class Node
{
public:
	const unsigned int		id;

	Node() : id(nextFreeId++)
	{
	}

	virtual ~Node()
	{
	}

	bool					operator== (const Node &o)
	{
		if (o.id == id)
			return true;
		return false;
	}

	void					operator= (const Node &o)
	{
	}

protected:
	static unsigned int		nextFreeId;

	std::vector<Link<T> >	connections;
};

template <typename T>
unsigned int Node<T>::nextFreeId = 0;

#endif
