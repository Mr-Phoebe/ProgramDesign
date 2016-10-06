
def Viterbi(words):
    global start_prob,trans_prob,emit_prob,hidden_state,observe_state,h_size,o_size

    t_size = len(words)
    pre = [[None for j in range(h_size)] for i in range(t_size)]
    dp = [[-1e+100 for j in range(h_size)] for i in range(t_size)]

    for i in range(h_size):
        dp[0][i] = start_prob[i] + emit_prob[i][observe_state[words[0]]]
    for t in range(t_size-1):
        for j in range(h_size):
            for i in range(h_size):
                tmp = dp[t][i] + trans_prob[i][j] + emit_prob[j][observe_state[words[t+1]]]
                if dp[t+1][j] < tmp:
                    dp[t+1][j] = tmp
                    pre[t+1][j] = i
        flag = True
        for j in range(h_size):
            if dp[t+1][j] != -1e+100:
                flag = False
                break
        if flag:
            print(words[t],words[t+1])
            return


    maxval = -1e+100
    pos =[None for i in range(t_size)]
    for i in range(h_size):
        if dp[t_size-1][i] > maxval:
            maxval = dp[t_size - 1][i]
            pos[t_size-1] = i
    print(maxval)
    for t in range(t_size-1,0,-1):
        pos[t-1] = pre[t][pos[t]]

    for i in range(t_size):
        words[i] += '/' + hidden_state[pos[i]]
    return words

observe_state = {}
observe_flie = open("observe_state.txt","r")
for line in observe_flie:
    word, wid = line.split()
    observe_state[word] = int(wid)
observe_flie.close()

hidden_state = {}
hidden_file = open("hidden_state.txt","r")
for line in hidden_file:
    word, wid = line.split()
    hidden_state[int(wid)] = word
hidden_file.close()

h_size = len(hidden_state)
o_size = len(observe_state)
start_file = open("start_prob.txt","r")
start_prob = eval(start_file.read())
start_file.close()

trans_file = open("trans_prob.txt","r")
trans_prob = eval(trans_file.read())
trans_file.close()

emit_file = open("emit_prob.txt","r")
emit_prob= eval(emit_file.read())
emit_file.close()


test_file = open("test_data.txt","r")
result_file = open("result.txt","w")
for lineno,line in enumerate(test_file):
    print(lineno)
    words = line.strip().split('  ')
    try:
        pos = Viterbi(words)
        result_file.write('  '.join(pos) + '\n')
    except(TypeError):
        print('××')

test_file.close()
result_file.close()



