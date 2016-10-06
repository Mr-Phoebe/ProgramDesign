import string
import re
pos_split = re.compile("[\u4E00-\uFFFF]+/[a-zA-Z]+")
orig_file = open("tagged_data.txt","r")
seg_flie = open("standard_result.txt","w")
passage = list()
for line in orig_file:
    line = line.strip()
    if len(line) == 0:
        if len(passage) > 0:
            seg_flie.writelines('  '.join(passage) + '\n')
            passage = []
    pos = re.findall(pos_split,line)
    for word in pos:
        if word != ' ':
            passage.append(word)
orig_file.close()
seg_flie.close()
