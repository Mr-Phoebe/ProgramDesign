#!/usr/bin/env python

# example using hadoop-streaming, from 
# http://www.michael-noll.com/tutorials/writing-an-hadoop-mapreduce-program-in-python/

import sys
import string
# the system python does not have numpy, but the python/gnu/3.4.4 does
# (we don't actually need it, but attempting to import it will trigger 
# an error if the mapper can't see the version of python we want to use)
import numpy

# input comes from STDIN (standard input)
for line in sys.stdin:
    # remove leading and trailing whitespace
    line = line.strip()
    # split the line into words
    words = line.split()
    # increase counters
    for word in words:
        # write the results to STDOUT (standard output);
        # what we output here will be the input for the
        # Reduce step, i.e. the input for reducer.py
        #
        # tab-delimited; the trivial word count is 1
        w=word.strip(string.punctuation)
        if w:
            print('{0:s}\t{1:d}'.format(w.lower(), 1))


