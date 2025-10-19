#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

void initPairMatrix(std::vector<std::vector<char>> & pairMatrix, int maxValue);

std::pair<int, int> findNextFalse(std::vector<std::vector<char>> & pairMatrix, int testSize);

//definition from codewars
std::vector<std::vector<int>> arrays(int p);

#endif //SOLUTION_HPP
