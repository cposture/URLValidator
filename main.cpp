#include <iostream>
#include <string>
#include "URLValidator.h"

using namespace std;

int main()
{
	std::string url = R"(http://127.0.0.1/w/cpp/regex/regex_match)";

    cout << url << endl;

	URLValidator url_validator;

	cout << url_validator.match(url) << endl;
	return 0;
}