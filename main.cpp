#include <iostream>
#include <string>
#include <fstream>
#include "URLValidator.h"

using namespace std;

int main()
{
	URLValidator url_validator;
	std::ifstream fin("foo.txt", std::ios::in);
	std::ofstream fout("result", std::ios::out);
	char line[1024] = { 0 };
	int max = 12000;
	int valid = 0;
	int invalid = 0;

	while (fin.getline(line, sizeof(line)))
	{
		if (max <= 0)
			break;
		try{
			if (url_validator.match(line))
			{
				valid++;
			}
			else
			{
				invalid++;
			}
		}
		catch (...)
		{
			;
		}
		max--;
	}
	fout << "valid:" << valid << "  invalid:" << invalid;
	fin.clear();
	fin.close();
	fout.close();
	return 0;
}
