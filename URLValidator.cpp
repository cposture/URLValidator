#include "URLValidator.h"
#include <regex>
#include <iostream>

URLValidator::URLValidator()
{
	/*
	RFC 1738 :
		;HTTP(���ı�����Э��)
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
		1. �á�.���ָ������־�������־����ĸ�������ֿ�ͷ�ͽ�����Ҳ���ܰ����� - ���ַ������ұߵ����־���������ֿ�ͷ
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

	m_toplabel = R"((?:(?![-0-9])[a-z)" + m_unicode + R"(0-9-]{1,63})*)"; //���Ա�ʾ���ұߵ����־�������������ֿ�ͷ

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
		R"((?:\S+(?::\S*)?@)?)"					//�û�:����,����ʡ�ԡ�<�û���>:<����>@������ :<����>��
		R"((?:)" + m_host + ")"					//����
		R"((?::\d{2,5})?)"						//�˿ڣ���:port�� ����ʡ��
		R"((/)" + hsegment + R"()*)"			//hpath
		R"((\?)" + hsegment + R"()?)"			//search
		R"(\s?$)";
	std::regex pattern(pattern_str);
	return std::regex_match(value, pattern);
}
