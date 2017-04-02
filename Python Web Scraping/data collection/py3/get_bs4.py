# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-03-15 10:23:15
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-03-25 12:09:59

from bs4 import BeautifulSoup
import requests
from dfs_tree import *
from print_tree import *
from Node import *
from get_unique import *

def get_bs4(url):
    # user_agent = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36'
    user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36'
    headers = {'User-Agent': user_agent}
    r = requests.get(url, headers=headers)
    return BeautifulSoup(r.text, "html.parser")

def test(soup_packetpage):
    dic_test = {"class":["reactable-data"]}

    li = soup_packetpage.findAll("tbody", dic_test)
    for item in li:
        if 'class' in item.attrs \
            and item.attrs['class'] == ["reactable-data"]:
            print(item)

if __name__ == '__main__':
    url = 'http://interbrand.com/best-brands/best-global-brands/2016/ranking/'
    #url = 'http://blog.csdn.net/u013007900?viewmode=contents'
    string = '178,119 $m'.strip()
    #string = 'ACM'.strip()
    anchor = []

    soup_packetpage = get_bs4(url)
    [script.extract() for script in soup_packetpage.findAll('script')]
    [style.extract() for style in soup_packetpage.findAll('style')]

    get_anchor_pos(soup_packetpage, anchor, string)

    print(anchor)
    if anchor == []:
        exit(1)

    method = input()

    if method == 1:
        fa_list = []
        for node in anchor:
            fa_list.append(node.get_father())
        anchor = keep_unique(fa_list, anchor)

        num = 0
        for fa in fa_list:
            num += 1
            get_all_fit_path(soup_packetpage, fa, num, method)
    else:
        num = 0
        for node in anchor:
            num += 1
            get_all_fit_path(soup_packetpage, node, num, method)








