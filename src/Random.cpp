#include "Random.h"

 int Random::getRandomInt(int min, int max) {
    static std::random_device rd;  // Non-deterministic random seed
    static std::mt19937 rng(rd()); // Mersenne Twister PRNG
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

 std::vector<std::vector<int>> Random::makeRandomMatrix(int m) {
	 std::vector<std::vector<int>> mat(m, std::vector<int>(m));

	 for (int i = 0; i < m ; i++) {
		 for (int j = 0; j < m; j++) {
			 mat[i][j] = Random::getRandomInt(-1, 1);
		 }
	 }
	 return mat;
 }