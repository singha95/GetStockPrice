#include <curl/curl.h>
#include <regex>

size_t write_to_string(void *ptr, size_t size, size_t nmemb, std::string stream)
{
  size_t realsize = size * nmemb;
  std::string temp(static_cast<const char*>(ptr), realsize);
  stream.append(temp);
  return realsize;
}

float get_price(CURL *curl, const char *url)
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
    if (!b || matches[1] == "")
    { 
      return 0; 
    }
    std::string price = matches[1]; 
    price.erase(std::remove(price.begin(), price.end(), ','), price.end());
    return std::stod(price); 
}