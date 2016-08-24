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
	int max = 20;

	while (fin.getline(line, sizeof(line)))
	{
		if (max <= 0)
			break;
		fout << line << "=" << url_validator.match(line) << endl;
		max--;
	}
	fin.clear();
	fin.close();
	fout.close();
	return 0;
}
