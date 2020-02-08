#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <curl/curl.h>
#include "parse.hpp"

int main()
{
    std::ifstream stocks;
    std::string x; 
    stocks.open("portfolio.txt");
    if (!stocks) {
        std::cout << "Unable to open file";
        exit(1); 
    }

    CURL *curl;
    curl_global_init(0);    
    while (stocks >> x) {
        //${font}${color}AMZN${alignr}${exec /home/angad/scripts/GetStockPrice/parse_prices -p amzn}
        //s.substr(0, s.find(delimiter))
        std::string symbol = x.substr(0, x.find(","));
        float price = std::stod(x.substr(x.find(",") + 1, x.size() - 1));

        //Argument for the color of price 
        std::string color("green"); 
        std::string url("https://ca.finance.yahoo.com/quote/"); 
        url += symbol; 
        float cPrice = get_price(curl, url.c_str());
        if (cPrice < price){ 
            color = "red"; 
        }
        std::cout << "${font}${color}" << x << "{color " << color << "}${alignr}" << cPrice << std::endl; 
    }
    
    curl_global_cleanup();
    stocks.close(); 
    return 0 ;
}