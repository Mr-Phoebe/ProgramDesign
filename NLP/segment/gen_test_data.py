orig_file = open("clean_data.txt","r")
test_file = open("test_data.txt","w")
cnt = 0
for line in orig_file:
    cnt += 1
    if cnt < 2500:
        pass
    test_file.writelines(line)
orig_file.close()
test_file.close()
