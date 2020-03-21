size_t write_to_string(void *ptr, size_t size, size_t nmemb, std::string stream); 

std::string get_html(CURL *curl, const char *url); 

std::string filter_stock_html(std::string html) ;

std::string get_stock_color(std::string html); 

float get_price(std::string html); 