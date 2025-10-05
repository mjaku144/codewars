#include <vector>
#include <algorithm>
#include <numeric>

#include "solution.hpp"

bool isEqual(const std::vector<int> & lhs, const std::vector<int> & rhs)
{
	bool oneElementEqual = false;
	for (const auto & value : lhs)
	{
		if(std::find(rhs.begin(), rhs.end(), value) != rhs.end())
		{
			if( oneElementEqual == false)
			{
				oneElementEqual = true;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}

bool increment(std::vector<int> & data, const int maxValue)
{
	for(auto iter = data.rbegin(); iter != data.rend(); iter++)
	{
		(*iter)++;
		std::iota( (iter+1).base(), data.end(), *iter);
		if(*iter > maxValue || data.back() > maxValue)
		{
			continue;
		}
		else
		{
			return true;
		}
	}
	return false;
}
