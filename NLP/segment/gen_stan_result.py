import string
orig_file = open("tagged_data.txt","r")
seg_flie = open("standard_result.txt","w")
passage = list()
linen = 0
for line in orig_file:
    cnt = 0
    line = line.strip()
    if len(line) == 0:
        if len(passage) > 0:
            linen += 1
            #if linen >= 2500:
            seg_flie.writelines(''.join(passage) + '\n')
            passage = []
    for ch in line:
        if ord(ch) > 128:
            passage.append(ch)
            cnt = 0
        if ch == ' ' and cnt  < 2:
            passage.append(ch)
            cnt += 1
        else:
            continue
orig_file.close()
seg_flie.close()

