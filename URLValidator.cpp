#include "URLValidator.h"
#include <regex>
#include <iostream>

URLValidator::URLValidator()
        : m_unicode(R"(\u00a1-\ffff)")
        , m_ipv4(R"((?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)(?:\.(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)){3})")
{
    //m_domain = R"((?:\.(?!-)[a-z)" + m_unicode + R"(0-9-]{1,63}(?<!-))*)";
	m_domain = R"((?:\.(?!-)[a-z)" + m_unicode + R"(0-9-]{1,63})*)";
    m_hostname = R"([a-z)" + m_unicode + R"(0-9](?:[a-z)" + m_unicode + R"(0-9-]{0,61}[a-z)" + m_unicode + R"(0-9])?)";
    m_tld = R"(\.)"
            R"((?!-))"
            R"((?:[a-z' + ul + '-]{2,63})"
            R"(|xn--[a-z0-9]{1,59}))"
            //R"((?<!-))"
            R"(\.?)";
	/*
	m_hostname :
	1. �á�.���ָ������־�������־����ĸ�������ֿ�ͷ�ͽ�����Ҳ���ܰ����� - ���ַ������ұߵ����־���������ֿ�ͷ
	2. Host software MUST handle host names of up to 63 characters and SHOULD handle host names of up to 255 characters.
	*/
    m_host = "("
		+ m_hostname
            + m_domain 
            + m_tld
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
                R"(^(?:[a-z0-9\.\-\+]*)://)"
                R"((?:\S+(?::\S*)?@)?)"					//�û�:����,���ܻ�ʡ�ԡ�<�û���>:<����>@������ :<����>��
                R"((?:)" + m_ipv4 + "|"  + m_host + ")"	//
                //R"((?::\d{2,5})?)"						//�˿ڣ�:port ����ʡ�ԣ�
 				R"((?::[0-6][0-5][0-5][0-3][0-5])?)"
                R"((?:[/?#][^\s]*)?)";					//hpath
	std::cout << pattern_str << std::endl;
	std::regex pattern(pattern_str);

	return std::regex_match(value, pattern);
}

