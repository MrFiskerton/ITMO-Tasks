#include <cstdio>
#include <sstream>
#include <string>
#include "lazy_string.h"
#include "lazy_string.cpp"

int main() {
    printf("\nChecking lengths:\n\n");

    printf("Checking empty constructor\n");
    lazy_string ecls;
    printf("Expected: 0\n");
    printf("Returned: %d\n", ecls.length());

    printf("Checking empty string\n");
    lazy_string els("");
    printf("Expected: 0\n");
    printf("Returned: %d\n", els.length());

    std::string s = "hello world";
    lazy_string ls(s);
    printf("Checking string: %s\n", s.c_str());
    printf("Expected: %d\n", s.length());
    printf("Returned: %d\n", ls.length());

    printf("\nChecking immutability of constructor:\n\n");

    s = "hello world";
    printf("Checking string: %s\n", s.c_str());
    std::string cs = s;
    lazy_string cls(s);
    s[4] = ' ';
    printf("symbol 4 changed ->: %s\n", s.c_str());
    printf("Expected: %c\n", cs[4]);
    printf("Returned: %c\n", static_cast<char>(cls[4]));
    printf("Expected: %s\n", cs.c_str());
    printf("Returned: %s\n", static_cast<std::string>(cls).c_str());

    printf("\nChecking chars:\n\n");

    s = "hello world";
    printf("Checking string: %s\n", s.c_str());
    printf("Symbol 4 checking:\n");
    lazy_string ccls(s);
    printf("Expected: %c\n", s[4]);
    printf("Returned: %c\n", static_cast<char>(ccls[4]));
    s[4] = 'p';
    ccls[4] = 'p';
    printf("symbol 4 changed ->: %s\n", s.c_str());
    printf("Expected: %c\n", s[4]);
    printf("Returned: %c\n", static_cast<char>(ccls[4]));

    printf("\nChecking substring:\n\n");

    s = "hello world";
    std::string sss = s.substr(0, 4);
    printf("Checking string: %s\n", s.c_str());
    lazy_string fssls(s);
    lazy_string ssls = fssls.substr(0, 4);
    printf("Expected: %d\n", sss.length());
    printf("Returned: %d\n", ssls.length());
    printf("Expected: %s\n", sss.c_str());
    printf("Returned: %s\n", static_cast<std::string>(ssls).c_str());

    printf("\nChecking immutability of constructor of substring:\n\n");

    s = "hello world";
    sss = s.substr(0, 4);
    printf("Checking string: %s\n", s.c_str());
    lazy_string fcfssls(s);
    lazy_string fcssls = fcfssls.substr(0, 4);
    sss[3] = 'p';
    fcssls[3] = 'p';
    printf("Expected: %s %s\n", s.c_str(), sss.c_str());
    printf("Returned: %s %s\n", static_cast<std::string>(fcfssls).c_str(), static_cast<std::string>(fcssls).c_str());
    s = "hello world";
    sss = s.substr(0, 4);
    lazy_string scfssls(s);
    lazy_string scssls = scfssls.substr(0, 4);
    s[3] = 'p';
    scfssls[3] = 'p';
    printf("Expected: %s %s\n", s.c_str(), sss.c_str());
    printf("Returned: %s %s\n", static_cast<std::string>(scfssls).c_str(), static_cast<std::string>(scssls).c_str());

    printf("\nChecking immutability of const lazy string:\n\n");

    s = "hello world";
    const lazy_string cmols(s);
    const char* c = &cmols[1];

    printf("\nChecking streams:\n\n");

    printf("Checking input stream\n");
    std::stringstream ss;
    std::string yas = "yet_another hello world";
    lazy_string yals;
    ss << yas;
    ss >> yals;
    ss = std::stringstream();
    ss << yas;
    std::string yasc;
    ss >> yasc;
    printf("Expected: %s\n", yasc.c_str());
    printf("Returned: %s\n", static_cast<std::string>(yals).c_str());

    printf("Checking output stream\n");
    yas = "yet_another hello world";
    lazy_string yalsfo(yas);
    ss = std::stringstream();
    ss << yas;
    printf("Expected: %s\n", ss.str().c_str());
    ss = std::stringstream();
    ss << yalsfo;
    printf("Returned: %s\n", ss.str().c_str());
    return 0;
}
