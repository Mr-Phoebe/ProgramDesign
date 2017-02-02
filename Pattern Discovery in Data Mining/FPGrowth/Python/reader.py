# -*- coding: utf-8 -*-

def  readAsMatrix(fileName, regex, encoding):
    '''
    :param fileName: 文件名
    :param regex: 文件分隔符
    :param encoding: 文件编码
    :return:
    '''
    matrix = []
    row = 0
    fp = open(fileName, 'r+')
    for line in fp.readlines():
        matrix.append(line.replace("\n","").split(regex))
    fp.close()
    return matrix


if __name__ == '__main__':
    matrix = readAsMatrix("retail.txt", "\t", "utf-8")
    print matrix
