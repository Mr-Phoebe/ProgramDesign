#!/usr/bin/env python
#Reduce function for computing matrix multiply A*B

#Input arguments:
#variable n should be set to the inner dimension of the matrix product (i.e., the number of columns of A/rows of B)

import sys
import string
import numpy

#number of columns of A/rows of B
n = int(sys.argv[1]) 

#Create data structures to hold the current row/column values (if needed; your code goes here)

A = {}
B = {}

currentkey = None

# input comes from STDIN (stream data that goes to the program)
for line in sys.stdin:

    #Remove leading and trailing whitespace
    line = line.strip()

    #Get key/value 
    key, value = line.split('\t',1)

    #Parse key/value input (your code goes here)

    args = value.split()
    mat = args[0]
    pos = int(args[1])
    number = float(args[2])

    #If we are still on the same key...
    if key == currentkey:

        #Process key/value pair (your code goes here)
        if mat == 'A':
            A[pos] = number
        else:
            B[pos] = number


    #Otherwise, if this is a new key...
    else:
        #If this is a new key and not the first key we've seen
        if currentkey:

            #compute/output result to STDOUT (your code goes here)
            ans = 0.0
            for i in range(n):
                ans += A[i] * B[i]
            print("({}, {}), {}".format(row, col, ans))

    
        currentkey = key
        
        #Process input for new key (your code goes here)

        if mat == 'A':
            A[pos] = number
        else:
            B[pos] = number
        args = key.split()
        row = int(args[0])
        col = int(args[1])


#Compute/output result for the last key (your code goes here)

if currentkey:
    #compute/output result to STDOUT (your code goes here)
    ans = 0.0
    for i in range(n):
        ans += A[i] * B[i]
    print("({}, {}), {}".format(row, col, ans))


