# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2016-12-22 20:37:38
# @Last Modified by:   HaonanWu
# @Last Modified time: 2016-12-22 21:27:30
import urllib2
import urllib
import re  
  
from bs4 import BeautifulSoup  
  

url = "https://www.packtpub.com/all"
try:
    html = urllib2.urlopen(url)  
except urllib2.HTTPError as e:
    print e
    exit()

soup_packtpage = BeautifulSoup(html, 'lxml')  
all_book_title = soup_packtpage.find_all("div", class_="book-block-title")  
  
price_regexp = re.compile(u"\s+\$\s\d+\.\d+")  
  
for book_title in all_book_title:  
    try:
        print "Book's name is " + book_title.string.strip()
    except AttributeError as e:
        print e
        exit()
    book_price = book_title.find_next(text=price_regexp)  
    try:
        print "Book's price is "+ book_price.strip()
    except AttributeError as e:
        print e
        exit()
    print ""
      
  