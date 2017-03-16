# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2016-12-24 16:18:01
# @Last Modified by:   HaonanWu
# @Last Modified time: 2016-12-24 17:25:33

import urllib2
import json
from bs4 import BeautifulSoup

def check_substring(stra, strb):
    lista = list(stra)
    listb = list(strb)
    j = 0
    l = len(listb)
    for i in lista:
        if listb[j] == i:
            j += 1
            if j == l:
                return True
    return False

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
            if check_substring(tmp.strip(), string):
                contain.append(now)
        except:
            pass
        return 

def get_parent(now):
    for parent in now.parents: 
        if parent:
            try:
                if parent.attrs.has_key('class') and parent.attrs['class'] != []:
                    return (parent.name, parent.attrs)
            except:
                pass

def print_temp(fa):
    f1 = open('test.txt', 'a+')
    f1.write(str(fa))
    f1.write("\n\n***********************\n\n")
    f1.close()

def print_tree(now, num):
    try:
        for child in now.children: 
            print_tree(child, num)
    except AttributeError as e:
        try:
            tmp = "" + now.string
            tmp.strip()
            f1 = open('test' + str(num) + '.txt','a+')
            if tmp != '\n':
                f1.write(tmp+"\n")
            f1.close()
        except:
            pass
        return 

def get_all(now, num):
    li = soup_packetpage.findAll(now[0], now[1])
    for item in li:
        if now[1] == item.attrs:
            print_tree(item, num)


if __name__ == '__main__':
    import sys
    reload(sys)             
    sys.setdefaultencoding('utf-8')
    url = 'http://blog.csdn.net/u013007900?viewmode=contents'
    string = u'ACM'
    soup_packetpage = get_bs4(url)
    contain = []
    get_pos(soup_packetpage, contain, string)
    
    label_set = set()

    for pos in contain:
        fa = get_parent(pos)
        print_temp(fa)
        label_set.add(json.dumps(fa))  
        print "++++"    

    num = 0
    for fa_json in label_set:
        fa = json.loads(fa_json)
        print "****"
        print_temp(fa)
        get_all(fa, num)
        num += 1

    # [u'ul', {u'class': [u'panel_body', u'itemlist']}]
    # dic_test = {u'class': [u'panel_body', u'itemlist']}

    # li = soup_packetpage.findAll("ul", dic_test)
    # for item in li:
    #     if item.attrs == dic_test:
    #         print str(item)
    #         f1 = open('test4.txt','a+')
    #         f1.write(str(item))
    #         f1.write("\n**************************\n")
    #         f1.close()
            # try:
            #     for child in item.children:
            #         f1 = open('test50.txt','a+')
            #         f1.write(str(child))
            #         f1.write("\n**************************\n")
            #         f1.close()
            # except:
            #     pass




