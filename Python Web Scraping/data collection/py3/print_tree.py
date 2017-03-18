# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-03-15 10:22:40
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-03-15 11:06:10

import codecs
import copy

def print_temp(fa, flag):
    f1 = codecs.open('testha.txt', 'a+', encoding='utf-8')
    f1.write(str(fa))
    s = flag * 10
    f1.write(s+"\n")
    f1.close()

def print_brother(ori, num, dep):
    cur = ori
    f1 = codecs.open('test' + str(num) + '_' + str(dep) + '.txt', 'a+', encoding='utf-8')
    while cur:
        try:
            tmp = "" + cur.string
            cur = cur.next_sibling
        except:
            break
        tmp.strip()
        if tmp != '\n':
            f1.write(tmp + "\n" + "dep:  " + str(dep) + "\n")
            f1.write("\n++++++++++++++++++++++++\n")

    f1.write("\n**************************************\n")
    f1.close()

def print_children(ori, num, dep):
    cur = ori
    f1 = codecs.open('test' + str(num) + '_' + str(dep) + '.txt', 'a+', encoding='utf-8')
    try:
        for child in cur.children:
            try:
                tmp = "" + child.string
            except:
                break
            tmp.strip()
            if tmp != '\n':
                f1.write(tmp + "\n" + "dep:  " + str(dep) + "\n")
    except:
        pass
    f1.close()
    pass

def print_tree(now, num, dep):
    for child in now.children:
        try:
            child.children             # 有儿子，则继续
            print_tree(child, num, dep + 1)
        except AttributeError as e:
            print_brother(child, num, dep)



            # tmp = "" + now.string
            # tmp.strip()
            # f1 = codecs.open('test' + str(num) + '.txt', 'a+', encoding='utf-8')
            # if tmp != '\n':
            #     f1.write(tmp + "\n" + "dep:  " + str(dep) + "\n")
            # f1.close()