# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-01-20 11:07:11
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-01-20 11:24:05

import xlrd
import xlwt

file = open('Brand Finance.txt')
workbook = xlwt.Workbook(encoding = 'utf-8')

sheet = workbook.add_sheet('Brand Finance')

sheet.write(0,0,'rank');sheet.write(0,1,'name');sheet.write(0,2,'country');sheet.write(0,3,'value');

line = file.readline()
pos = -1
row = 1

while line:
    line = file.readline()
    pos += 1
    pos %= 7
    if pos == 0:
        sheet.write(row, 0, line)
    elif pos == 2:
        sheet.write(row, 1, line)
    elif pos == 4:
        sheet.write(row, 2, line)
    elif pos == 5:
        sheet.write(row, 3, line)
        row += 1

workbook.save('Brand Finance.xls')


'''
Rank 2016
Rank 2015
Brand name
Industry Group
Domicile
Brand value ($m) 2016
Brand value ($m) 2015
'''