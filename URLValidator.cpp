#include "URLValidator.h"
#include <regex>
#include <iostream>

URLValidator::URLValidator()
        : m_ipv4(R"((?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)(?:\.(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)){3})")
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
	std::string unicode_str = "\u00a1-\uffff";
	m_domain = m_domain
		+ R"((()"
		+ R"((?:[a-z)" + unicode_str + R"(0-9]))"
		+ R"(|()"
		+ R"((?:[a-z)" + unicode_str + R"(0-9]))"
		+ R"((?:[a-z)" + unicode_str + R"(0-9-]*))"
		+ R"((?:[a-z)" + unicode_str + R"(0-9])))"
		+ R"()\.)*)";

	m_toplabel = R"(([a-z)" + unicode_str + R"(])" 
			+ R"(|)" 
			+ R"([a-z)" + unicode_str + R"(])" 
			+ R"((?:[a-z)" + unicode_str + R"(0-9-]*))" 
			+ R"((?:[a-z)" + unicode_str + R"(0-9])))"; //���Ա�ʾ���ұߵ����־�������������ֿ�ͷ

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
  std::string unicode_str = "\u00a1-\uffff";
  hsegment = hsegment
        + R"(((?:[a-z)" + unicode_str + R"(0-9\+\.\*\(\)\$-_!',;:&=@]))" // alphadigit
        + R"(|(?:%[0-9a-f]{2}))*)";

	pattern_str =
                R"(^(?:http(s)?)://)"					//http(s)
                R"((?:\S+(?::\S*)?@)?)"					//�û�:����,����ʡ�ԡ�<�û���>:<����>@������ :<����>��
				R"((?:)" +  m_host + ")"				//����
				R"((?::\d{2,5})?)"						//�˿ڣ���:port�� ����ʡ��
                R"((/)" + hsegment + R"()*)"			//
                R"((\?)" + hsegment + R"()?)";
	std::regex pattern(pattern_str);
	return std::regex_match(value, pattern);
}
