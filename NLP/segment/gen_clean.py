import re
import time

orig_file = open("tagged_data.txt","r")
clean_flle = open("clean_data.txt","w")
passage = list()
for ln in orig_file:
    line = ln.strip()
    if len(line) == 0:
        if len(passage) > 0:
            clean_flle.writelines(''.join(passage) + '\n')
            passage = []
            continue
    for ch in line:
        if ord(ch) > 128:
            passage.append(ch)
        else:
            continue
orig_file.close()
clean_flle.close()


