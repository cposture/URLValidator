#include "URLValidator.h"
#include <regex>
#include <iostream>

URLValidator::URLValidator()
        : m_ipv4(R"((?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)(?:\.(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)){3})")
{
	/*
		;HTTP(超文本传输协议)
		httpurl        = "http://" hostport [ "/" hpath [ "?" search ]]
		hpath          = hsegment *[ "/" hsegment ]
		hsegment       = *[ uchar | ";" | ":" | "@" | "&" | "=" ]
		search         = *[ uchar | ";" | ":" | "@" | "&" | "=" ]

		hostport       = host [ ":" port ]
		host           = hostname | hostnumber
		hostname       = *[ domainlabel "." ] toplabel
		domainlabel    = alphadigit | alphadigit *[ alphadigit | "-" ] alphadigit
		toplabel       = alpha | alpha *[ alphadigit | "-" ] alphadigit
	*/
	m_domain = m_domain
		+ R"(()"
		+ R"((?:[a-z\u00a1-\ffff0-9]))"
		+ R"(|()"
		+ R"((?:[a-z\u00a1-\ffff0-9]))"
		+ R"((?:[a-z\u00a1-\ffff0-9-]*))"
		+ R"((?:[a-z\u00a1-\ffff0-9])))"
		+ R"(\.)"
		+ R"()*)";
	m_toplabel = m_toplabel
		+ R"((?:[a-z\u00a1-\ffff]))"
		+ R"(|()"
		+ R"((?:[a-z\u00a1-\ffff]))"
		+ R"((?:[a-z\u00a1-\ffff0-9-]*))"
		+ R"((?:[a-z\u00a1-\ffff0-9])))";
	m_hostname = m_domain + m_toplabel;
	/*
	m_hostname :
	1. 用“.”分隔的域标志串，域标志以字母或者数字开头和结束，也可能包含“ - ”字符。最右边的域标志不能以数字开头
	2. Host software MUST handle host names of up to 63 characters and SHOULD handle host names of up to 255 characters.
	*/
    m_host = "("
			+ m_hostname
            + "|localhost)";

    m_schemes.push_back("http");
    m_schemes.push_back("https");
    m_schemes.push_back("ftp");
    m_schemes.push_back("ftps");
}

bool URLValidator::match(const std::string &value)
{
	std::string pattern_str;
	pattern_str =
                R"(^http(s)?://)"						//http(s)
                //R"((?:\S+(?::\S*)?@)?)"					//用户:密码,可以省略“<用户名>:<密码>@”，“ :<密码>”
                R"((?::\d{2,5})?)"						//端口，“:port” 可以省略，
                R"((?:[/?#][^\s]*)?)";					//hpath
	std::cout << pattern_str << std::endl;
	std::regex pattern(m_domain);

	return std::regex_match(value, pattern);
}

