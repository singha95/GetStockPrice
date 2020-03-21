CC=g++
conky_prices: conky_prices.o parse.o pugixml.o
	$(CC) -o conky_prices_temp conky_prices.o parse.o pugixml.o -lcurl 


parse_prices: price.o pugixml.o
	$(CC) -o parse_prices_temp price.o pugixml.o -lcurl  

pugixml: 
	$(CC) -o pugixml pugixml.cpp

clean: 
	rm -rf parse_prices *.o