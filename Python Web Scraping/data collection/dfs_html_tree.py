# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2016-12-24 16:18:01
# @Last Modified by:   HaonanWu
# @Last Modified time: 2016-12-24 17:25:33

import urllib2
import json
from bs4 import BeautifulSoup

def get_bs4(url):
    user_agent = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36'
    headers = {'User-Agent':user_agent}
    request = urllib2.Request(url = url, headers = headers)
    response = urllib2.urlopen(request)
    return BeautifulSoup(response,"html.parser")

def get_pos(now, contain, string):
    try:
        for child in now.children: 
            get_pos(child, contain, string)
    except AttributeError as e:
        try:
            tmp = "" + now.string
            if tmp.strip() == string:
                contain.append(now)
        except:
            pass
        return 

def get_parent(now):
    for parent in now.parents: 
        if parent:
            try:
                if parent.attrs.has_key('class') and parent.attrs['class'] != []:
                    return parent
            except:
                pass

def print_tree(now):
    try:
        for child in now.children: 
            print_tree(child)
    except AttributeError as e:
        try:
            tmp = "" + now.string
            tmp.strip()
            f1 = open('test.txt','a+')
            if tmp != '\n':
                f1.write(tmp+"\n")
            f1.close()
        except:
            pass
        return 

def get_all(now):
    li = soup_packetpage.findAll(now.name, now.attrs)
    for item in li:
        try:
            print_tree(item)
        except:
            pass



if __name__ == '__main__':
    import sys
    reload(sys)             
    sys.setdefaultencoding('utf-8')
    url = 'http://blog.csdn.net/u013007900?viewmode=contents'
    string = u'ACM'
    soup_packetpage = get_bs4(url)
    contain = []
    get_pos(soup_packetpage, contain, string)
    

    for pos in contain:
        fa = get_parent(pos)
        get_all(fa)
        print "********************"

    # dic_test = {"class":["list_item", "list_view"]}

    # li = soup_packetpage.findAll("div", dic_test)
    # for item in li:
    #     try:
    #         print item.div.h1.span.string
    #     except:
    #         pass




