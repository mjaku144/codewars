#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>

#include "solution.hpp"

//TODO: working with indexes disallow usage of algorithms,
//it will be faster (performance) to manually write loop rather than obtain iterator and use of std::distance to convert to index
//Am i able to modify algorithm to work with iterators?? std::vector<std::set<int>> maybe as next approach??

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

std::pair<bool, int> findNextValueForSolution(std::vector<int> & solutionRow, std::vector<std::vector<char>> & pairMatrix, int maxValue)
{
	for(int index = 0; index < maxValue; index++)
	{
		bool sum = false;
		for(auto value : solutionRow)
		{
			sum |= pairMatrix[value][index];
		}
		if(sum == false)
		{
			return {true, index};
		}
	}
	return {false, 0};
}

//TODO testing of this function
void fillSolutionRowForInitCoordinates(std::vector<int> & solutionRow, std::vector<std::vector<char>> & initPairMatrix, int maxValue, unsigned int solutionRowSize)
{
	while(solutionRow.size() != solutionRowSize)
	{
		auto [result, value] = findNextValueForSolution(solutionRow, initPairMatrix, maxValue);
		if(result == true)
		{
			solutionRow.push_back(value);
		}

		//TODO to delete, should work for 2 -> kind of recursion needed here
		break;
	}
	//TODO
}

void transformFromIndexDomainToNumberDomain(std::vector<int> & data)
{
	std::for_each(data.begin(), data.end(), [](auto & x){x++;});
}

void markIndexesInMatrix(std::vector<std::vector<char>> & matrix, const std::vector<int> & indexes)
{
	for(auto iter1 = indexes.begin(); iter1 != indexes.end(); iter1++)
	{
		for(auto iter2 = iter1 + 1; iter2 != indexes.end(); iter2++)
		{
			matrix[*iter1][*iter2] = true;
			matrix[*iter2][*iter1] = true;
		}
	}
}

//TODO add testing
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
		std::vector<int> solutionRow;
		solutionRow.reserve(sizeOfArray);
		auto [ column, row ] = findNextFalse(pairMatrix, maxValue);
		solutionRow.push_back(column);
		solutionRow.push_back(row);

		fillSolutionRowForInitCoordinates(solutionRow, pairMatrix, maxValue, sizeOfArray);
		markIndexesInMatrix(pairMatrix, solutionRow);

		transformFromIndexDomainToNumberDomain(solutionRow);
		solution.push_back(solutionRow);
	}

	return solution;
}