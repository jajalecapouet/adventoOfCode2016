#include <iostream>
#include <fstream>
#include <map>

void resetData(bool& i, bool& f, bool& t, char& a, char& b)
{
	i = false;
	f = false;
	t = true;
	a = 0;
	b = 0;
}

bool goToNextLine(std::ifstream& in, bool& i, bool& f, bool& t, char& a, char& b)
{
	resetData(i, f, t, a, b);
	char c = in.get();
	while (c != '\n' && c != EOF)
		c = in.get();
	if (c == EOF)
		return true;
	return false;
}

int main()
{
	std::ifstream in("./Input.txt");
	if (in.fail()) {
		std::cerr << "couldn't read file ./Input.txt";
		return 1;
	}
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;

	int result = 0;
	char a;
	char b;
	char c;
	bool found;
	bool aTurn;
	bool inbrackets;
	resetData(inbrackets, found, aTurn, a, b);
	if (part == 1) {
		while (in.get(c))
		{
			if (c == '\n') {
				result += found;
				resetData(inbrackets, found, aTurn, a, b);
			}
			else if (c == '[') {
				inbrackets = true;
				a = 0;
				b = 0;
				aTurn = true;
			}
			else if (c == ']') {
				inbrackets = false;
				a = 0;
				b = 0;
				aTurn = true;
			}
			else if (!found || inbrackets)
			{
				if (aTurn)
				{
					if (!a || !b) {
						a = c;
						aTurn = false;
					}
					else if (a == c) {
						if (inbrackets) {
							if (goToNextLine(in, inbrackets, found, aTurn, a, b))
								break;
						}
						else
							found = true;
					}
					else {
						if (c == b) {
							a = c;
							b = 0;
						}
						else
						{
							a = b;
							b = c;
						}
						aTurn = false;
					}
				}
				else
				{
					if (!b) {
						if (c != a)
							b = c;
						else
							aTurn = true;
					}
					else if (b == c)
						aTurn = true;
					else {
						a = b;
						b = c;
					}
				}
			}
		}
	}
	else {
		std::map<std::string, bool> aba;
		std::pair<std::map<std::string, bool>::iterator, bool> insertResult;
		std::string newAba;
		while (in.get(c)) {
			if (c == '\n') {
				aba.clear();
				resetData(inbrackets, found, aTurn, a, b);
			}
			else if (c == '[') {
				inbrackets = true;
				a = 0;
				b = 0;
			}
			else if (c == ']') {
				inbrackets = false;
				a = 0;
				b = 0;
			}
			else {
				if (!a)
					a = c;
				else if (!b) {
					if (a != c)
						b = c;
				}
				else if (a != c) {
					a = b;
					if (c != b)
						b = c;
					else
						b = 0;
				}
				else {
					newAba += inbrackets * b + !inbrackets * a;
					newAba += inbrackets * a + !inbrackets * b;
					newAba += inbrackets * b + !inbrackets * a;
					insertResult = aba.insert(std::make_pair(newAba, !inbrackets));
					newAba.clear();
					if (insertResult.first->second == inbrackets) {
						result += 1;
						aba.clear();
						if (goToNextLine(in, inbrackets, found, aTurn, a, b))
							break;
					}
					a = b;
					b = c;
				}
			}
		}
	}
	std::cout << "result is " << result;
	return 0;
}