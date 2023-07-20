#pragma warning (disable : 4996)

#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <set>

typedef std::pair<int, int> Coord;

Coord& operator+=(Coord& lhs, const Coord& rhs) {
	lhs.first += rhs.first;
	lhs.second += rhs.second;
	return lhs;
}

std::ostream& operator<<(std::ostream& o, const Coord& c) {
	o << c.first << '|' << c.second;
	return o;
}

int myModulo(int a, int b) {
	if (b <= 0)
		return -1;
	if (a >= 0)
		return a % b;
	else
		return (b - (-a % b)) % b;
}

int ManDist(const Coord& lhs, const Coord& rhs) {
	return (abs(lhs.first - rhs.first) + abs(lhs.second - rhs.second));
}

int main() {
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "Couldn't open file ./Input.txt : " << strerror(errno) << std::endl;
		return errno;
	}

	int part = 1;
	int dir = 0;
	std::string line;
	std::set<Coord> visited;
	Coord pos(0, 0);

	visited.insert(pos);
	std::cout << "Wich part ? (1 or 2)\n";
	std::cin >> part;
	while (!input.eof()) {
		getline(input, line);
		std::string::size_type idx = 0;
		while (idx < line.size()) {
			char c = line[idx];
			switch (c) {
			case 'R':
				dir = myModulo(dir + 1, 4);
				break;
			case 'L':
				dir = myModulo(dir - 1, 4);
				break;
			default:
				if (isdigit(c)) {
					int add = atoi(&line[idx]);
					while (isdigit(line[idx]))
						++idx;
					--idx;
					switch (dir) {
					case 0:
						if (part != 1) {
							for (int i = 0; i < add; ++i) {
								pos += std::make_pair(0, 1);
								std::pair<std::set<Coord>::iterator, bool> insertRes = visited.insert(pos);
								if (!insertRes.second) {
									std::cout << "result is " << ManDist(*insertRes.first, std::make_pair(0, 0)) << std::endl;
									return 0;
								}
							}
						}
						else
							pos += std::make_pair(0, add);
						break;
					case 1:
						if (part != 1) {
							for (int i = 0; i < add; ++i) {
								pos += std::make_pair(1, 0);
								std::pair<std::set<Coord>::iterator, bool> insertRes = visited.insert(pos);
								if (!insertRes.second) {
									std::cout << "result is " << ManDist(*insertRes.first, std::make_pair(0, 0)) << std::endl;
									return 0;
								}
							}
						}
						else
							pos += std::make_pair(add, 0);
						break;
					case 2:
						if (part != 1) {
							for (int i = 0; i < add; ++i) {
								pos += std::make_pair(0, -1);
								std::pair<std::set<Coord>::iterator, bool> insertRes = visited.insert(pos);
								if (!insertRes.second) {
									std::cout << "result is " << ManDist(*insertRes.first, std::make_pair(0, 0)) << std::endl;
									return 0;
								}
							}
						}
						else
							pos += std::make_pair(0, -add);
						break;
					case 3:
						if (part != 1) {
							for (int i = 0; i < add; ++i) {
								pos += std::make_pair(-1, 0);
								std::pair<std::set<Coord>::iterator, bool> insertRes = visited.insert(pos);
								if (!insertRes.second) {
									std::cout << "result is " << ManDist(*insertRes.first, std::make_pair(0, 0)) << std::endl;
									return 0;
								}
							}
						}
						else
							pos += std::make_pair(-add, 0);
						break;
					default:
						throw("");
					}
				}
				break;
			}
			++idx;
		}
	}
	std::cout << "Result is " << ManDist(pos, std::make_pair(0, 0)) << std::endl;
	return 0;
}