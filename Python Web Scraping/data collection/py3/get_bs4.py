# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-03-15 10:23:15
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-03-18 10:31:24

from bs4 import BeautifulSoup
import requests
from dfs_tree import *
from print_tree import *
from get_unique import *

html = '''
<ul class="panel_body">
                 <li>
                    <a href="/u013007900/article/category/2234277" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">ACM</a><span>(21)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2234279" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">位运算</a><span>(7)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2275095" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">数学 &amp; 博弈论</a><span>(57)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2275251" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">动态规划 &amp; 贪心</a><span>(65)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2289081" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">数据结构</a><span>(65)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2309373" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">图论</a><span>(30)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2406467" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">hash</a><span>(6)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2406469" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">模拟</a><span>(45)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2421229" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">搜索</a><span>(21)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2454717" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">前缀 &amp; 后缀</a><span>(28)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2459915" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">匹配</a><span>(5)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2487029" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">计算几何</a><span>(5)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2502783" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">网络流</a><span>(12)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2893153" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">二分 &amp; 三分</a><span>(11)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2895695" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">分治</a><span>(7)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/3277211" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">树分治</a><span>(4)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/5756365" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">树链剖分</a><span>(4)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/5429461" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">FFT</a><span>(8)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2770641" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">Android开发</a><span>(1)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/2858747" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">QT开发</a><span>(30)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/6018681" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">Java开发</a><span>(13)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/6633206" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">Python开发</a><span>(18)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/3278573" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">数学建模</a><span>(31)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/5421311" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">计算机学科学习笔记</a><span>(42)</span>
                </li>
                 <li>
                    <a href="/u013007900/article/category/6582738" onclick="_gaq.push(['_trackEvent','function', 'onclick', 'blog_articles_wenzhangfenlei']); ">机器学习 &amp; 深度学习</a><span>(25)</span>
                </li>
</ul>
'''

def get_bs4(url):
    # user_agent = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36'
    user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36'
    headers = {'User-Agent': user_agent}
    r = requests.get(url, headers=headers)
    return BeautifulSoup(r.text, "html.parser")

def get_all_fit(bs, now, num):
    li = filter(lambda x:x.attrs == now[1], bs.findAll(now[0], now[1]))
    for item in li:
        print_tree(item, num, 0)

if __name__ == '__main__':
    url = 'http://blog.csdn.net/u013007900?viewmode=contents'
    string = u'ACM'
    contain = []

    soup_packetpage = get_bs4(url)
    get_pos(soup_packetpage, contain, string)

    fa_list = keep_unique(map(get_parent, contain))

    num = 0
    for fa in fa_list:
        num += 1
        get_all_fit(soup_packetpage, fa, num)


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




