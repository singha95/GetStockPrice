#include <curl/curl.h>
#include "pugixml.hpp"
#include <regex>
#include <iostream>
#include <string.h>



size_t write_to_string(void *ptr, size_t size, size_t nmemb, std::string stream)
{
  size_t realsize = size * nmemb;
  std::string temp(static_cast<const char*>(ptr), realsize);
  stream.append(temp);
  return realsize;
}

std::string get_html(CURL *curl, const char *url){ 
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
    return response; 
}

std::string filter_stock_html(std::string html){ 
    pugi::xml_document doc;
    //pugi::xml_parse_result result = doc.load_string(html);
    std::regex rgx("<div class=\"D\\(ib\\) Va\\(m\\) Maw\\(65%\\) Ov\\(h\\)\" data-reactid=\"32\">(.*?)</div>");
    std::smatch matches;
    bool b = std::regex_search(html, matches, rgx);
    return matches[1]; 
}

float get_percent(std::string html){ 
  std::regex rgx("<span class=\"Trsdu\\(0.3s\\) Fw\\(500\\) Pstart\\(10px\\) Fz\\(24px\\) C\\(\\$data.*?\\)\" data-reactid=\"35\">.*?\\((.*?)\\)</span>"); 
  std::smatch matches; 
  bool b = std::regex_search(html, matches, rgx);
  if (!b || matches[1] == "")
  { 
    return 0.0f; 
  }
  std::string percent = matches[1];
  return std::stod(percent); 
}

std::string get_stock_color(std::string html){ 

  std::string s = "<span class=\"Trsdu(0.3s) Fw(b) Fz(36px) Mb(-4px) D(ib)\">1,480.39</span>";
  std::regex rgx("Trsdu\\(0.3s\\) Fw\\(500\\) Pstart\\(10px\\) Fz\\(24px\\) C\\(\\$data(.*?)\\)");
  std::smatch matches;
  bool b = std::regex_search(html, matches, rgx);
  if (!b || matches[1] == "")
  { 
    return ""; 
  }
  std::string temp(matches[1]); 
  std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
  return temp;
  //<span class="Trsdu(0.3s) Fw(500) Pstart(10px) Fz(24px) C($dataGreen)" data-reactid="35">+8.57 (+0.57%)</span>
}



float get_price(std::string html)
{     
    std::regex rgx("<span class=\"Trsdu\\(0.3s\\) Fw\\(b\\) Fz\\(36px\\) Mb\\(-4px\\) D\\(ib\\)\" data-reactid=\"34\">([\\s\\S]*?)</span>");
    std::smatch matches;
    bool b = std::regex_search(html, matches, rgx);
    if (!b || matches[1] == "")
    { 
      return 0; 
    }
    std::string price = matches[1]; 
    price.erase(std::remove(price.begin(), price.end(), ','), price.end());
    return std::stod(price); 
}