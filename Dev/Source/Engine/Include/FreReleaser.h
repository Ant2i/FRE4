#pragma once

template <typename T>
class Releaser
{
public:
	void operator()(T * ptr) const
	{
		if (ptr)
			ptr->Destroy();
	}
};