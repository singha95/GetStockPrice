#!/bin/python3 

import yfinance as yf  
import matplotlib.pyplot as plt
import datetime
import sys
import os 


if not sys.argv[1:]: 
    print("Add stock names to generate graphs for")
    exit(1)

stocks = [ x.upper() for x in sys.argv[1:] ]
savePath = "./stocks/"
if not os.path.exists(savePath):
    os.makedirs(savePath)
    os.makedirs(savePath + 'month')
    os.makedirs(savePath + 'week')
curDate = datetime.date.today().strftime('%Y-%m-%d')
startDateMonth = (datetime.date.today() - datetime.timedelta(365/12)).strftime('%Y-%m-%d')
startDateWeek = (datetime.date.today() - datetime.timedelta(365/50)).strftime('%Y-%m-%d')

#Monthly Charts for stocks 
for stock in stocks: 
    # Get the data for the stock Apple by specifying the stock ticker, start date, and end date
    data = yf.download(stock, startDateMonth,curDate)
    
    # Plot the close prices
    data.Close.plot()
    plt.title(stock + " (Month)", {}, 'center')
    plt.savefig(savePath + "month/" + stock + ".png")
    plt.clf()

#Weekily Charts for stocks 
for stock in stocks: 
    # Get the data for the stock Apple by specifying the stock ticker, start date, and end date
    data = yf.download(stock, startDateWeek,curDate)
    
    # Plot the close prices
    data.Close.plot()
    plt.title(stock + " (Week)", {}, 'center')
    plt.savefig(savePath + "week/" + stock + ".png")
    plt.clf()