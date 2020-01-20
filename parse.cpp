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

void print_price(char* code, std::string price )
{ 
    std::cout.width(25 - price.length()) ; 
    std::cout << std::left << code << std::right << price << std::endl;
}

std::string get_price(CURL *curl, const char *url)
{   
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
    CURL *curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
 
    curl = curl_easy_init();
    char str[100];
    const char *param; 
    if(curl) {
      for (int i = 1 ; i < argc ; ++i){ 
          strcpy(str, "https://ca.finance.yahoo.com/quote/"); 
          strcat(str, argv[i]);
          print_price(argv[i], get_price(curl, str)); 
          curl = curl_easy_init();
          
      }
    } 
    curl_global_cleanup();
    return 0; 
 }