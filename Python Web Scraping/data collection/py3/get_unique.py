# -*- coding: utf-8 -*-
# @Author: HaonanWu
# @Date:   2017-03-18 10:34:37
# @Last Modified by:   HaonanWu
# @Last Modified time: 2017-03-18 10:34:44

import json

def keep_unique(li):
    label_set = set(map(json.dumps, li))
    return map(json.loads, list(label_set))