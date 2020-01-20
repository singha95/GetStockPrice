
#include <stdio.h>
#include <iostream>
#include <regex>
#include <stdlib.h>

int main(){ 
    std::string s = "<span class=\"Trsdu(0.3s) Fw(b) Fz(36px) Mb(-4px) D(ib)\">1,480.39</span>";
    std::regex rgx("<span class=\"Trsdu\\(0.3s\\) Fw\\(b\\) Fz\\(36px\\) Mb\\(-4px\\) D\\(ib\\)\">([\\s\\S]*?)</span>");
    std::smatch matches;
    bool b = std::regex_search(s, matches, rgx);
    std::cout << matches[0] << std::endl; 
    std::cout << b << matches[1] << std::endl; 
}