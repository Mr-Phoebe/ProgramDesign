import jieba.posseg as pseg
import jieba
data = open("data.txt","r")
result = open("result.txt","w")
pos = pseg.POSTokenizer(jieba.Tokenizer(dictionary='dict.txt.big'))
for line in data:
    words = pos.cut(line)
    for word, flag in words:
        result.write('%s\%s '%(word,flag))
    break
data.close()
result.close()
words = pos.cut('我的老师说：“我们大家都是好孩子，好孩子应该看《好书》”')
for word, flag in words:
    print('%s %s'%(word,flag))

