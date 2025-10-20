#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

void initPairMatrix(std::vector<std::vector<char>> & pairMatrix, int maxValue);

std::pair<int, int> findNextFalse(std::vector<std::vector<char>> & pairMatrix, int testSize);

std::pair<bool, int> findNextValueForSolution(std::vector<int> & solutionRow, std::vector<std::vector<char>> & initPairMatrix, int maxValue);

void fillSolutionRowForInitCoordinates(std::vector<int> & solutionRow, std::vector<std::vector<char>> & initPairMatrix, int maxValue, unsigned int solutionRowSize);

void transformFromIndexDomainToNumberDomain(std::vector<int> & data);

void markIndexesInMatrix(std::vector<std::vector<char>> & matrix, const std::vector<int> & numbers);

//definition from codewars
std::vector<std::vector<int>> arrays(int p);

#endif //SOLUTION_HPP
