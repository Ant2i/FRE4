#pragma once

#include <mutex>
#include <vector>
#include <algorithm>

template <typename T, typename Compare>
class SafeSet
{
	typedef std::vector<T> Container;
	typedef typename Container::value_type Type;

public:
	struct Result
	{
		Result() :
			Correct(false)
		{

		}

		Result(const Type & v) : 
			Correct(true)
		{
			new(_values) T(v);
		}

		T GetValue() const
		{
			return *(reinterpret_cast<T*>((void *)_values));
		}

		const bool Correct;

	private:
		char * _values[sizeof(T)];
	};

public:
	SafeSet()
	{

	}

	SafeSet(const SafeSet & s) :
		_data(s._data)
	{

	}

	SafeSet(const SafeSet && s) :
		_data(std::move(s._data))
	{

	}

	~SafeSet()
	{

	}

	bool Insert(const Type & v)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		Compare compare;
		auto it = std::lower_bound(_data.begin(), _data.end(), v, compare);
		if (it == _data.end() || compare(v, *it))
		{
			_data.insert(it, v);
			return true;
		}
		return false;
	}

	void Remove(const Type & v)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		auto it = std::lower_bound(_data.begin(), _data.end(), v, Compare());
		if (it != _data.end())
		{
			_data.erase(it);
		}
	}

	Result Search(typename Compare::CompareType value) const
	{
		std::lock_guard<std::mutex> lock(_mutex);

		auto it = std::lower_bound(_data.begin(), _data.end(), value, Compare());
		if (it != _data.end())
			return Result(*it);
		return Result();
	}

	unsigned Size() const
	{
		return _data.size();
	}

private:
	Container _data;
	mutable std::mutex _mutex;
};