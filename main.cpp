#include <iostream>
#include <string>

using namespace std;

int main()
{
	std::string raw_str = R"(First line.\nSecond line.\nEnd of message.\n)";
	cout << raw_str << endl;
	return 0;
}