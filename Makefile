CC=g++
conky_prices: conky_prices.o parse.o pugixml.o
	$(CC) -o conky_prices conky_prices.o parse.o pugixml.o -lcurl 


parse_prices: prices.o parse.o pugixml.o 
	$(CC) -o parse_prices prices.o parse.o pugixml.o -lcurl  

pugixml: 
	$(CC) -o pugixml pugixml.cpp

clean: 
	rm -rf parse_prices *.o