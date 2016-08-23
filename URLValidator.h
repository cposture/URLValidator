#include <regex.h>
#include <string>

class URLValidator
{
public:
	URLValidator();
	~URLValidator();
	
	bool isValid(std::string value);
private:
	std::string m_unicode;
	std::string m_ipv4;
	std::string m_hostname;
	std::string m_domain;
	std::string m_tld;
	std::string m_host;
	std::vector<std::string> schemes;
};