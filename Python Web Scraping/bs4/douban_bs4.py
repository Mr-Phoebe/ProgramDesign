# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2016-12-24 16:18:01
# @Last Modified by:   HaonanWu
# @Last Modified time: 2016-12-24 17:03:16

import urllib2
import json
from bs4 import BeautifulSoup

def nowplaying_movies(url):
    user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36'
    headers = {'User-Agent':user_agent}
    request = urllib2.Request(url = url, headers = headers)
    response = urllib2.urlopen(request)
    soup_packetpage = BeautifulSoup(response, 'lxml')
    items = soup_packetpage.find_all("li", class_="list-item")
    movies = []
    for item in items:
        if item.attrs['data-category'] == 'nowplaying':
            movie = {}
            movie['title'] = item.attrs['data-title']
            movie['score'] = item.attrs['data-score']
            movie['director'] = item.attrs['data-director']
            movie['actors'] = item.attrs['data-actors']
            movies.append(movie)
            print('%(title)s|%(score)s|%(director)s|%(actors)s' % movie)

    return movies



if __name__ == '__main__':
    url = 'https://movie.douban.com/nowplaying/beijing/'
    movies = nowplaying_movies(url)

    print('%s' % json.dumps(movies, sort_keys=True, indent=4, separators=(',', ': ')))