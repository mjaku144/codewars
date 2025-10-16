
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

#include "solution.hpp"

/* base of previous experimet it was found out that increment have to be optimized,
 * and create set of uniqe values is not enought we have to optymise piking next array which
 * will block minimal potential next arrays
 */

void printVector(const std::vector<int>& data)
{
	for(auto & value : data)
	{
		std::cout << value << '\t';
	}
	std::cout << '\n';
}

void printVectors(const std::vector<std::vector<int>>::iterator begin, const std::vector<std::vector<int>>::iterator end)
{
	for( auto iter = begin; iter != end; iter++)
	{
		printVector(*iter);
	}
	std::cout << '\n';
}

int main(int argc, char** argv)
{
	int argument = std::stoi(argv[1]);
	int maxValue = argument * argument + argument + 1;
	int size = argument+1;

	std::vector<std::vector<int>> possibleValues;
	std::vector<std::vector<int>> largestSetOfData = {};
	std::vector<int> dataCounter;
	dataCounter.resize(size);
	std::iota(dataCounter.begin(), dataCounter.end(), 1);
	possibleValues.push_back(dataCounter);
	while(increment(dataCounter, maxValue) == true)
	{
		possibleValues.push_back(dataCounter);
	}

	auto bestValueIter = possibleValues.begin();
	auto bestValue = *bestValueIter;
	largestSetOfData.push_back(bestValue);
	auto checkSimilarity = [&bestValue](auto x){return isEqual(x,bestValue);};
	auto endIter = std::remove_if(possibleValues.begin(), possibleValues.end(), checkSimilarity);
	std::vector<std::pair<std::vector<std::vector<int>>::iterator, int>> similaritiesMap = {};
	similaritiesMap.reserve(std::distance(possibleValues.begin(), endIter));

	printVectors(possibleValues.begin(), endIter);
	std::cout << "\n\n";

	int x =0;
	while(endIter != possibleValues.begin())
	{

		std::cout << "ITERATION: " << x << '\n';
		std::cout << "create similariteisMap: \n\n";
		for( auto iter = possibleValues.begin(); iter != endIter; iter++)
		{
			bestValue = *iter;
			int count = std::count_if(possibleValues.begin(), endIter, checkSimilarity);
			std::pair<std::vector<std::vector<int>>::iterator, int> pair(iter, count);
			
			similaritiesMap.push_back(pair);
		}

		//find lowest count
		std::cout << "find lowest: \n\n";
		for(auto iter : similaritiesMap)
		{
			printVector(*(iter.first));
			std::cout << "count1: " << iter.second << "\n\n";
		}

		//find minimal value 
		auto min = std::min_element(similaritiesMap.begin(), similaritiesMap.end(), [](auto a, auto b){return a.second < b.second;});
		printVector(*(min->first));
		std::cout << "count2: " << min->second << "\n\n";
		//shrink possible values
		bestValue = *(min->first);
		largestSetOfData.push_back(bestValue);
		endIter = std::remove_if(possibleValues.begin(), endIter, checkSimilarity);
		std::cout << "rest of possible values\n";
		printVectors(possibleValues.begin(), endIter);
		//repeat
		similaritiesMap.clear();
		x++;
	}

	//print result
	std::cout << "RESULT:\n";
	printVectors(largestSetOfData.begin(), largestSetOfData.end());
	std::cout << "size: " << largestSetOfData.size() << '\n';
}
