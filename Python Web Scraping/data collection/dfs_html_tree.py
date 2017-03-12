# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2016-12-24 16:18:01
# @Last Modified by:   HaonanWu
# @Last Modified time: 2016-12-24 17:25:33

import urllib2
import json
import copy
from bs4 import BeautifulSoup

def get_bs4(url):
    user_agent = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36'
    headers = {'User-Agent':user_agent}
    request = urllib2.Request(url = url, headers = headers)
    response = urllib2.urlopen(request)
    # print response.read()
    # response = '''
    #     <div class="article_title">
    #     <span class="ico ico_type_Original"></span>
    #     <h1>
    #     <span class="link_title"><a href="/u013007900/article/details/52357067">
    #             Leetcode 391. Perfect Rectangle            
    #             </a></span>
    #     </h1>
    #     </div>
    #'''
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

def get_class(now):
    for parent in now.parents: 
        if parent is None: 
            print parent
        else: 
            print parent.name
            if parent.attrs.has_key('class') and parent.attrs['class'] != []:
                print " ",parent.attrs['class']


if __name__ == '__main__':
    url = 'http://blog.csdn.net/u013007900?viewmode=contents'
    string = u'Github计算contributions'
    soup_packetpage = get_bs4(url)
    contain = []
    get_pos(soup_packetpage, contain, string)
    
    for pos in contain:
        get_class(pos)
        print "********************"

    li = soup_packetpage.findAll("span", class_=u'link_title')
    for item in li:
        try:
            print item.string
        except:
            pass




