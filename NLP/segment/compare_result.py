result_file = open("result.txt",'r')
standard_file = open("standard_result.txt","r")
result = result_file.read().split()
standard = standard_file.read().split()
N = len(result)
M = len(standard)
i = 0
j = 0
correct = 0
wrong = 0
while i < N and j < M:
    if(result[i] == standard[j]):
        correct += 1
        i += 1
        j += 1
    else:
        rbuf = []
        sbuf = []
        rlen = len(result[i])
        rbuf.append(result[i])
        i += 1
        slen = len(standard[j])
        sbuf.append(standard[j])
        j += 1
        while i < N and j < M and rlen != slen:
            if rlen > slen:
                slen += len(standard[j])
                sbuf.append(standard[j])
                j += 1
            else:
                rlen += len(result[i])
                rbuf.append(result[i])
                i += 1

print("the precision is %f"%(correct * 100 / N))
print("the recall is %f"%(correct * 100 / M))

result_file.close()
standard_file.close()
