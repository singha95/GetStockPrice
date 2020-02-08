CC=g++
conky_prices: conky_prices.cpp parse_prices parse.hpp
	$(CC) conky_prices.cpp -o conky_prices -lcurl 


parse_prices: parse.cpp parse.hpp
	$(CC) parse.cpp -o parse_prices -lcurl  

clean: 
	rm -rf parse_prices 