import numpy as np
import math


class KNN:
    def __init__(self, k):
        # KNN state here
        # Feel free to add methods
        self.k = k

    def distance(self, featureA, featureB):
        diffs = (featureA - featureB)**2
        return np.sqrt(diffs.sum())

    def train(self, X, y):
        # training logic here
        # input is an array of features and labels
        self.samples = np.array(X)
        self.labels = np.array(y)

    def predict(self, X):
        # Run model here
        # Return array of predictions where there is one prediction for each set of features
        prediction = np.array([])
        for x in X:
            distanceVector = self.getDistace(x)
            kNearestNeighbours = self.getKNN(distanceVector)
            classification = self.getLable(kNearestNeighbours)
            prediction = np.append(prediction, [classification])
        return prediction

    def getDistace(self, x):
        distances = list(
            map(lambda sample: self.distance(x, sample), self.samples))
        return zip(distances, self.labels)

    def getKNN(self, disatanceVector):
        disatanceVector = sorted(disatanceVector, key=lambda x: x[0])
        return disatanceVector[:self.k]

    def getLable(self, kNearestNeighbours):
        vote = {}
        for neighbour in kNearestNeighbours:
            label = neighbour[1]
            if label in vote:
                vote[label] += 1
            else:
                vote[label] = 1
        return max(vote, key=vote.get)


class ID3:
    def __init__(self, nbins, data_range):
        # Decision tree state here
        # Feel free to add methods
        self.bin_size = nbins
        self.range = data_range

    def preprocess(self, data):
        # Our dataset only has continuous data
        norm_data = (data - self.range[0]) / (self.range[1] - self.range[0])
        categorical_data = np.floor(self.bin_size * norm_data).astype(int)
        return categorical_data

    def train(self, X, y):
        # training logic here
        # input is array of features and labels
        categorical_data = self.preprocess(X)
        featureIndex = tuple(['x' + str(i) for i in range(X.shape[1])])
        self.tree = self.build(categorical_data, y, featureIndex)

    def predict(self, X):
        # Run model here
        # Return array of predictions where there is one prediction for each set of features
        X = self.preprocess(X)

        def classify(root, sample):
            featIndex = list(root.keys())[0]
            secondDict = root[featIndex]
            child = list(secondDict.items())[0]
            for i in range(1, len(featIndex)):
                key = sample[int(featIndex[i:])]
                if key in secondDict:
                    child = secondDict[key]
                    break

            return child if not isinstance(child, dict) else classify(child, sample)

        results = []
        for i in range(X.shape[0]):
            results.append(classify(self.tree, X[i]))
        return np.array(results)

    def build(self, X, y, featureIndex):
        number = np.count_nonzero(y)
        if number == len(y) or number == 0:
            return y[0]
        if len(featureIndex) == 0:
            return np.argmax(np.bincount(y))

        bestFeatIndex = self.ID3(X, y)

        bestFeatStr = featureIndex[bestFeatIndex]
        featureIndex = list(featureIndex)
        featureIndex.remove(bestFeatStr)
        featureIndex = tuple(featureIndex)

        root = {bestFeatStr: {}}
        uniqueVals = set(X[:, bestFeatIndex])
        for value in uniqueVals:
            sub_X, sub_y = self.splitDataSet(X, y, bestFeatIndex, value)
            root[bestFeatStr][value] = self.build(
                sub_X, sub_y, featureIndex)
        return root

    def ID3(self, X, y):
        numFeatures = X.shape[1]
        oldEntropy = self.calcEntropy(y)
        bestInfoGain = 0.0
        bestFeatureIndex = -1

        for i in range(numFeatures):
            uniqueVals = set(X[:, i])
            newEntropy = 0.0

            for value in uniqueVals:
                sub_X, sub_y = self.splitDataSet(X, y, i, value)
                prob = len(sub_y) / len(y)
                newEntropy += prob * self.calcEntropy(sub_y)

            infoGain = oldEntropy - newEntropy
            if infoGain > bestInfoGain:
                bestInfoGain = infoGain
                bestFeatureIndex = i
        return bestFeatureIndex

    def calcEntropy(self, y):
        labelCounts = np.bincount(y) / y.shape[0]
        labelCounts = labelCounts[labelCounts > 0]
        entropy = 0.0
        for prob in labelCounts:
            entropy -= prob * np.log2(prob)
        return entropy

    def splitDataSet(self, X, y, index, value):
        mask = X[:, index] == value
        # X = np.delete(X, index, 1)
        X = X[:, [i for i in range(X.shape[1]) if i != index]]
        return X[mask, :], y[mask]


class Perceptron:
    def __init__(self, w, b, lr):
        # Perceptron state here, input initial weight matrix
        # Feel free to add methods
        self.lr = lr
        self.w = w
        self.b = b

    def train(self, X, y, steps):
        # training logic here
        # input is array of features and labels
        i = 0
        while i < steps:
            train = X[i % len(X)]
            target = y[i % len(y)]
            output = 0 if np.dot(train, self.w) + self.b < 0 else 1
            if output != target:
                self.w = self.w + self.lr * target * train
                self.b = self.b + self.lr * target
            i += 1

    def predict(self, X):
        # Run model here
        # Return array of predictions where there is one prediction for each set of features
        predictions = []
        for test in X:
            predictions.append(
                0 if np.dot(test, self.w) + self.b < 0 else 1)
        return np.array(predictions)


class MLP:
    def __init__(self, w1, b1, w2, b2, lr):
        self.l1 = FCLayer(w1, b1, lr)
        self.a1 = Sigmoid()
        self.l2 = FCLayer(w2, b2, lr)
        self.a2 = Sigmoid()

    def MSE(self, prediction, target):
        return np.square(target - prediction).sum()

    def MSEGrad(self, prediction, target):
        return -2.0 * (target - prediction)

    def shuffle(self, X, y):
        idxs = np.arange(y.size)
        np.random.shuffle(idxs)
        return X[idxs], y[idxs]

    def train(self, X, y, steps):
        for s in range(steps):
            i = s % y.size
            if (i == 0):
                X, y = self.shuffle(X, y)
            xi = np.expand_dims(X[i], axis=0)
            yi = np.expand_dims(y[i], axis=0)

            pred = self.l1.forward(xi)
            pred = self.a1.forward(pred)
            pred = self.l2.forward(pred)
            pred = self.a2.forward(pred)
            # loss = self.MSE(pred, yi)
            # print(loss)

            grad = self.MSEGrad(pred, yi)
            grad = self.a2.backward(grad)
            grad = self.l2.backward(grad)
            grad = self.a1.backward(grad)
            grad = self.l1.backward(grad)

    def predict(self, X):
        pred = self.l1.forward(X)
        pred = self.a1.forward(pred)
        pred = self.l2.forward(pred)
        pred = self.a2.forward(pred)
        pred = np.round(pred)
        return np.ravel(pred)


class FCLayer:
    def __init__(self, w, b, lr):
        self.lr = lr
        self.w = w  # Each column represents all the weights going into an output node
        self.b = b

    def forward(self, input):
        # Write forward pass here
        self.input = input
        return np.dot(input, self.w) + self.b

    def backward(self, gradients):
        # Write backward pass herem
        dw = np.dot(self.input.T, gradients)
        dx = np.dot(gradients, self.w.T)
        self.w = self.w - self.lr * dw
        self.b = self.b - self.lr * gradients
        return dx


class Sigmoid:
    def __init__(self):
        pass

    def forward(self, input):
        # Write forward pass here
        self.output = np.tanh(input)
        return self.output

    def backward(self, gradients):
        # Write backward pass here
        return (1 - self.output**2) * gradients
