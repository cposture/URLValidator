#include "URLValidator.h"
#include <regex>
#include <iostream>

URLValidator::URLValidator()
        : m_unicode(R"(\u00a1-\uffff)")
        , m_ipv4(R"((?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)(?:\.(?:25[0-5]|2[0-4]\d|[0-1]?\d?\d)){3})")
{
    m_domain = R"((?:\.(?!-)[a-z)" + m_unicode + R"(0-9-]{1,63}(?<!-))*)";
    m_hostname = R"([a-z)" + m_unicode + R"(0-9](?:[a-z)" + m_unicode + R"(0-9-]{0,61}[a-z)" + m_unicode + R"('0-9])?)";
    m_tld = m_tld +
            R"(\.)"
            R"((?!-))"
            R"((?:[a-z)" + m_unicode + R"(-]{2,63})"
            R"(|xn--[a-z0-9]{1,59}))"
            R"((?<!-))"
            R"(\.?)";

    m_host = m_host
               + "("
               + m_hostname
               + m_domain
               + m_domain
               + m_tld
               + "|localhost";

    m_schemes.push_back("http");
    m_schemes.push_back("https");
    m_schemes.push_back("ftp");
    m_schemes.push_back("ftps");
}

bool URLValidator::match(const std::string &value)
{
    std::string pattern_str = pattern_str +
                              R"(^(?:[a-z0-9\.\-\+]*)://)"
                              R"((?:\S+(?::\S*)?@)?)"
                              R"(?:)" + m_ipv4 + "|"  + m_host + ")"
                              R"((?::\d{2,5})?)"
                              R"((?:[/?#][^\s]*)?)";

    std::cout << pattern_str << std::endl;
    std::regex pattern(pattern_str);

    return std::regex_match(value, pattern);
}

