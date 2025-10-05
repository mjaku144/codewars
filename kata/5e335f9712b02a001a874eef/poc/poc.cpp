#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>

/* Pourpose of this solution is rather to play with data
 * to find unique features of set and to be able to propose
 * something optimal, data would be printed to std::out so further
 * processing would be possible with bash*/

void increment(std::vector<int> & data, const int maxValue)
{
	for ( auto & value : data)
	{
		value++;
		if (value > maxValue)
		{
			value = 1;
		}
		else
		{
			break;
		}
	}
}

bool compare(const std::vector<int>& lhs, const std::vector<int>& rhs)
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
				return false;
			}
		}
	}
	return true;
}

bool uniqeElements(const std::vector<int>& data)
{
	auto copiedData = data;
	std::sort(copiedData.begin(), copiedData.end());
	auto iter = std::unique(copiedData.begin(),copiedData.end());
	return iter == copiedData.end();
}

void printVector(const std::vector<int>& data)
{
	for(auto & value : data)
	{
		std::cout << value << '\t';
	}
	std::cout << '\n';
}

void printHash(const std::vector<int>& data)
{
	std::cout << std::accumulate(data.begin(), data.end(), 1, std::multiplies<int>()) << '\n';
}

int main(int argc, char **argv)
{
	int argument = std::stoi(argv[1]);
	int maxValue = argument * argument + argument + 1;
	int size = argument+1;
	std::cout << "debug argument: " << argument << '\n';
	std::cout << "debug size: " << size << '\n';
	std::cout << "debug maxValue: " << maxValue << '\n';
	std::vector<int> data(size, 1);
	std::vector<std::vector<int>> uniqeData = {};
	bool lastValueMax = false;
	bool overflowDetected = false;
	while(overflowDetected == false)
	{
		increment(data, maxValue);
		if(data.back() == maxValue)
		{
			lastValueMax = true;
		}
		if(lastValueMax == true && data.back() != maxValue)
		{
			overflowDetected = true;
			continue;
		}
		if(uniqeElements(data) == false)
		{
			continue;
		}
		if(std::find_if(uniqeData.begin(), uniqeData.end(), [&data](std::vector<int>& value){return compare(data, value) == false;}) == uniqeData.end())
		{
			printVector(data);
			uniqeData.push_back(data);
		}
	}
}
