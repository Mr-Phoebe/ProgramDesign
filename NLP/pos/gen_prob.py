from math import log
def calc_forward():
    global start_prob, trans_prob,emit_prob,observe_state,training_pair,forw_prob,h_size,t_size

    for i in range(h_size):
        forw_prob[0][i] = start_prob[i] * emit_prob[i][observe_state[training_pair[0][0]]]
    for t in range(t_size - 1):
        for j in range(h_size):
            forw_prob[t+1][j] = 0.0
            for i in range(h_size):
                forw_prob[t+1][j] += forw_prob[t][i] * trans_prob[i][j]
            forw_prob[t+1][j] *= emit_prob[j][observe_state[training_pair[t+1][0]]]
    return

def calc_backward():
    global trans_prob,emit_prob,observe_state,back_porb,t_size,h_size,training_pair,back_porb

    for i in range(h_size):
        back_porb[t_size-1][i] = 1.0;
    for t in range(t_size-2, -1, -1):
        for i in range(h_size):
            back_porb[t][i] = 0.0
            for j in range(h_size):
                back_porb[t][i] += trans_prob[i][j] * back_porb[t+1][j] * emit_prob[j][observe_state[training_pair[t+1][0]]]
    return

def training():
    global start_prob,trans_prob,emit_prob,h_size,o_size

    training_file = open("training_data.txt","r")
    cnt = 0
    for line in training_file:
        cnt+= 1
        print(cnt)
        training_pair = []
        for word in line.split():
            training_pair.append(word.split('/'))
        for i in range(len(training_pair)):
            emit_prob[hidden_state[training_pair[i][1]]][observe_state[training_pair[i][0]]] += 1
            if i == 0:
                start_prob[hidden_state[training_pair[i][1]]] += 1
            else:
                trans_prob[hidden_state[training_pair[i-1][1]]][hidden_state[training_pair[i][1]]] += 1

    for i in range(h_size):
        start_prob[i] += 0.01
    for i in range(h_size):
        for j in range(h_size):
            trans_prob[i][j] += 0.01
    for i in range(h_size):
        for j in range(o_size):
            emit_prob[i][j] += 0.01

    psum = 0
    for i in range(h_size):
        psum += start_prob[i]
    for i in range(h_size):
        start_prob[i] /= psum

    for i in range(h_size):
        psum = 0
        for j in range(h_size):
            psum += trans_prob[i][j]
        for j in range(h_size):
            trans_prob[i][j] /= psum

    for i in range(h_size):
        psum = 0
        for j in range(o_size):
            psum += emit_prob[i][j]
        for j in range(o_size):
            emit_prob[i][j] /= psum
    emit_file = open("orig_emit_prob.txt","w")
    emit_file.write(repr(emit_prob))
    emit_file.close()

    start_file = open("orig_start_prob.txt","w")
    start_file.write(repr(start_prob))
    start_file.close()

    trans_file = open("orig_trans_prob.txt","w")
    trans_file.write(repr(trans_prob))
    trans_file.close()

    for i in range(h_size):
        if start_prob[i] == 0.0:
            start_prob[i] = -1e+100
        else:
            start_prob[i] = log(start_prob[i])
    for i in range(h_size):
        for j in range(h_size):
            if trans_prob[i][j] == 0.0:
                trans_prob[i][j] = -1e+100
            else:
                trans_prob[i][j] = log(trans_prob[i][j])
    for i in range(h_size):
        for j in range(o_size):
            if emit_prob[i][j] == 0.0:
                emit_prob[i][j] = -1e+100
            else:
                emit_prob[i][j] = log(emit_prob[i][j])

    emit_file = open("emit_prob.txt","w")
    emit_file.write(repr(emit_prob))
    emit_file.close()

    start_file = open("start_prob.txt","w")
    start_file.write(repr(start_prob))
    start_file.close()

    trans_file = open("trans_prob.txt","w")
    trans_file.write(repr(trans_prob))
    trans_file.close()
    return

def EM():
    global start_prob,trans_prob,emit_prob,forw_prob,back_porb,h_size,o_size,training_pair


    iter_times = 20
    for times in range(iter_times):
        print(times)
        calc_forward()
        calc_backward()
        for t in range(t_size):
            for i in range(h_size):
                print(forw_prob[t][i],back_porb[t][i])

        for t in range(t_size):
            gamma_sum[t] = 0.0
            for i in range(h_size):
                gamma_sum[t] += forw_prob[t][i] * back_porb[t][i]

        for t in range(t_size-1):
            for i in range(h_size):
                for j in range(h_size):
                    gamma[t][i][j] = forw_prob[t][i] * trans_prob[i][j] * emit_prob[j][observe_state[training_pair[t+1][0]]] * back_porb[t+1][j] / gamma_sum[t]

        for t in range(t_size):
            for i in range(h_size):
                xi[t][i] = forw_prob[t][i] * back_porb[t][i] / gamma_sum[t]

        for i in range(h_size):
            xi_sum[i] = 0.0;
            for t in range(t_size):
                xi_sum += xi[t][i]

        for i in range(h_size):
            start_prob[i] = xi[0][i]

        for i in range(h_size):
            for j in range(h_size):
                trans_prob[i][j] = 0.0
                for t in range(t_size-1):
                    trans_prob[i][j] += gamma[t][i][j]
                trans_prob[i][j] /= (xi_sum[i] - xi[t_size - 1][i])

        for j in range(h_size):
            for k in range(o_size):
                emit[j][k] = 0.0
                for t in range(t_size):
                    if(observe_state[training_pair[t][0]] == k):
                        emit[j][k] += xi[t][j]
                emit[j][k] /= xi_sum[j]

    return

observe_state = {}
hidden_state = {}
observe_flie = open("observe_state.txt","r")
for line in observe_flie:
    word, wid = line.split()
    observe_state[word] = int(wid)
observe_flie.close()

hidden_file = open("hidden_state.txt","r")
for line in hidden_file:
    word, wid = line.split()
    hidden_state[word] = int(wid)
hidden_file.close()

h_size = len(hidden_state)
o_size = len(observe_state)


start_prob = [0 / h_size for i in range(h_size)]
print(1)
trans_prob = [[0 / h_size for j in range(h_size)] for i in range(h_size)]
print(2)
emit_prob =  [[0 for j in range(o_size)] for i in range(h_size)]
print(3)


training()
