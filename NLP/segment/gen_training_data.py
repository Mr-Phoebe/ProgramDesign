orig_file = open("all_result.txt","r")
training_file = open("training_data.txt","w")
cnt=0
for line in orig_file:
    cnt += 1
    if cnt == 2500:
        pass
    training_file.writelines(line)
orig_file.close()
training_file.close()
