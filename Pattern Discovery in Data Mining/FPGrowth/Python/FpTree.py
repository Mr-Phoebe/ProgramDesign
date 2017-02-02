# -*- coding: utf-8 -*-

from reader import readAsMatrix
from FpNode import FpNode
from FpNode import Holder

ABSSupport = -1
SUPPORT = 0.6

def getHeader(matrix, frequentMap):
    '''
    生成表头
    :param matrix: 整个记录
    :param frequentMap:
    :param ABSSupport:
    :return: header 表头的键为id号，并且按照出现次数的降序排序
    '''

    countMap = {}
    global ABSSupport

    for line in matrix:
        for idName in line:
            countMap[idName] = 1 if idName not in countMap else countMap[idName] + 1

    for item in countMap.items():
        if item[1] >= ABSSupport:
            frequentMap[item[0]] = item[1]

    mapList = sorted(frequentMap.iteritems(), key = lambda item:item[1], reverse=True)
    frequentMap.clear()
    header = {}

    for item in mapList:
        frequentMap[item[0]] = item[1]
        header[item[0]] = None

    return header

def getFpTree(matrix, header, frequentMap):
    '''
    构造FP树,同时利用方法的副作用更新表头
    :param matrix:
    :param header:
    :param frequentMap:
    :return: 返回数的根结点
    '''
    root = FpNode(None, -1)
    for line in matrix:
        orderline = getOrderLine(line, frequentMap)
        parent = root
        for idName in orderline:
            index = parent.hasChild(idName)
            if index != -1:
                parent = parent.getChild(index)
                parent.addCount()
            else:
                node = FpNode(idName)
                parent.addChild(node)
                node.setParentNode(parent)
                nextNode = header.get(idName)
                if nextNode == None:
                    header[idName] = node
                else:
                    while nextNode.next != None:
                        nextNode = nextNode.next
                    nextNode.next = node
                parent = node

    return root

def getOrderLine(line, frequentMap):
    '''
    将line数组里id按照frequentMap的值得降序排序
    :param line:
    :param frequentMap:
    :return:
    '''
    countMap = {}
    for idName in line:
        if frequentMap.has_key(idName):
            countMap[idName] = frequentMap[idName]

    mapList = sorted(countMap.iteritems(), key=lambda item: item[1], reverse=True)
    orderline = []
    for item in mapList:
        orderline.append(item[0])
    return orderline

def fpGrowth(root, header, idName):
    '''
    用fp增长递归求平凡项
    :param root:
    :param header:
    :param idName:
    :return:
    '''
    conditionFres = {}
    keyArray = header.keys()
    firstIdName = keyArray[len(keyArray) - 1]

    if isSinglePath(header, firstIdName): #只有一条路径时，求路径上的所有组合即可得到调节频繁集
        if idName == None:
            return conditionFres
        leaf = header[firstIdName]
        paths = [] # 自顶向上保存路径结点
        paths.append(leaf)
        node = leaf
        while node.parent.idName != None:
            paths.append(node.parent)
            node = node.parent
        conditionFres = getCombinationPattern(paths, idName)
        tempNode = FpNode(idName, -1L)
        conditionFres = addLeafToFrequent(tempNode, conditionFres)
    else:
        for i in range(len(keyArray)-1, -1, -1):
            key = keyArray[i]
            leafs = []
            link = header[key]
            while link != None:
                leafs.append(link)
                link = link.next
            paths = {}
            leafCount = 0
            noParentNode = None
            for leaf in leafs:
                path = []
                node = leaf
                while node.parent.idName != None:
                    path.append(node.parent.idName)
                    node = node.parent
                leafCount += leaf.count
                if len(path) > 0:
                    paths[frozenset(path)] = leaf.count
                else:
                    noParentNode = leaf
            if noParentNode != None:
                oneItem = []
                oneItem.append(noParentNode)
                if idName != None:
                    oneItem.append(FpNode(idName, -2))
                conditionFres[frozenset(oneItem)] = leafCount
            holder = getConditionFpTree(paths)
            if len(holder.header) != 0:
                preFres = fpGrowth(holder.root, holder.header, key)
                if idName != None:
                    tempNode = FpNode(idName, leafCount)
                    preFres = addLeafToFrequent(tempNode, preFres)
                for item in preFres.items():
                    conditionFres[item[0]] = item[1]

    return conditionFres


def isSinglePath(header, tableLink):
    '''
    判断一颗fptree是否为单一路径
    :param header:
    :param tableLink:
    :return:
    '''
    if len(header) == 1 and header[tableLink].next == None:
        return True
    return False

def getConditionFpTree(paths):
    '''
    生成条件树
    :param paths:
    :return:
    '''
    matrix = []
    for entry in paths.items():
        for i in range(0, entry[1]):
            matrix.append(entry[0])

    frequentMap = {}
    cHeader = getHeader(matrix, frequentMap)
    cRoot = getFpTree(matrix, cHeader, frequentMap)
    return Holder(cRoot, cHeader)


def getCombinationPattern(paths, idName):
    '''
    求单一路径上的所有组合加上idName构成的频繁项
    :param paths:
    :param idName:
    :return:
    '''
    conditionFres = {}
    size = len(paths)
    for mask in range(1, (1<<size)):
        fplist = []
        for i in range(0, len(paths)):
            if (mask & (1<<i)) > 0:
                fplist.append(paths[i])
        minValue = -1
        for node in fplist:
            minValue = node.count if minValue == -1 else min(node.count, minValue)
        conditionFres[frozenset(fplist)] = minValue

    return conditionFres


def addLeafToFrequent(leaf, conditionFres):
    '''
    将叶子结点添加到频繁集中
    :param leaf:
    :param conditionFres:
    :return:
    '''
    if len(conditionFres) == 0:
        fplist = []
        fplist.append(leaf)
        conditionFres[fplist] = leaf.count
    else:
        keys = conditionFres.keys()
        for fpset in keys:
            count = conditionFres[fpset]
            conditionFres.pop(fpset)
            fplist = list(fpset)
            fplist.append(leaf)
            conditionFres[frozenset(fplist)] = count

    return conditionFres


if __name__ == '__main__':

    matrix = readAsMatrix("d.txt", "\t", "utf-8")
    global ABSSupport
    ABSSupport = long(SUPPORT * len(matrix))

    print "绝对支持度： ", ABSSupport

    # 一级频繁项
    frequentMap = {}

    header = getHeader(matrix, frequentMap)
    root = getFpTree(matrix, header, frequentMap)
    frequents = fpGrowth(root, header, None)

    for item in frequents.items():
        for node in item[0]:
            print(node.idName),
        print "",item[1]