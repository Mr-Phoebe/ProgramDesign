# Using lasagne to fit mnist.
# show how to use NeuralNet
# HaonanWu, 12/16/16.

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

DATA_URL = 'http://deeplearning.net/data/mnist/mnist.pkl.gz'
DATA_FILENAME = './data/mnist.pkl.gz'

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


def pickle_load(f, encoding):
    return pickle.load(f)

def _load_data(url=DATA_URL, filename=DATA_FILENAME):
    """Load data from `url` and store the result in `filename`."""
    print 'filename for the minist datatset:',filename
    if not os.path.exists(filename):
        print("Downloading MNIST dataset")
        urlretrieve(url, filename)

    with gzip.open(filename, 'rb') as f:
        return pickle_load(f, encoding='latin-1')


def load():
    """Get data with labels, split into training, validation and test set."""
    data = _load_data()
    X_train, y_train = data[0]
    y_train = np.asarray(y_train,dtype='int32')
    #X_valid, y_valid = data[1]
    #X_test, y_test = data[2]
    print 'size:',X_train.shape, y_train.shape, X_train.dtype, y_train.dtype
    return X_train,y_train


net3 = NeuralNet(
    layers=[  # three layers: one hidden layer
        ('input', layers.InputLayer),
        ('dropout1', layers.DropoutLayer),
        ('hidden1', layers.DenseLayer),
        ('output', layers.DenseLayer),
        ],
    # layer parameters:
    input_shape=(None, 28*28),  # 28x28 input pixels per batch
    hidden1_num_units=200,  # number of units in hidden layer
    output_nonlinearity=lasagne.nonlinearities.softmax,  # output layer
    output_num_units=10,  # 10 target values

    dropout1_p=0.1,

    # optimization method:
    update=nesterov_momentum,
    update_learning_rate=theano.shared(float32(0.03)),
    update_momentum=theano.shared(float32(0.9)),

    regression=False,
    on_epoch_finished=[
        AdjustVariable('update_learning_rate', start=0.03, stop=0.0001),
        AdjustVariable('update_momentum', start=0.9, stop=0.999),
        ],
    max_epochs=1000,
    verbose=1,
    )

X, y = load()
net3.fit(X, y)

with open('net3.pickle', 'wb') as f:
    pickle.dump(net3, f, -1)

train_loss = np.array([i["train_loss"] for i in net3.train_history_])
valid_loss = np.array([i["valid_loss"] for i in net3.train_history_])
pyplot.plot(train_loss, linewidth=3, label="net3_train")
pyplot.plot(valid_loss, linewidth=3, label="net3_valid")
pyplot.grid()
pyplot.legend()
pyplot.xlabel("epoch")
pyplot.ylabel("loss")
pyplot.ylim(1e-3, 1)
pyplot.yscale("log")
pyplot.show()