# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-03-15 10:22:04
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-03-25 12:09:49

from print_tree import *
from Node import *

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

def LCA(nodex, nodey):
    xdep = nodex.get_dep()
    ydep = nodey.get_dep()
    if xdep > ydep:
        nodex, nodey = nodey, nodex
    dist = ydep - xdep
    xdomNode = nodex.bs4node
    ydomNode = nodey.bs4node
    while dist != 0:
        ydomNode = ydomNode.parent
        dist -= 1
    while xdomNode != ydomNode:
        xdomNode = xdomNode.parent
        ydomNode = ydomNode.parent
    return Node(xdomNode)



def get_anchor_pos(now, contain, string):
    try:
        for child in now.children:
            get_anchor_pos(child, contain, string)
    except Exception as e:
        try:
            tmp = "" + now.string
            if check_substring(tmp.strip(), string):
                contain.append(Node(now))
        except:
            pass
        return

def get_pos_path(now, contain, path, node, lastclass):
    if 'class' in now.attrs:
        lastclass = now.attrs['class']
    if path == node.path and lastclass == node.get_father()[1]:
        contain.append(Node(now))
        return
    try:
        for child in now.children:
            if child.name != None:
                path.append(child.name)
                get_pos_path(child, contain, path, node, lastclass)
                path.pop()
    except:
        pass
    return

def get_all_fit_css(bs, now, num):
    li = filter(lambda x:x.attrs['class'] == now[1], bs.findAll(now[0], {'class':now[1]}))
    for item in li:
        print_tree(item, num, 0)

def get_all_fit_path(bs, node, num, method):
    li = []
    get_pos_path(bs, li, [], node, [])
    cnt = 0
    if method == 1:
        for item in li:
            print_tree(item.bs4node, num, 0)
    else:
        for item in li:
            if cnt > 4:
                break
            lcanode = LCA(item, node)
            print_temp(lcanode.bs4node, cnt)
            cnt += 1