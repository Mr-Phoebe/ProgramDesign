import re
import time
from math import log


class ChineseSegment:

    re_userdict = re.compile('^(.+?)( +[0-9]+)?( +[a-z]+)?$', re.U)
    re_partition = re.compile("([\u4E00-\u9FD5a-zA-Z0-9+#&\._]+)", re.U)
    re_skip = re.compile("(\r\n|\s)", re.U)
    re_english = re.compile('[a-zA-Z0-9]',re.U)

    word_freqence = {}
    total_frequence = 0

    def add_word(self,word, freq=None, tag=None):
        freq = int(freq)
        self.word_freqence[word] = freq
        self.total_frequence += freq
        for i in range(len(word)):
            pre_word = word[:i + 1]
            if pre_word not in self.word_freqence:
                self.word_freqence[pre_word] = 0
        return

    def load_userdict(self):

        file = open("dict.txt.big","r")
        for lineno,ln in enumerate(file,1):
            line = ln.strip()
            word, freq, tag = self.re_userdict.match(line).groups()
            self.add_word(word,freq,tag)
        file.close()
        return;

    def training(self):
        file = open("training_data.txt","r")
        words = file.read().split('  ')
        word_cnt = {}
        for word in words:
            if word not in word_cnt:
                word_cnt[word] =0
            word_cnt[word] += 1
        for key,value in word_cnt.items():
            self.add_word(key,value,None)
        return

    def construct_DAG(self,sentence):
        DAG = {}
        N = len(sentence)
        for i in range(N):
            nextpos = []
            j = i
            prefix = sentence[i]
            while j < N and prefix in self.word_freqence:
                if self.word_freqence[prefix]:
                    nextpos.append(j)
                j += 1
                prefix = sentence[i:j+1]
            if not nextpos:
                nextpos.append(i)
            DAG[i] = nextpos
        return DAG

    def construct_path(self,sentence,DAG):
        N  = len(sentence)
        path = {}
        path[N] = (0,0)
        logtotal = log(self.total_frequence)
        for i in range(N - 1, -1, -1):
            path[i] = max((log(self.word_freqence.get(sentence[i:x+1]) or 1) -
                            logtotal + path[x+1][0],x) for x in DAG[i])
        return path

    def segment_block(self,sentence):
        word_DAG = self.construct_DAG(sentence)
        path = self.construct_path(sentence,word_DAG)
        x = 0
        buf = ''
        N = len(sentence)
        while x < N:
            y = path[x][1] + 1
            word = sentence[x:y]
            if self.re_english.match(word) and len(word) == 1:
                buf += word
                x = y
            else:
                if buf:
                    yield buf
                yield word
                x = y
        if buf:
            yield buf
            buf = ''
        return;

    def segment_sentence(self,sentence):

        blocks = self.re_partition.split(sentence)
        for blk in blocks:
            if not blk:
                continue;
            if self.re_partition.match(blk):
                for word in self.segment_block(blk):
                    yield word
            else:
                others = self.re_skip.split(blk)
                for other in others:
                    for i in other:
                        yield i
        return;


seger = ChineseSegment()
seger.load_userdict()
#seger.training()
data = open("test_data.txt","r")
result = open("result.txt","w")
for line in data:
    if len(line) > 0:
        result.writelines("  ".join(seger.segment_sentence(line)))
data.close()
result.close()
