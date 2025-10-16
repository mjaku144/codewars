#include <vector>

#include <gtest/gtest.h>

#include "solution.hpp"

TEST(isEqual, ReturnTrueIfSameVectorPassed)
{
	std::vector<int> sut1 = {1, 2, 3, 56, 23};
	std::vector<int> sut2 = sut1;
	EXPECT_TRUE(isEqual(sut1, sut2));
}

TEST(isEqual, ReturnTrueIf2ElementsInVectorsSame)
{
	std::vector<int> sut1 = {1, 2, 3, 4, 6};
	std::vector<int> sut2 = {4, 6, 34, 12, 3};
	EXPECT_TRUE(isEqual(sut1, sut2));
}

TEST(isEqual, ReturnFalseIf1ElementsInVectorsSame)
{
	std::vector<int> sut1 = {1, 2, 3};
	std::vector<int> sut2 = {3, 4, 5};
	EXPECT_FALSE(isEqual(sut1, sut2));
}

TEST(isEqual, ReturnFalseIfVectorsElementsAreAllDiffernt)
{
	std::vector<int> sut1 = {1, 2, 3};
	std::vector<int> sut2 = {6, 4, 5};
	EXPECT_FALSE(isEqual(sut1, sut2));
}

TEST(increment, ReturnTrueIsSuccesfull)
{
	std::vector<int> sut1 = {1, 2, 3};
	std::vector<int> sut2 = sut1;
	EXPECT_TRUE(increment(sut2, 10));
}

TEST(increment, ModifyDataToBeNotEqualToPreviousValue)
{
	std::vector<int> sut1 = {1, 2, 3};
	std::vector<int> sut2 = sut1;
	increment(sut2, 10);
	EXPECT_FALSE(sut1 == sut2);
}

TEST(increment, ReturnFalseIfCannotIncrement)
{
	std::vector<int> sut1 = {1, 2, 3};
	std::vector<int> sut2 = sut1;
	EXPECT_FALSE(increment(sut2, 3));
}

TEST(increment, CanInterateThroughAllPossibleValues)
{
	std::vector<int> data = {1,2,3};
	int maxValue = 4;
	std::vector<std::vector<int>> iterationValues = {{1,2,4}, {1,3,4}, {2,3,4}};

	for( auto& nextIteration : iterationValues)
	{
		increment(data, maxValue);
		EXPECT_EQ(data, nextIteration);
	}
	EXPECT_FALSE(increment(data, maxValue));
}

void printVector(const std::vector<int>& data)
{
	for(auto & value : data)
	{
		std::cout << value << '\t';
	}
	std::cout << '\n';
}

TEST(test, test)
{
	std::vector<int> data = {1,2,3};
	printVector(data);
	while(increment(data, 7) == true)
	{
		printVector(data);
	}
}
