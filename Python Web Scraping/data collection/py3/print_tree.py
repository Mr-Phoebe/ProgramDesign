# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-03-15 10:22:40
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-03-15 11:06:10

import codecs

def print_temp(fa):
    f1 = codecs.open('ha.txt', 'a+', encoding='utf-8')
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
            f1 = codecs.open('test' + str(num) + '.txt', 'a+', encoding='utf-8')
            if tmp != '\n':
                f1.write(tmp + "\n")
            f1.close()
        except:
            pass
        return