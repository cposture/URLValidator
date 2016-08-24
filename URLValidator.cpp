#include "URLValidator.h"
#include <regex>
#include <iostream>

URLValidator::URLValidator()
        : m_ipv4(R"((?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)(?:\.(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)){3})")
{
	/*
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
	*/
	//m_domain = m_domain
	//	+ R"(()"
	//	+ R"((?:[a-z\u00a1-\ffff0-9]))"
	//	+ R"(|()"
	//	+ R"((?:[a-z\u00a1-\ffff0-9]))"
	//	+ R"((?:[a-z\u00a1-\ffff0-9-]*))"
	//	+ R"((?:[a-z\u00a1-\ffff0-9])))"
	//	+ R"(\.)"
	//	+ R"()*)";
	m_domain = R"([a-z\u00a1-\uffff0-9](?:[a-z\u00a1-\uffff0-9-]{0,61}[a-z\u00a1-\uffff0-9])?)";
	m_toplabel = R"((?:\.(?!-)[a-z\u00a1-\uffff0-9-]{1,63})*)"; //���Ա�ʾ���ұߵ����־�������������ֿ�ͷ
	m_hostname = m_domain + m_toplabel;
	/*
	m_hostname :
	1. �á�.���ָ������־�������־����ĸ�������ֿ�ͷ�ͽ�����Ҳ���ܰ����� - ���ַ������ұߵ����־���������ֿ�ͷ
	2. Host software MUST handle host names of up to 63 characters and SHOULD handle host names of up to 255 characters.
	*/
    m_host = "("
			+ m_hostname
            + "|localhost)";
}

bool URLValidator::match(const std::string &value)
{
	std::string pattern_str;
	pattern_str =
                R"(^(?:http(s)?)://)"					//http(s)
                R"((?:\S+(?::\S*)?@)?)"					//�û�:����,����ʡ�ԡ�<�û���>:<����>@������ :<����>��
				R"((?:)" + m_ipv4 + "|" + m_host + ")"	//host
				R"((?::\d{2,5})?)"						//�˿ڣ���:port�� ����ʡ�ԣ�
                R"((?:[/?#][^\s]*)?)";					//hpath
	std::cout << pattern_str << std::endl;
	std::regex pattern(m_domain);

	return std::regex_match(value, pattern);
}

