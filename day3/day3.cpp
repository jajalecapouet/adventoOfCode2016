#pragma warning (disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <deque>


int parseLine(const std::string& str) {
	std::string::size_type idx = 0;
	std::deque<int> sides;
	int side;

	while (idx < str.size()) {
		while (!isdigit(str[idx]) && idx < str.size())
			++idx;
		side = atoi(&str[idx]);
		if (sides.empty() || side < sides[0])
			sides.push_back(side);
		else
			sides.push_front(side);
		while (isdigit(str[idx]))
			++idx;
	}
	
	if (sides[0] < sides[1] + sides[2])
		return 1;
	return 0;
}

int parseLine2(const std::string& str) {
	static std::deque<int> triangleA;
	static std::deque<int> triangleB;
	static std::deque<int> triangleC;
	
	std::deque<int>* triangle = nullptr;

	std::string::size_type idx = 0;
	int loop = 0;
	int side = 0;
	int result = 0;

	while (idx < str.size()) {
		if (loop == 0)
			triangle = &triangleA;
		else if (loop == 1)
			triangle = &triangleB;
		else
			triangle = &triangleC;
		while (!isdigit(str[idx]) && idx < str.size())
			++idx;
		side = atoi(&str[idx]);
		if (triangle->empty() || side < triangle->at(0))
			triangle->push_back(side);
		else
			triangle->push_front(side);
		while (isdigit(str[idx]))
			++idx;
		if (triangle->size() == 3) {
			if (triangle->at(0) < triangle->at(1) + triangle->at(2))
				++result;
			triangle->clear();
		}
		loop++ ;
	}
	return result;
}

int main() {
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "Couldn't open file ./Input.txt : " << strerror(errno) << std::endl;
		return errno;
	}
	int part = 1;
	std::cout << "Wich part ? (1 or 2)\n";
	std::cin >> part;
	std::string line;

	int result = 0;
	while (!input.eof()) {
		getline(input, line);
		if (part == 1)
			result += parseLine(line);
		else {
			result += parseLine2(line);
		}
	}
	std::cout << "result is " << result << std::endl;

	return 0;
}