# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2016-12-22 16:16:08
# @Last Modified by:   HaonanWu
# @Last Modified time: 2016-12-22 21:34:02

import urllib
import urllib2
import re
import os
from bs4 import BeautifulSoup

if __name__ == '__main__':
	url = 'http://www.qiushibaike.com/textnew/page/1/?s=4941357'
	user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36'
	headers = {'User-Agent':user_agent}
	request = urllib2.Request(url = url, headers = headers)
	response = urllib2.urlopen(request)
	# print response.read()
	soup_packetpage = BeautifulSoup(response, 'lxml')
	items = soup_packetpage.find_all("div", class_="content")

	for item in items:
		try:
			content = item.span.string
		except AttributeError as e:
			print e
			exit()

		if content:
			print content + "\n"
