stand= open("standard_result.txt","r")
result = open("result.txt","r")
stand_words = stand.read().split()
result_words =  result.read().split()
if len(stand_words) != len(result_words):
    print("bad")
allword = len(stand_words)
print(len(stand_words),len(result_words))
wrongword = 0
for word in zip(stand_words,result_words):
    print(word[0],word[1])
    if word[0] != word[1]:
        wrongword += 1
print(allword,wrongword)
print((allword - wrongword) / allword * 100)
