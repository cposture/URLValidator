#include "URLValidator.h"
#include <regex>
#include <iostream>

URLValidator::URLValidator()
{
	/*
	RFC 1738 :
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

	domainlabel :
		1. 用“.”分隔的域标志串，域标志以字母或者数字开头和结束，也可能包含“ - ”字符。最右边的域标志不能以数字开头
		2. Host software MUST handle host names of up to 63 characters and SHOULD handle host names of up to 255 characters.
	*/
	m_unicode = "";
	m_ipv4 = R"((?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)(?:\.(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)){3})";

	m_domain = m_domain
		+ R"((()"
		+ R"((?:[a-z)" + m_unicode + R"(0-9]))"
		+ R"(|()"
		+ R"((?:[a-z)" + m_unicode + R"(0-9]))"
		+ R"((?:[a-z)" + m_unicode + R"(0-9-]*))"
		+ R"((?:[a-z)" + m_unicode + R"(0-9])))"
		+ R"()\.)*)";

	m_toplabel = R"((?:(?![-0-9])[a-z)" + m_unicode + R"(0-9-]{1,63})*)"; //用以表示最右边的域标志，它不能以数字开头

	m_hostname = m_domain + m_toplabel;

    m_host = "("
			+ m_hostname
			+ "|"
			+ m_ipv4
            + "|localhost)";
}

bool URLValidator::match(const std::string &value)
{
	std::string pattern_str;
	std::string hsegment;

    hsegment = hsegment
		+ R"(((?:[a-z)" + m_unicode + R"(0-9\+\.\*\(\)\$-_!',;:&=@]))" // alphadigit
        + R"(|(?:%[0-9a-f]{2}))*)";

	pattern_str =
		R"(^(?:http(s)?)://)"					//http(s)
		R"((?:\S+(?::\S*)?@)?)"					//用户:密码,可以省略“<用户名>:<密码>@”，“ :<密码>”
		R"((?:)" + m_host + ")"					//主机
		R"((?::\d{2,5})?)"						//端口，“:port” 可以省略
		R"((/)" + hsegment + R"()*)"			//hpath
		R"((\?)" + hsegment + R"()?)"			//search
		R"(\s?$)";
	std::regex pattern(pattern_str);
	return std::regex_match(value, pattern);
}
