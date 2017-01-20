# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-01-19 22:15:51
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-01-20 16:00:37

import urllib2
from bs4 import BeautifulSoup
import cPickle as pickle
import copy
import xlwt

def brand_info(url):
    user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36'
    headers = {'User-Agent':user_agent}
    request = urllib2.Request(url = url, headers = headers)
    response = urllib2.urlopen(request)
    soup_packetpage = BeautifulSoup(response, 'lxml')

    infos = soup_packetpage.find_all("div", class_="brand-info")

    with open('interbrand_info.pickle', 'wb') as f:
        pickle.dump(infos, f, -1)


def info_find(infos):
    brands = []
    brand = {}
    for info in infos:
        if 'brand-rank' in info.attrs['class']:
            brand['rank'] = info.attrs['title'][6::]
        if 'brand-name' in info.attrs['class']:
            brand['name'] = info.attrs['title'][11::]
        if 'brand-country'  in info.attrs['class']:
            brand['country'] = info.attrs['title'][9::]
        if 'brand-value' in info.attrs['class']:
            brand['value'] = info.attrs['title'][7:len(info.attrs['title'])-3:]
            temp = copy.deepcopy(brand)
            brands.append(temp)

    return brands

def write_excel(brands):
    book = xlwt.Workbook(encoding='utf-8', style_compression=0)
    sheet = book.add_sheet('interbrand', cell_overwrite_ok=False)
    sheet.write(0,0,'rank');sheet.write(0,1,'name');sheet.write(0,2,'country');sheet.write(0,3,'value');
    row = 1
    for brand in brands:
        sheet.write(row, 0, brand['rank'])
        sheet.write(row, 1, brand['name'])
        sheet.write(row, 2, brand['country'])
        sheet.write(row, 3, brand['value'])
        row += 1
    book.save("brands.xls")


if __name__ == '__main__':
    url = 'http://interbrand.com/best-brands/best-global-brands/2016/ranking/'
    # brand_info(url)
    
    f = open('interbrand_info.pickle', 'rb')
    infos = pickle.load(f)

    brands = info_find(infos)

    write_excel(brands)
