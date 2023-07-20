#pragma warning (disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<int> Row;
typedef std::vector<Row> Grid;

int main() {
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "Couldn't open file ./Input.txt : " << strerror(errno) << std::endl;
		return errno;
	}
	int part = 1;
	std::cout << "Wich part ? (1 or 2)\n";
	std::cin >> part;

	char c;
	int digit = 5;
	std::string line;
	std::string result;
	Grid g(5, Row(5, 0));
	g[0][2] = 1;
	g[1] = { 0, 2, 3, 4, 0 };
	g[2] = { 5, 6, 7, 8, 9 };
	g[3] = { 0, 10, 11, 12, 0 };
	g[4][2] = 13;
	int x = 0;
	int y = 2;
	while (!input.eof()) {
		getline(input, line);
		if (part == 1) {
			for (char c : line) {
				switch (c) {
				case 'U':
					if (digit >= 4)
						digit -= 3;
					break;
				case 'D':
					if (digit <= 6)
						digit += 3;
					break;
				case 'L':
					if (digit % 3 != 1)
						--digit;
					break;
				case 'R':
					if (digit % 3)
						++digit;
					break;
				}
			}
			result += digit + '0';
		}
		else {
			for (char c : line) {
				switch (c) {
				case 'U':
					if (y - 1 >= 0 && g[y - 1][x])
						--y;
					break;
				case 'D':
					if (y + 1 < 5 && g[y + 1][x])
						++y;
					break;
				case 'L':
					if (x - 1 >= 0 && g[x - 1][y])
						--x;
					break;
				case 'R':
					if (x + 1 < 5 && g[x + 1][y])
						++x;
					break;
				}
			}
			if (g[y][x] > 9)
				result += g[y][x] + 'A' - 10;
			else
				result += g[y][x] + '0';
		}
	}

	std::cout << "result is " << result << std::endl;
	return 0;
}
