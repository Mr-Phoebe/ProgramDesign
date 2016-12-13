# Using lasagne to fit mnist.
# show how to use NeuralNet
# Tarrega, 150611.

import lasagne
from lasagne import layers
from lasagne.updates import nesterov_momentum
from nolearn.lasagne import NeuralNet
import os
from urllib import urlretrieve
import gzip
import pickle
import numpy

DATA_URL = 'http://deeplearning.net/data/mnist/mnist.pkl.gz'
DATA_FILENAME = './data/mnist.pkl.gz'

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
    y_train = numpy.asarray(y_train,dtype='int32')
    #X_valid, y_valid = data[1]
    #X_test, y_test = data[2]
    print 'size:',X_train.shape, y_train.shape, X_train.dtype, y_train.dtype
    return X_train,y_train


net1 = NeuralNet(
    layers=[  # three layers: one hidden layer
        ('input', layers.InputLayer),
        ('hidden', layers.DenseLayer),
        ('output', layers.DenseLayer),
        ],
    # layer parameters:
    input_shape=(None, 28*28),  # 28x28 input pixels per batch
    hidden_num_units=200,  # number of units in hidden layer
    output_nonlinearity=lasagne.nonlinearities.softmax,  # output layer
    output_num_units=10,  # 10 target values

    # optimization method:
    update=nesterov_momentum,
    update_learning_rate=0.01,
    update_momentum=0.9,

    regression=False,  # flag to indicate we're dealing with regression problem
    max_epochs=400,  # we want to train this many epochs
    verbose=1,
    )

X, y = load()
net1.fit(X, y)