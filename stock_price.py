#!/bin/python3 

import yfinance as yf  
import matplotlib.pyplot as plt
import datetime

stocks = ['GOOGL', 'AAPL', 'TD', 'AMZN']
savePath = "/home/angad/Pictures/stocks/"
for stock in stocks: 
    # Get the data for the stock Apple by specifying the stock ticker, start date, and end date
    curDate = datetime.date.today().strftime('%Y-%m-%d')
    startDate = (datetime.date.today() - datetime.timedelta(365/12)).strftime('%Y-%m-%d')
    data = yf.download(stock, startDate,curDate)
    
    # Plot the close prices
    data.Close.plot()
    plt.title(stock, {}, 'center')
    plt.savefig(savePath + stock + ".png")
    plt.clf()