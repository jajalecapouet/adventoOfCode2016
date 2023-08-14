#pragma warning (disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

typedef std::map<char, int> CharMap;
typedef std::map<int, std::set<char>, std::greater<int>> IntMap;

char charrade(int c, int add) {
	if (c == '-')
		return ' ';
	char toReturn = ((c + add - 'a') % 26) + 'a';
	return toReturn;
}

char getNextChar(int uid, const IntMap& iMap) {
	static bool firstCall = true;
	static bool endReached = false;
	static int newMapDetector = 0;
	static IntMap::const_iterator citI = iMap.begin();
	static std::set<char>::const_iterator citC = citI->second.begin();
	if (newMapDetector != uid) {
		firstCall = true;
		endReached = false;
		newMapDetector = uid;
		citI = iMap.begin();
		citC = citI->second.begin();
	}
	if (firstCall) {
		firstCall = false;
		return *citC;
	}
	if (endReached)
		return 0;
	if (++citC == citI->second.end()) {
		if (++citI == iMap.end()) {
			endReached = true;
			return 0;
		}
		citC = citI->second.begin();
		return *citC;
	}
	return *citC;
}

int parseLine(const std::string& str) {
	int result = 0;
	CharMap cMap;
	IntMap iMap;
	static int uid = 0;
	int modulo = 0;

	++uid;
	std::string::size_type idx = 0;
	while (!isdigit(str[idx])) {
		if (str[idx] != '-')
			cMap[str[idx]] += 1;
		++idx;
	}
	for (CharMap::const_iterator cit = cMap.begin(); cit != cMap.end(); ++cit)
		iMap[cit->second].insert(cit->first);
	result += atoi(&str[idx]);
	while (!isalpha(str[idx]))
		++idx;
	while (str[idx] != ']') {
		if (getNextChar(uid, iMap) != str[idx])
			return 0;
		++idx;
	}
	return result;
}

void parseLinePart2(std::string& str, const char* toCmp) {
	static int loop = 0;
	std::string::size_type idx = 0;
	std::string::size_type idxDigit = 0;
	int jump = 0;

	++loop;
	while (!isdigit(str[idxDigit]))
		++idxDigit;
	jump = atoi(&str[idxDigit]);
	while (toCmp[idx]) {
		str[idx] = charrade(str[idx], jump);
		if (toCmp[idx] != str[idx])
			return;
		++idx;
	}
	for (std::string::size_type idx2 = strlen(toCmp); idx2 < idxDigit; ++idx2)
		str[idx2] = charrade(str[idx2], jump);
	std::cout << "result could be " << jump << " at line " << loop << " : " << str << std::endl;
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
	int loop = 0;
	while (!input.eof()) {
		getline(input, line);
		if (part == 1)
			result += parseLine(line);
		else
			parseLinePart2(line, "north");
	}
	if (part == 1)
		std::cout << "result is : " << result << std::endl;
	return 0;
}