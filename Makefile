CC=g++

parse_prices: parse.cpp
	$(CC) parse.cpp -o parse_prices -lcurl  

clean: 
	rm -rf parse_prices 