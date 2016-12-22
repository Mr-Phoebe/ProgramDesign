# -*- coding: UTF-8 -*-
import urllib2
import urllib
if __name__ == '__main__':
	# 设置URL、设置头部、设置数据
	url = 'https://passport.csdn.net/account/login'
	headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36'}
	values = {'email' : 'whn', 'pwd' : 'whn'}
	data = urllib.urlencode(values)
	# 发送请求、接收相应
	request = urllib2.Request(url = url, data = data, headers = headers)
	response = urllib2.urlopen(request)
	print response.read()

