#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<bool> Row;
typedef std::vector<Row> Screen;

std::ostream& operator<<(std::ostream & o, const Row & r) {
	for (bool b : r)
	{
		if (b)
			o << '#';
		else
			o << ' ';
	}
	return o;
}

std::ostream& operator<<(std::ostream& o, const Screen& s) {
	for (Row r : s)
		o << r << std::endl;
	return o;
}

void doRect(Screen& screen, int w, int t) {
	for (int y = 0; y < t; ++y) {
		for (int x = 0; x < w; ++x) {
			screen[y][x] = true;
		}
	}
}

//I wanted to use less memory than just copy all
//I guessed that we can't reassignate a bool on a screen before he has been copied by 
//another pixel screen or a temporal memory
//I guessed that right-shift is the same thing that left-shift
//with left-shift = size - right-shift, and the shorter is the shift, better it is
void doRowShift(Screen& screen, int row, int shift) {
	std::vector<bool> temp;
	if (shift <= 25) {
		temp.resize(shift);
		for (std::vector<bool>::size_type idx = 0; idx < temp.size(); ++idx)
			temp[shift - 1 - idx] = screen[row][49 - idx];
		for (int i = 49; i >= shift; --i)
			screen[row][i] = screen[row][i - shift];
		for (int i = shift - 1; i >= 0; --i)
			screen[row][i] = temp[i];
	}
	else {
		temp.resize(50 - shift);
		for (std::vector<bool>::size_type idx = 0; idx < temp.size(); ++idx)
			temp[idx] = screen[row][idx];
		for (int i = 0; i < shift; ++i)
			screen[row][i] = screen[row][i + 50 - shift];
		for (int i = shift; i < 50; ++i)
			screen[row][i] = temp[i - shift];
	}
}

void doColShift(Screen& screen, int col, int shift) {
	std::vector<bool> temp;
	if (shift <= 3) {
		temp.resize(shift);
		for (std::vector<bool>::size_type idx = 0; idx < temp.size(); ++idx)
			temp[shift - 1 - idx] = screen[5 - idx][col];
		for (int i = 5; i >= shift; --i)
			screen[i][col] = screen[i - shift][col];
		for (int i = shift - 1; i >= 0; --i)
			screen[i][col] = temp[i];
	}
	else {
		temp.resize(6 - shift);
		for (std::vector<bool>::size_type idx = 0; idx < temp.size(); ++idx)
			temp[idx] = screen[idx][col];
		for (int i = 0; i < shift; ++i)
			screen[i][col] = screen[i + 6 - shift][col];
		for (int i = shift; i < 6; ++i)
			screen[i][col] = temp[i - shift];
	}
}

void applyInstruction(const std::string& str, Screen& screen)
{
	int a;
	int b;
	std::string::size_type idx;
	if (isdigit(str[5])) {
		a = atoi(&str[5]);
		idx = str.find('x', 6) + 1;
		b = atoi(&str[idx]);
		doRect(screen, a, b);
	}
	else if (str[11] == 'y') {
		a = atoi(&str[13]);
		idx = str.find('y', 16) + 2;
		b = atoi(&str[idx]);
		doRowShift(screen, a, b % 50);
	}
	else {
		a = atoi(&str[16]);
		idx = str.find('y', 19) + 2;
		b = atoi(&str[idx]);
		doColShift(screen, a, b % 6);
	}
}

int countTrue(const Screen& screen) {
	int res = 0;
	for (int y = 0; y < 6; ++y) {
		for (int x = 0; x < 50; ++x)
			res += screen[y][x];
	}
	return res;
}

int main()
{
	std::ifstream in("./Input.txt");
	if (in.fail()) {
		std::cerr << "Couldn't open file.\n";
		return errno;
	}
	std::string line;
	Screen screen(6, Row(50, false));
	while (!in.eof()) {
		getline(in, line);
		applyInstruction(line, screen);
	}
	std::cout << "result is " << countTrue(screen) << " lights on.\n" << std::endl;
	std::cout << screen;
	return 0;
}