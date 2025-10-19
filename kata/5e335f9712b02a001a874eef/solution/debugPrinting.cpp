
#include <iostream>
#include <vector>

#include <debugPrinting.hpp>

int convertCharToInt(char data)
{
    if(data)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

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

void printMatrix(const std::vector<std::vector<char>>& data)
{
	std::cout << "DEBUG Printing matrix:\n";
	for( auto & column : data)
	{
		for(auto & row : column)
		{
			std::cout << convertCharToInt(row) << '\t';
		}	
		std::cout << '\n';
	}
	std::cout << '\n';
}