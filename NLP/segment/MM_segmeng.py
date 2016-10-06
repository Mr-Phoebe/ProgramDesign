import re
import time
from math import log

class ChineseSegment:
    words = set()
    re_userdict = re.compile('^(.+?)( +[0-9]+)?( +[a-z]+)?$', re.U)
    words_len = 0;

    def add_word(self,word):
        self.words.add(word)
        self.words_len = max(self.words_len,len(word))
        return
    def load_userdict(self):
        file = open("dict.txt.big","r")
        for line in file:
            line = line.strip()
            word,freq,tag = self.re_userdict.match(line).groups()
            self.add_word(word)
        file.close()
        return;
    def segment_sentence(self,sentence):
        i = 0
        while i < len(sentence):
            word = sentence[i:min(i+self.words_len,len(sentence))]
            sig = False
            while len(word) > 0:
                if word in self.words:
                    sig = True
                    break
                word = word[:-1]
            if sig:
                yield word
                i += len(word)
            else:
                yield sentence[i:i+1]
                i += 1
        return

    def training(self):
        file = open("training_data.txt","r")
        data = file.read().split("  ")
        for word in data:
            self.add_word(word)
        return


seger = ChineseSegment()
#seger.load_userdict()
seger.training()
data = open("test_data.txt","r")
result = open("result.txt","w")
for line in data:
    if len(line) > 0:
        result.writelines("  ".join(seger.segment_sentence(line)) )
data.close()
result.close()
