# -*- coding: utf-8 -*-

class FpNode:

    def __init__(self, idName = None, count = 1):
        '''
        用于生成结点
        :param idName:  结点名称
        :param count:  结点数量
        '''
        self.idName = idName
        self.count = count
        self.children = []
        self.parent = None
        self.next = None

    def addChild(self, child):
        '''
        添加一个孩子
        :param child: 孩子结点
        '''
        self.children.append(child)

    def addCount(self, count = 1):
        '''
        结点数量增加
        :param count: 数量
        '''
        self.count += count

    def setNextNode(self, next):
        '''
        设置下一个结点
        :param next: 下一个结点
        '''
        self.next = next

    def setParentNode(self, parent):
        '''
        设置父亲结点
        :param parent: 父亲结点
        '''
        self.parent = parent

    def getChild(self, index):
        '''
        取得指定孩子
        :param index: 孩子结点下标
        :return 孩子结点 FpNode
        '''
        return self.children[index]

    def hasChild(self, idName):
        '''
        查找是否包含id号为idName的孩子
        :param idName: 孩子结点名称
        :return: 找到返回下标号，没找到返回-1
        '''
        row = 0
        for child in self.children:
            if child.idName == idName:
                return row
            else:
                row += 1
        return -1

    def __str__(self):
        return "id:" + self.idName + " count:" + self.count + " 孩子个数:" + len(self.children)


class Holder:
    '''
    生成条件树用到的包装器
    '''
    def __init__(self, root, header):
        self.root = root
        self.header = header


class Support:
    def __init__(self):
        self.ABSSupport = -1
        self.SUPPORT = 0.6

    def setabs(self, ABSSupport):
        self.ABSSupport = ABSSupport

    def getabs(self):
        return self.ABSSupport