#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <regex>

size_t write_to_string(void *ptr, size_t size, size_t nmemb, std::string stream)
{
  size_t realsize = size * nmemb;
  std::string temp(static_cast<const char*>(ptr), realsize);
  stream.append(temp);
  return realsize;
}

void print_usage()
{ 
  std::cout << "A program to get stock prices from Yahoo Fianance:" 
            << std::endl 
            << "-p \t\t Print only the prices of the given stocks"
            << std::endl
            << "Example Usage: price -p googl"  
            <<std::endl ; 
}

void print_price(char* code, std::string price )
{ 
    std::cout.width(25 - price.length()) ; 
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

std::string get_price(CURL *curl, const char *url)
{   
    curl = curl_easy_init();
    CURLcode res;
    std::string response; 
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* Store the response data in the variable response */ 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK) { 
        std::cout << "curl_easy_perform() failed: " 
                  << curl_easy_strerror(res) 
                  << std::endl;
    }
    /* always cleanup */ 
    curl_easy_cleanup(curl);

    std::string s = "<span class=\"Trsdu(0.3s) Fw(b) Fz(36px) Mb(-4px) D(ib)\">1,480.39</span>";
    std::regex rgx("<span class=\"Trsdu\\(0.3s\\) Fw\\(b\\) Fz\\(36px\\) Mb\\(-4px\\) D\\(ib\\)\" data-reactid=\"34\">([\\s\\S]*?)</span>");
    std::smatch matches;
    bool b = std::regex_search(response, matches, rgx);
    if (!b)
    { 
      return ""; 
    }
    return matches[1]; 
}

int main(int argc, char** argv) 
{ 

    if (argc < 2 ){ 
      print_usage(); 
      return 0 ;
    }

    int isPrices = check_params(argc, argv); 
    CURL *curl;
    curl_global_init(0);
 
    
    char str[100];
    const char *param; 
    if(curl) {
      for (int i = 1; i < argc ; ++i){ 
          strcpy(str, "https://ca.finance.yahoo.com/quote/"); 
          strcat(str, argv[i]);
          if (!isPrices){
            print_price(argv[i], get_price(curl, str));
          }
          else if (strcmp(argv[i], "-p")) 
          {
            std::cout << get_price(curl, str) << std::endl; 
          }
          
      }
      
    } 
    //curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0; 
 }