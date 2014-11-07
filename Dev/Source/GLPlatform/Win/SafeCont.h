#pragma once

#include <mutex>
#include <vector>
#include <algorithm>

template <typename T, typename Compare>
class SafeSortContainer
{
	typedef std::vector<T> Container;
	typedef typename Container::value_type Type;

public:
	typedef std::pair<bool, Type &> SearchResult;

public:
	void Add(const Type & v)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_data.push_back(v);
	}

	void Remove(const Type & v)
	{
		if (!_data.empty())
		{
			auto it = std::lower_bound(_data.begin(), _data.end(), v);

			SortData();

			if (it != _data.end())
			{
				std::lock_guard<std::mutex> lock(_mutex);
				_data.erase(it);
			}
		}
	}

	template <typename T, typename Compare>
	SearchResult Search(T value, Compare comp)
	{
		if (!_data.empty())
		{
			std::lock_guard<std::mutex> lock(_mutex);
			auto it = std::lower_bound(_data.begin(), _data.end(), value, comp);
			return SearchResult(it != _data.end(), *it);
		}

		return SearchResult(false, *_data.end());
	}

private:
	void SortData()
	{
		std::sort(_data.begin(), _data.end(), Compare());
	}

private:
	Container _data;
	std::mutex _mutex;
};