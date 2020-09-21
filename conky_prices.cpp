#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <curl/curl.h>
#include "parse.h"

int main(int argc, char** argv)
{
    CURL *curl;
    curl_global_init(0);    
    // while (stocks >> x) {
    for (int i = 1; i < argc ; ++i){ 
        std::string x(argv[i]); 
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
    return 0 ;
}