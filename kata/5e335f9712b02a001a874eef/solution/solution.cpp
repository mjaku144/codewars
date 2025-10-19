#include <vector>
#include <utility>
#include <cassert>

#include "solution.hpp"

//TODO: working with indexes disallow usage of algorithms,
//it will be faster (performance) to manually write loop rather than obtain iterator and use of std::distance to convert to index
//Am i amble to modify algorithm to work with iterators?? std::vector<std::set<int>> maybe as next approach??

void initPairMatrix(std::vector<std::vector<char>> & pairMatrix, int maxValue)
{
	pairMatrix.resize(maxValue);
	for( auto & array : pairMatrix)
	{
		array = std::vector<char>(maxValue, false);
	}
	for(int index = 0; index < maxValue; index++)
	{
		pairMatrix[index][index] = true;
	}
}

std::pair<int, int> findNextFalse(std::vector<std::vector<char>> & pairMatrix, int maxValue)
{
	for(int columnIndex = 0; columnIndex < maxValue; columnIndex++)
	{
		for(int rowIndex = 0; rowIndex < maxValue; rowIndex++)
		{
			if(pairMatrix[columnIndex][rowIndex] == false)
			{
				return {columnIndex, rowIndex};
			}
		}
	}

	//TODO error handling?? should not reach this point
	//light error for debug
	assert(false);
	return {0,0};
}

std::vector<std::vector<int>> arrays(int p)
{
	const int inputNumber = p;
	const int sizeOfArray = inputNumber + 1;
	const size_t sizeOfSolution = inputNumber * inputNumber + inputNumber + 1;
	const int maxValue = sizeOfSolution;

	std::vector<std::vector<int>> solution;
	solution.reserve(sizeOfSolution);
	
	std::vector<std::vector<char>> pairMatrix;
	initPairMatrix(pairMatrix, maxValue);
	
	while(solution.size() != sizeOfSolution)
	{
		auto [ column, row ] = findNextFalse(pairMatrix, maxValue);

		//TODO to delete
		std::ignore = column;
		std::ignore = row;
		solution.resize(sizeOfSolution);
	}

	//TODO to delete
	std::ignore = sizeOfArray;

	return solution;
}