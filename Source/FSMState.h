#ifndef FSMSTATE_H
#define FSMSTATE_H

template <typename T>
public class FSMState
{
public:
							FSMState(T *_owner)
							{
								owner = _owner;
							}

	virtual void			Enter() = 0;
	virtual void			Update(/*float deltaTime*/) = 0;
	virtual void			Exit() = 0;

	//char*					Name;

protected:
	T*						owner;
};

#endif