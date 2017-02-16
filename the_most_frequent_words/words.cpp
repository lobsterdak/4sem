#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <string> 
#include <cstdlib>
#include <cctype>
#include <fstream>

std::string prepare(const std::string& str) {
	std::string result = str;
	std::transform(str.begin(), str.end(), result.begin(), ::tolower);
	if (!isalpha(str[str.size() - 1]))
		result.pop_back();
	return result;
}

struct Statistics
{
	int cout;
	std::string word;

};

bool compare(const Statistics& a, const Statistics& b)
{
	return (a.cout > b.cout);
}
int main() 
{
	int N = 20;
	std::map<std::string, int> map;
	std::ifstream file("file.txt");
	if (file.is_open()) 
	{
		std::string word;
		while (!file.eof())
		{
			file >> word;
			word = prepare(word);
			//std::cout << word << i << "\n";
			map[word] ++;
		}
		std::vector<Statistics> array;
		for (std::map<std::string, int>::iterator it = map.begin(); it != map.end(); it++)
		{
			Statistics element;
			element.cout = it->second;
			element.word = it->first;
			array.push_back(element);
			//std::cout << it->first << " " << it->second << "\n";
		}
		std::sort(array.begin(), array.end(), compare);
		std::cout << "The final result\n";
		for (int i = 0; ((unsigned int)i < array.size() && (i < N)); i++) {
			std::cout << array[i].word << "-" << array[i].cout << "\n";
		}
	}
	file.close();
	system("pause");
	return 0;
}