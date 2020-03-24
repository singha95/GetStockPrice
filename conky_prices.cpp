#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <curl/curl.h>
#include "parse.h"

int main()
{
    std::ifstream stocks;
    std::string x; 
    stocks.open("/home/angad/scripts/GetStockPrice/portfolio.txt");
    if (!stocks) {
        std::cout << "Unable to open file";
        exit(1); 
    }

    CURL *curl;
    curl_global_init(0);    
    while (stocks >> x) {
        std::string symbol = x.substr(0, x.find(","));

        //Argument for the color of price 
        std::string url("https://ca.finance.yahoo.com/quote/"); 
        url += symbol; 
        std::string response = filter_stock_html(get_html(curl, url.c_str()));
        float price =  get_price(response); 
        float percent = get_percent(response);
        std::string color("green");
        if (percent < 0){ 
            color = "red"; 
        } 
        std::cout << "${font}${color}" << symbol << "${color " << color << "}${alignr}" << price << " (" << percent << "%)" << std::endl; 
    }
    
    curl_global_cleanup();
    stocks.close(); 
    return 0 ;
}