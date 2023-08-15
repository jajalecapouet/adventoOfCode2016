#include <iostream>
#include <fstream>
#include <string>

long long recuMark(std::string::size_type start, std::string::size_type len, const std::string& line, bool part1) {
	long long res = 0;
	long long times;
	std::string::size_type sub;

	for (std::string::size_type idx = start; idx < start + len; ++idx) {
		if (line[idx] == '(') {
			sub = atoi(&line[++idx]);
			idx = line.find('x', idx + 1) + 1;
			times = atoi(&line[idx]);
			idx = line.find(')', idx + 1) + 1;
			if (part1)
				res += (times * sub);
			else
				res += times * recuMark(idx, sub, line, part1);
			idx += sub - 1;
		}
		else
			++res;
	}
	return res;
}

int main() {
	std::ifstream in("./Input.txt");
	std::string line;

	if (in.fail())
		return errno;
	getline(in, line);
	std::cout << "result part 1 is " << recuMark(0, line.size(), line, true) << std::endl;
	std::cout << "result part 2 is " << recuMark(0, line.size(), line, false) << std::endl;
	return 0;
}