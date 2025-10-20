#include <algorithm>

#include <gtest/gtest.h>

#include "debugPrinting.hpp"
#include "solution.hpp"

TEST(initPairMatrix, IsSizeOfMaxValue)
{
	int testSize = 8;
	std::vector<std::vector<char>> sut;
	initPairMatrix(sut, testSize);
	EXPECT_EQ(sut.size(), testSize );
}

TEST(initPairMatrix, SubArraysAreSizeOfMaxValue)
{
	int testSize = 10;
	std::vector<std::vector<char>> sut;
	initPairMatrix(sut, testSize);
	for(auto & array : sut)
	{
		EXPECT_EQ(array.size(), testSize);
	}
}

TEST(initPairMatrix, FilledWithFalsesAndTruesOnSameValueOfRowAndColumn)
{
	int testSize = 9;
	std::vector<std::vector<char>> sut;
	initPairMatrix(sut, testSize);
	for(int columnIndex = 0; columnIndex < testSize; columnIndex++)
	{
		for(int rowIndex = 0; rowIndex < testSize; rowIndex++)
		{
			if(rowIndex == columnIndex)
			{
				EXPECT_TRUE(sut[columnIndex][rowIndex]);
			}
			else
			{
				EXPECT_FALSE(sut[columnIndex][rowIndex]);
			}
		}
	}
}

TEST(findNextFalse, ReturningCoordinatesToAnyFalse)
{
	int testSize = 15;
	std::vector<std::vector<char>> sut;
	initPairMatrix(sut, testSize);
	for(int columnIndex = 0; columnIndex < testSize; columnIndex++)
	{
		for(int rowIndex = 0; rowIndex < testSize; rowIndex++)
		{
			if((columnIndex * rowIndex + 1) % 3 != 0)
			{
				sut[columnIndex][rowIndex] = true;
				sut[rowIndex][columnIndex] = true;
			}
		}
	}
	auto [column, row] = findNextFalse(sut, testSize);
	EXPECT_FALSE(sut[column][row]);
}

TEST(findNextFalse, ReturningCoordinatesToTheOnlyFalse)
{
	int testSize = 17;
	std::vector<std::vector<char>> sut;
	initPairMatrix(sut, testSize);
	for(auto & column : sut)
	{
		std::fill(column.begin(), column.end(), true);
	}
	int columnWithFalse = 4;
	int rowWithFalse = 7;
	sut[columnWithFalse][rowWithFalse] = false;

	auto [column, row] = findNextFalse(sut, testSize);
	EXPECT_EQ(column, columnWithFalse);
	EXPECT_EQ(row, rowWithFalse);
}

TEST(findNextValueForSolution, WillReturnFirstCommonFalseForColumns)
{
	int testSize = 100;
	int commonTrues = testSize * 3 / 4;
	int firstCommonFalse = commonTrues + 1;
	std::vector<std::vector<char>> pairMatrix;
	initPairMatrix(pairMatrix, testSize);

	std::vector<int> resultValues = {2, 5, 6};
	for(int index = 0; index <= commonTrues; index++)
	{
		if(index % 2)
		{
			pairMatrix[resultValues[0]][index] = true;
		}
		if(index % 3 != 1)
		{
			pairMatrix[resultValues[1]][index] = true;
		}
		if(index % 5 != 1 || ( pairMatrix[resultValues[0]][index] == false && pairMatrix[resultValues[1]][index] == false))
		{
			pairMatrix[resultValues[2]][index] = true;
		}
	}
	auto [result, value] =  findNextValueForSolution(resultValues, pairMatrix, testSize);
	EXPECT_TRUE(result);
	EXPECT_EQ(value, firstCommonFalse);
}

TEST(findNextValueForSolution, WillReturnFalseIfNoCommonFalseInMatrixForColumns)
{
	int testSize = 100;
	std::vector<std::vector<char>> pairMatrix;
	initPairMatrix(pairMatrix, testSize);

	std::vector<int> resultValues = {2, 5, 6};
	for(int index = 0; index < testSize; index++)
	{
		if(index % 2)
		{
			pairMatrix[resultValues[0]][index] = true;
		}
		if(index % 3 != 1)
		{
			pairMatrix[resultValues[1]][index] = true;
		}
		if(index % 5 != 1 || ( pairMatrix[resultValues[0]][index] == false && pairMatrix[resultValues[1]][index] == false))
		{
			pairMatrix[resultValues[2]][index] = true;
		}
	}
	auto [result, value] =  findNextValueForSolution(resultValues, pairMatrix, testSize);
	EXPECT_FALSE(result);
	std::ignore = value;
}

