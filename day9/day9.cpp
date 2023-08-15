#include <iostream>
#include <fstream>
#include <string>

long long recuMark(std::string::size_type start, std::string::size_type len, const std::string& line) {
	long long res = 0;
	long long times;
	std::string::size_type sub;
	for (std::string::size_type idx = start; idx < start + len; ++idx) {
		if (line[idx] == '(') {
			sub = atoi(&line[++idx]);
			idx = line.find('x', idx + 1) + 1;
			times = atoi(&line[idx]);
			idx = line.find(')', idx + 1) + 1;
			res += times * recuMark(idx, sub, line);
			idx += sub - 1;
		}
		else
			++res;
	}
	return res;
}

int main() {
	std::ifstream in("./Input.txt");
	if (in.fail()) {
		return errno;
	}
	std::string line;
	long long res = 0;
	long long times;
	std::string::size_type sub;
	getline(in, line);
	for (std::string::size_type idx = 0; idx < line.size(); ++idx) {
		if (line[idx] == '(') {
			sub = atoi(&line[++idx]);
			idx = line.find('x', idx + 1) + 1;
			times = atoi(&line[idx]);
			idx = line.find(')', idx + 1) + 1;
			res += (times * sub);
			idx += sub - 1;
		}
		else
			++res;
	}
	std::cout << "result part 1 is " << res << std::endl;
	std::cout << "result part 2 is " << recuMark(0, line.size(), line) << std::endl;
	return 0;
}