# Using lasagne to fit mnist.
# show how to use NeuralNet
# HaonanWu, 12/18/16.

import lasagne
import theano
from lasagne import layers
from lasagne.updates import nesterov_momentum
from nolearn.lasagne import NeuralNet
import os
from urllib import urlretrieve
import gzip
import pickle
import numpy as np
from matplotlib import pyplot

def float32(k):
    return np.cast['float32'](k)

class AdjustVariable(object):
    def __init__(self, name, start = 0.03, stop = 0.001):
        self.name = name
        self.start, self.stop = start, stop
        self.ls = None
    def __call__(self, nn, train_history):
        if self.ls is None:
            self.ls = np.linspace(self.start, self.stop, nn.max_epochs)
        epoch = train_history[-1]['epoch']
        new_value = float32(self.ls[epoch - 1])
        getattr(nn, self.name).set_value(new_value)

f2 = open('net2.pickle', 'rb')
net2 = pickle.load(f2)

f3 = open('net3.pkl', 'rb')
net3 = pickle.load(f3)

train_loss = np.array([i["train_loss"] for i in net2.train_history_])
valid_loss = np.array([i["valid_loss"] for i in net2.train_history_])
pyplot.plot(train_loss, linewidth=3, label="net2_train")
pyplot.plot(valid_loss, linewidth=3, label="net2_valid")
train_loss = np.array([i["train_loss"] for i in net3.train_history_])
valid_loss = np.array([i["valid_loss"] for i in net3.train_history_])
pyplot.plot(train_loss, '--', linewidth=3, label="net3_train")
pyplot.plot(valid_loss, '--', linewidth=3, label="net3_valid")
pyplot.grid()
pyplot.legend()
pyplot.xlabel("epoch")
pyplot.ylabel("loss")
pyplot.ylim(1e-6, 1)
pyplot.yscale("log")
pyplot.show()