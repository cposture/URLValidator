#include <string>
#include <vector>

class URLValidator
{
public:
	URLValidator();
	
	bool match(const std::string &value);
private:
	std::string m_host;
	std::string m_ipv4;
	std::string m_domain;
	std::string m_hostname;
	std::string m_tld;
	std::vector<std::string> m_schemes;
};