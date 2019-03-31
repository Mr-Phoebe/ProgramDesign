import assignment3 as models
import numpy as np

#==========================================================Data==========================================================
# Number of Instances:    
# 569
# Number of Attributes:
# 30 numeric, predictive attributes and the class

# Attribute Information:
# radius (mean of distances from center to points on the perimeter)
# texture (standard deviation of gray-scale values)
# perimeter
# area
# smoothness (local variation in radius lengths)
# compactness (perimeter^2 / area - 1.0)
# concavity (severity of concave portions of the contour)
# concave points (number of concave portions of the contour)
# symmetry
# fractal dimension (“coastline approximation” - 1)

# The mean, standard error, and “worst” or largest (mean of the three largest values) of these features were computed for each image, resulting in 30 features

# Class Distribution:
# 212 - Malignant (0), 357 - Benign (1)
#========================================================================================================================

def train_test_split(X, y, test_ratio):
    tr = int(y.size*test_ratio)
    return X[:tr], X[tr:], y[:tr], y[tr:]

def load_data(path):
    data = np.genfromtxt(path, delimiter=',', dtype=float)
    return data[:,:-1], data[:,-1].astype(int)

X, y = load_data("breast_cancer_dataset.csv")
X_train, X_test, y_train, y_test = train_test_split(X, y, 0.75)

#Initialization
#KNN
k = 3
knn = models.KNN(k)
#ID3
nbins = 3
data_range = (X_train.min(0), X_train.max(0))
id3 = models.ID3(nbins, data_range)
#Perceptron
lr = .001
w = np.random.normal(0, .1, size=X_train.shape[1])    #Each column represents all the weights going into an output node
b = np.random.normal(0, .1, size=1)
perceptron = models.Perceptron(w, b, lr)
#MLP
lr = .0001
w1 = np.random.normal(0, .1, size=(X_train.shape[1], 10))
w2 = np.random.normal(0, .1, size=(10,1))
b1 = np.random.normal(0, .1, size=(1,10))
b2 = np.random.normal(0, .1, size=(1,1))
mlp = models.MLP(w1, b1, w2, b2, lr)

#Train
steps = 100*y_train.size
knn.train(X_train, y_train)
id3.train(X_train, y_train)
perceptron.train(X_train, y_train, steps)
mlp.train(X_train, y_train, steps)

#Check weights (For grading)
# perceptron.w
# perceptron.b
# mlp.w1
# mlp.b1
# mlp.w2
# mlp.b2

#Evaluate
def evaluate(solutions, real):
    if(solutions.shape != real.shape):
        raise ValueError("Output is wrong shape.")
    predictions = np.array(solutions)
    labels = np.array(real)
    return (predictions == labels).sum() / float(labels.size)

solutions = knn.predict(X_test)
print(evaluate(solutions, y_test))
solutions = id3.predict(X_test)
print(evaluate(solutions, y_test))
solutions = perceptron.predict(X_test)
print(evaluate(solutions, y_test))
solutions = mlp.predict(X_test)
print(evaluate(solutions, y_test))