TEST(transformFromIndexDomainToNumberDomain, AddOneToAllElements)
{
	std::vector<int> data = {0,1,2};
	auto dataCopy = data;
	transformFromIndexDomainToNumberDomain(data);
	EXPECT_TRUE(std::equal(data.begin(), data.end(), dataCopy.begin(), dataCopy.end(), [](auto x, auto y){return  x == (y + 1);}));
}

TEST(markIndexesInMatrix, WillMarkEveryPossiblePairOfINdexesAsTrue)
{
	int testSize = 10;
	std::vector<std::vector<char>> matrix;
	initPairMatrix(matrix, testSize);
	std::vector<int> indexes = {2, 4, 7};
	markIndexesInMatrix(matrix, indexes);

	for(auto iter1 = indexes.begin(); iter1 != indexes.end(); iter1++)
	{
		for(auto iter2 = iter1 + 1; iter2 != indexes.end(); iter2++)
		{
			EXPECT_TRUE(matrix[*iter1][*iter2]);
			EXPECT_TRUE(matrix[*iter2][*iter1]);
		}
	}
}

TEST(markIndexesInMatrix, WillNotModifyIndexesOutOfPassedList)
{
	int testSize = 11;
	std::vector<std::vector<char>> matrix;
	initPairMatrix(matrix, testSize);
	auto copyOfMatrix = matrix; 
	std::vector<int> indexes = {1, 3, 8};
	markIndexesInMatrix(matrix, indexes);

	for(int columnIndex = 0; columnIndex < testSize; columnIndex++)
	{
		for(int rowIndex = 0; rowIndex < testSize; rowIndex++)
		{
			bool isColumnInIndexes = (std::find(indexes.begin(), indexes.end(), columnIndex) != indexes.end());
			bool isRowInIndexes = (std::find(indexes.begin(), indexes.end(), rowIndex) != indexes.end());
			if(!(isColumnInIndexes && isRowInIndexes && columnIndex != rowIndex))
			{
				EXPECT_EQ(copyOfMatrix[columnIndex][rowIndex], matrix[columnIndex][rowIndex]);
			}
		}
	}
}

TEST(arrays, SizeOfResultAccordinglyToRequirements)
{
	constexpr int testNumber = 2;
	constexpr int expectedResultSize = testNumber * testNumber + testNumber + 1;

	auto result = arrays(testNumber);
	EXPECT_EQ(result.size(), expectedResultSize);	
}

TEST(arrays, ResultNumbersInRestrictedRange)
{
	constexpr int testNumber = 2;
	constexpr int expectedResultSize = testNumber * testNumber + testNumber + 1;
	constexpr int maxValue = expectedResultSize;

	auto result = arrays(testNumber);
	for(auto & array : result)
	{
		EXPECT_TRUE(std::all_of(array.begin(), array.end(), [&maxValue](auto x){return x > 0 && x <= maxValue;}));
	}
}

TEST(arrays, ResultsArraysElementUnique)
{
	constexpr int testNumber = 2;
	auto result = arrays(testNumber);

	for(auto & array : result)
	{
		for(auto number : array)
		{
			EXPECT_EQ(1, std::count(array.begin(), array.end(), number));
		}
	}
}

TEST(arrays, ResultsArraysHaveMaxOneElementInCommonWithRestOfThem)
{
	constexpr int testNumber = 2;
	auto result = arrays(testNumber);

	for(auto arrayIndex1 = result.begin(); arrayIndex1 != result.end(); arrayIndex1++)
	{
		for(auto arrayIndex2 = arrayIndex1 + 1; arrayIndex2 != result.end(); arrayIndex2++)
		{
			bool oneNumberInBoth = false;
			for( auto number : *arrayIndex1)
			{
				if(std::find((*arrayIndex2).begin(), (*arrayIndex2).end(), number) != (*arrayIndex2).end())
				{
					EXPECT_FALSE(oneNumberInBoth);
					oneNumberInBoth = true;
				}
			}
		}
	}
}