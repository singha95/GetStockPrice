#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <regex>
#include <iomanip>
#include <algorithm>
#include "parse.h"


void print_usage()
{ 
  std::cout << "A program to get stock prices from Yahoo Fianance:" 
            << std::endl 
            << "-p \t\t Print only the prices of the given stocks"
            << std::endl
            << "Example Usage: price -p googl"  
            <<std::endl ; 
}

void print_price(char* code, float price )
{ 
    std::cout << std::setprecision(7); //
    std::cout.width(25 - 7) ; 
    std::cout << std::left << code << std::right << price << std::endl;
}

int check_params(int argc, char** argv){ 
    for (int i = 0; i < argc; ++i )
    { 
        bool isEqual = strcmp(argv[i], "-p") == 0; 
        if (isEqual)
        { 
            return 1; 
        }
    }
    return 0; 
}


int main(int argc, char** argv) 
{ 

    if (argc < 2 ){ 
      print_usage();
      return 0; 
    }

    int isPrices = check_params(argc, argv); 
    CURL *curl;
    curl_global_init(0);
 
    char str[100];

    for (int i = 1; i < argc ; ++i){ 
        strcpy(str, "https://ca.finance.yahoo.com/quote/"); 
        strcat(str, argv[i]);
        std::string html = filter_stock_html(get_html(curl, str));
        std::cout << html << std::endl;
        if (!isPrices){
          print_price(argv[i], get_price(html));
        }
        else if (strcmp(argv[i], "-p")) 
        {
          std::cout << get_price(html) << std::endl; 
        }
        
    }

    //curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0; 
 }