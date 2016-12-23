# -*- coding: utf-8 -*-
import urllib


def print_list(list):
    for i in list:
        print(i)


def demo():
    s = urllib.urlopen('http://blog.kamidox.com/no-exist')
    msg = s.info()
    s.getcode()
    print_list(msg.status)


def progress(blk, blk_size, total_size):
    print('%d/%d - %.02f%%' % (blk * blk_size, total_size, (float)(blk * blk_size) * 100 / total_size))


def retrieve():
    urllib.urlretrieve('http://blog.kamidox.com', 'index.html', reporthook=progress)


if __name__ == '__main__':
    retrieve()