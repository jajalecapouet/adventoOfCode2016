#include <iostream>
#include <fstream>
#include <vector>
#include <map>

int main()
{
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "couldn't read file ./Input.txt";
		return 1;
	}
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	char c;
	std::vector<std::map<char, unsigned int>> letters;
	std::vector<std::map<char, unsigned int>>::size_type idx = 0;
	while (input.get(c))
	{
		if (c == '\n')
			idx = 0;
		else
		{
			if (idx >= letters.size())
				letters.push_back(std::map<char, unsigned int>());
			letters[idx][c] += 1;
			idx++;
		}
	}
	std::cout << "result is ";
	idx = 0;
	std::pair<unsigned, char> letter;
	while (idx < letters.size())
	{
		if (part == 1)
			letter.first = 0;
		else
			letter.first = ~0;
		for (std::map<char, unsigned int>::const_iterator cit = letters[idx].begin(); cit != letters[idx].end(); ++cit)
		{
			if (part == 1 && cit->second >= letter.first)
			{
				letter.first = cit->second;
				letter.second = cit->first;
			}
			else if (part != 1 && cit->second <= letter.first)
			{
				letter.first = cit->second;
				letter.second = cit->first;
			}
		}
		std::cout << letter.second;
		++idx;
	}
	return 0;
}