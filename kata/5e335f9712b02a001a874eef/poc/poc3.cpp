#include <iostream>
#include <vector>
#include <utility>

/*
 * After investigatin dobble game problem and find out one additional restriction algorithm will be proposed, this time hope will not need excesive time span
 *https://math.stackexchange.com/questions/3502159/how-can-i-make-a-collection-of-sets-where-every-pair-of-sets-has-exactly-one-ele#:~:text=For%20each%20of%20these%20collections%20of%20sets%2C,amount%20of%20numbers%20in%20the%20universal%20set).
 * https://math.stackexchange.com/questions/172771/are-there-an-infinite-set-of-sets-that-only-have-one-element-in-common-with-each#:~:text=I%20realise%20that%20having%20sets%20like%20%7B1%2C,5%2C%206%2C%207%7D%2C%20%7B1%2C%208%2C%209%2C%2010%7D%2C&text=answers%20the%20question%20(with%201%20being%20the,times%20(for%20example%2C%20in%207%20given%20sets).
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

void printMatrix(const std::vector<std::vector<int>>& data)
{
	std::cout << "DEBUG Printing matrix:\n";
	for( auto & column : data)
	{
		for(auto & row : column)
		{
			std::cout << row << '\t';
		}	
		std::cout << '\n';
	}
	std::cout << '\n';
}

//TODO finaly working algorithm -> the last thing is to add more local matrix buffers or optimize searching for used pairs
int main(int argc, char **argv)
{
	constexpr int True = 1;
	constexpr int False = 0;

	int argument = std::stoi(argv[1]);
	int maxValue = argument * argument + argument + 1;
	int size = argument+1;
	std::cout << "debug argument: " << argument << '\n';
	std::cout << "debug size: " << size << '\n';
	std::cout << "debug maxValue: " << maxValue << '\n';

	//create pairMarix
	//type int to avoid bool specialisation
	std::vector<std::vector<int>> pairMatrix;
	pairMatrix.resize(maxValue);
	std::vector<std::vector<int>> pairMatrixLocalCopy;
	for ( auto & column : pairMatrix)
	{
		column.resize(maxValue, False);
	}

	//printMatrix(pairMatrix);
	//fill crossing with true
	for(auto iter = 0; iter < maxValue; iter++)
	{
		pairMatrix[iter][iter] = True;
	}

	pairMatrixLocalCopy = pairMatrix;

	//printMatrix(pairMatrix);
	//printMatrix(pairMatrixLocalCopy);

	std::vector<std::vector<int>> result;
	for(auto columnIter = 0 ; columnIter < maxValue; columnIter++)
	{
		std::vector<int> resultRow;
		resultRow.reserve(size);
		//find first False one
		for( auto rowIter = 0 ; rowIter < maxValue; rowIter++)
		{
			if( pairMatrixLocalCopy[columnIter][rowIter] == False )
			{
				//additional check of row
				bool breakFlag = false;
				for(auto resultElement : resultRow)
				{
					if(pairMatrixLocalCopy[rowIter][resultElement] == True)
					{
						breakFlag = true;
						continue;
					}
				}
				if(breakFlag == true)
				{
					//it was dead end
					pairMatrixLocalCopy = pairMatrix;
					continue;
				}

				//push_back
				if(resultRow.size() == 0)
				{
					resultRow.push_back(columnIter);
				}
				resultRow.push_back(rowIter);
				//mark in matrix
				for(auto x : resultRow)
				{
					for(auto y : resultRow)
					{
						pairMatrixLocalCopy[x][y] = True;
						pairMatrixLocalCopy[y][x] = True;
					}
				}
			}
			//apply increment to change result row from indexes domain to real numbers domain
			if(resultRow.size() == size)
			{
				for( auto & element : resultRow)
				{
					element++;
				}
				result.push_back(std::move(resultRow));
				rowIter = 0;
				pairMatrix = pairMatrixLocalCopy;
			}
			
		}
	}
	std::cout << "END RESULT:\n";
	std::cout << "MATRIX:\n;";
	printMatrix(pairMatrix);
	std::cout << "VECTORS\n";
	printVectors(result.begin(), result.end());
	std::cout << "VECTORS SIZE: " << result.size() << '\n';
	std::cout << "EXPECTED SIZE: " << maxValue << '\n';
}
