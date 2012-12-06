#ifndef LINK_H
#define LINK_H

// a two-directional link
template <typename T>
class Link
{
public:
	float cost;
	T *origin;
	T *target;

	Link SwitchOriginTarget()
	{
		Link l;
		l.origin = target;
		l.target = origin;
		l.cost = cost;
		return l;
	}

	bool operator==(const Link& o) const
	{
		if (o.cost == cost && o.origin == origin && o.target == target)
			return true;
		else
			return false;
	}
};

#endif
