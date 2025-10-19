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