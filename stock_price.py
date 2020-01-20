#!/bin/python3 

import fecon236 as fe
import sys
import os

for arg in sys.argv[1:]:    
    sys.stdout = open(os.devnull, "w")
    stock = fe.get("s4" + arg)
    sys.stdout = sys.__stdout__
    print(arg.upper())
    print(fe.tail(stock))