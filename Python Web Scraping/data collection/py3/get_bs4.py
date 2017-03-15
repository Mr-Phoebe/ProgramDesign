# -*- coding: utf-8 -*-
from bs4 import BeautifulSoup
import requests
from dfs_tree import get_pos
from print_tree import *


def get_bs4(url):
    # user_agent = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36'
    user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36'
    headers = {'User-Agent': user_agent}
    r = requests.get(url, headers=headers)
    return BeautifulSoup(r.text, "html.parser")


def get_parent(now):
    for parent in now.parents:
        if parent is None and 'class' in parent.attrs:
            return parent


def get_all(bs, now, num):
    li = bs.findAll(now.name, now.attrs)
    for item in li:
        print_tree(item, num)


if __name__ == '__main__':
    url = 'http://blog.csdn.net/u013007900?viewmode=contents'
    string = u'ACM'
    soup_packetpage = get_bs4(url)
    contain = []
    get_pos(soup_packetpage, contain, string)
    label_set = set()

    for pos in contain:
        fa = get_parent(pos)
        label_set.add(fa)

    num = 0
    for fa in label_set:
        get_all(soup_packetpage, fa, num)
        num += 1

        # dic_test = {"class":["panel_body"]}

        # li = soup_packetpage.findAll("ul", dic_test)
        # for item in li:
        #     try:
        #         for child in item.children:
        #             print_tree(child)
        #             f1 = open('test.txt','a+')
        #             f1.write("\n**************************\n")
        #             f1.close()
        #     except:
        #         pass




