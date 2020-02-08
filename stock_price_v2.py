#!/bin/python3 

import yfinance as yf  
from alpha_vantage.timeseries import TimeSeries
import datetime

stocks = ['GOOGL', 'AAPL', 'TD', 'AMZN']
savePath = "/home/angad/Pictures/stocks/"

# Your key here
key = 'MCZCTGXDDSEVULB2'
ts = TimeSeries(key)
aapl, meta = ts.get_daily(symbol='AAPL')
print(aapl['2020-02-07'])