#include <string>
#include <regex>

class URLValidator
{
public:
	URLValidator();

	bool match(const std::string &value);
private:
	std::string m_host;
	std::string m_ipv4;
	std::string m_domain;
	std::string m_toplabel;
	std::string m_hostname;
	std::string m_tld;
	std::string m_unicode;
	std::string m_pattern;
	std::string m_hsegment;
	std::regex m_pattern_reg;
};
