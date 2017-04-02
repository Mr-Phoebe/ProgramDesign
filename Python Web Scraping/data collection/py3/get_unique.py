# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-03-18 10:34:37
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-03-18 10:34:44

import json

def keep_unique(li, anchor):
    fa_set = set()
    result = []
    for i in len(li):
        if json.dumps(li[i]) not in fa_set:
            result.append(anchor[i])
            fa_set.add(json.dumps(li[i]))
    return result