# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-02-02 10:48:44
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-02-02 10:50:01

samples = [  
    ["I1","I2","I5"],  
    ["I2","I4"],  
    ["I2","I3"],  
    ["I1","I2","I4"],  
    ["I1","I3"],  
    ["I2","I3"],  
    ["I1","I3"],  
    ["I1","I2","I3","I5"],  
    ["I1","I2","I3"]  
]  
min_support = 2  
min_confidence = 0.6  
fre_list = list()  
def get_c1():  
    global record_list  
    global record_dict  
    new_dict = dict()  
    for row in samples:  
        for item in row:  
            if item not in fre_list:  
                fre_list.append(item)  
                new_dict[item] = 1  
            else:  
                new_dict[item] = new_dict[item] + 1  
    fre_list.sort()  
    print "candidate set:"  
    print_dict(new_dict)  
    for key in fre_list:  
        if new_dict[key] < min_support:  
            del new_dict[key]  
    print "after pruning:"  
    print_dict(new_dict)  
    record_list = fre_list  
    record_dict = record_dict  
def get_candidateset():  
    new_list = list()  
    #自连接  
    for i in range(0,len(fre_list)):  
        for j in range(0,len(fre_list)):  
            if i == j:  
                continue  
            #如果两个k项集可以自连接，必须保证它们有k-1项是相同的  
            if has_samesubitem(fre_list[i],fre_list[j]):  
                curitem = fre_list[i] + ',' + fre_list[j]  
                curitem = curitem.split(",")  
                curitem = list(set(curitem))  
                curitem.sort()  
                curitem = ','.join(curitem)  
                #如果一个k项集要成为候选集，必须保证它的所有子集都是频繁的  
                if has_infresubset(curitem) == False and already_constains(curitem,new_list) == False:  
                    new_list.append(curitem)  
    new_list.sort()  
    return new_list  
def has_samesubitem(str1,str2):  
    str1s = str1.split(",")  
    str2s = str2.split(",")  
    if len(str1s) != len(str2s):  
        return False  
    nums = 0  
    for items in str1s:  
        if items in str2s:  
            nums += 1  
            str2s.remove(items)  
    if nums == len(str1s) - 1:  
        return True  
    else:  
        return False  
def judge(candidatelist):  
    # 计算候选集的支持度  
    new_dict = dict()  
    for item in candidatelist:  
        new_dict[item] = get_support(item)  
    print "candidate set:"  
    print_dict(new_dict)  
    #剪枝  
    #频繁集的支持度要大于最小支持度  
    new_list = list()  
    for item in candidatelist:  
        if new_dict[item] < min_support:  
            del new_dict[item]  
            continue  
        else:  
            new_list.append(item)  
    global fre_list  
    fre_list = new_list  
    print "after pruning:"  
    print_dict(new_dict)  
    return new_dict  
def has_infresubset(item):  
    # 由于是逐层搜索的，所以对于Ck候选集只需要判断它的k-1子集是否包含非频繁集即可  
    subset_list = get_subset(item.split(","))  
    for item_list in subset_list:  
        if already_constains(item_list,fre_list) == False:  
            return True  
    return False  
def get_support(item,splitetag=True):  
    if splitetag:  
        items = item.split(",")  
    else:  
        items = item.split("^")  
    support = 0  
    for row in samples:  
        tag = True  
        for curitem in items:  
            if curitem not in row:  
                tag = False  
                continue  
        if tag:  
            support += 1  
    return support  
def get_fullpermutation(arr):  
    if len(arr) == 1:  
        return [arr]  
    else:  
        newlist = list()  
        for i in range(0,len(arr)):  
            sublist = get_fullpermutation(arr[0:i]+arr[i+1:len(arr)])  
            for item in sublist:  
                curlist = list()  
                curlist.append(arr[i])  
                curlist.extend(item)  
                newlist.append(curlist)  
        return newlist  
def get_subset(arr):  
    newlist = list()  
    for i in range(0,len(arr)):  
        arr1 = arr[0:i]+arr[i+1:len(arr)]  
        newlist1 = get_fullpermutation(arr1)  
        for newlist_item in newlist1:  
            newlist.append(newlist_item)  
    newlist.sort()  
    newlist = remove_dumplicate(newlist)  
    return newlist  
def remove_dumplicate(arr):  
    newlist = list()  
    for i in range(0,len(arr)):  
        if already_constains(arr[i],newlist) == False:  
            newlist.append(arr[i])  
    return newlist  
def already_constains(item,curlist):  
    import types  
    items = list()  
    if type(item) is types.StringType:  
        items = item.split(",")  
    else:  
        items = item  
    for i in range(0,len(curlist)):  
        curitems = list()  
        if type(curlist[i]) is types.StringType:  
            curitems = curlist[i].split(",")  
        else:  
            curitems = curlist[i]  
        if len(set(items)) == len(curitems) and len(list(set(items).difference(set(curitems)))) == 0:  
            return True  
    return False  
def print_dict(curdict):  
    keys = curdict.keys()  
    keys.sort()  
    for curkey in keys:  
        print "%s:%s"%(curkey,curdict[curkey])  
# 计算关联规则的方法  
def get_all_subset(arr):  
    rtn = list()  
    while True:  
        subset_list = get_subset(arr)  
        stop = False  
        for subset_item_list in subset_list:  
            if len(subset_item_list) == 1:  
                stop = True  
            rtn.append(subset_item_list)  
        if stop:  
            break  
    return rtn  
def get_all_subset(s):  
    from itertools import combinations  
    return sum(map(lambda r: list(combinations(s, r)), range(1, len(s)+1)), [])  
def cal_associative_rule(frelist):  
    rule_list = list()  
    rule_dict = dict()  
    for fre_item in frelist:  
        fre_items = fre_item.split(",")  
        subitem_list = get_all_subset(fre_items)  
        for subitem in subitem_list:  
            # 忽略为为自身的子集  
            if len(subitem) == len(fre_items):  
                continue  
            else:  
                difference = set(fre_items).difference(subitem)  
                rule_list.append("^".join(subitem)+"->"+"^".join(difference))  
    print "The rule is:"  
    for rule in rule_list:  
        conf = cal_rule_confidency(rule)  
        print rule,conf  
        if conf >= min_confidence:  
            rule_dict[rule] = conf  
    print "The associative rule is:"  
    for key in rule_list:  
        if key in rule_dict.keys():  
            print key,":",rule_dict[key]  
def cal_rule_confidency(rule):  
    rules = rule.split("->")  
    support1 = get_support("^".join(rules),False)  
    support2 = get_support(rules[0],False)  
    if support2 == 0:  
        return 0  
    rule_confidency = float(support1)/float(support2)  
    return rule_confidency  
if __name__ == '__main__':  
    record_list = list()  
    record_dict = dict()  
    get_c1()  
    # 不断进行自连接和剪枝，直到得到最终的频繁集为止;终止条件是，如果自连接得到的已经不再是频繁集  
    # 那么取最后一次得到的频繁集作为结果  
    while True:  
        record_list = fre_list  
        new_list = get_candidateset()  
        judge_dict = judge(new_list)  
        if len(judge_dict) == 0:  
            break  
        else:  
            record_dict = judge_dict  
    print "The final frequency set is:"  
    print record_list  

    # 根据频繁集计算关联规则  
    cal_associative_rule(record_list)  