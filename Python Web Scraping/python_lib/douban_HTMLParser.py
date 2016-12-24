# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2016-12-24 15:57:54
# @Last Modified by:   HaonanWu
# @Last Modified time: 2016-12-24 17:03:27
from HTMLParser import HTMLParser
import urllib2
import json

class MovieParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.movies = []

    def handle_starttag(self, tag, attrs):
        def _attr(attrlist, attrname):
            for attr in attrlist:
                if attr[0] == attrname:
                    return attr[1]
            return None
        if tag == 'li' and _attr(attrs, 'data-title') and _attr(attrs, 'data-category') == 'nowplaying':
            movie = {}
            movie['title'] = _attr(attrs, 'data-title')
            movie['score'] = _attr(attrs, 'data-score')
            movie['director'] = _attr(attrs, 'data-director')
            movie['actors'] = _attr(attrs, 'data-actors')
            self.movies.append(movie)
            print('%(title)s|%(score)s|%(director)s|%(actors)s' % movie)


def nowplaying_movies(url):
    headers = {'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36'}    
    req = urllib2.Request(url, headers=headers)
    s = urllib2.urlopen(req)
    parser = MovieParser()
    parser.feed(s.read())
    s.close()
    return parser.movies


if __name__ == '__main__':
    url = 'https://movie.douban.com/nowplaying/beijing/'
    movies = nowplaying_movies(url)

    print('%s' % json.dumps(movies, sort_keys=True, indent=4, separators=(',', ': ')))