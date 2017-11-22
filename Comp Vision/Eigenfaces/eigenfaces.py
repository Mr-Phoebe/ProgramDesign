import os
import cv2
import sys
import shutil
import random
import numpy as np
import matplotlib.pyplot as plt

"""
A Python class that implements the Eigenfaces algorithm
for face recognition, using eigenvalue decomposition and
principle component analysis.

We use the AT&T data set, with 60% of the images as train
and the rest 40% as a test set, including 85% of the energy.

Additionally, we use a small set of celebrity images to
find the best AT&T matches to them.

Algorithm Reference:
    http://docs.opencv.org/modules/contrib/doc/facerec/facerec_tutorial.html
"""
class Eigenfaces(object):
    
    # number of labels
    faces_count = 40
    # directory path to the AT&T faces
    faces_dir = '.'

    train_faces_count = 6
    test_faces_count = 4

    # training images count
    l = train_faces_count * faces_count
    # number of columns of the image
    m = 92                                   
    # number of rows of the image                                   
    n = 112
    # length of the column vector
    mn = m * n                                                                  

    """
    Initializing the Eigenfaces model.
    """
    def __init__(self, _faces_dir = '.', _energy = 0.85):
        print '> Initializing started'

        self.faces_dir = _faces_dir
        self.energy = _energy
        self.training_ids = []

        L = np.empty(shape=(self.mn, self.l), dtype='float64')

        cur_img = 0
        for face_id in xrange(1, self.faces_count + 1):

            training_ids = random.sample(range(1, 11), self.train_faces_count)
            self.training_ids.append(training_ids)

            for training_id in training_ids:
                path_to_img = os.path.join(self.faces_dir,
                        's' + str(face_id), str(training_id) + '.pgm')
                #print '> reading file: ' + path_to_img
                img = cv2.imread(path_to_img, 0)

                img_col = np.array(img, dtype='float64').flatten()

                L[:, cur_img] = img_col[:]
                cur_img += 1

        # get the mean of all images / over the rows of L
        self.mean_img_col = np.sum(L, axis=1) / self.l
        # subtract from all training images
        for j in xrange(0, self.l):                                             
            L[:, j] -= self.mean_img_col[:]

        """
        instead of computing the covariance matrix as
        L*L^T, we set C = L^T*L, and end up with way
        smaller and computentionally inexpensive one
        we also need to divide by the number of training
        images
        """
        C = np.matrix(L.transpose()) * np.matrix(L)                             
        C /= self.l                                                             
                                                                                

        """
        eigenvectors/values of the covariance matrix
        getting their correct order - decreasing
        puttin the evalues in that order
        same for the evectors
        """

        self.evalues, self.evectors = np.linalg.eig(C)                          
        sort_indices = self.evalues.argsort()[::-1]                             
        self.evalues = self.evalues[sort_indices]                               
        self.evectors = self.evectors[sort_indices]                             

        # include only the first k evectors/values so
        # that they include approx. 85% of the energy
        evalues_sum = sum(self.evalues[:])                                      
        evalues_count = 0                                                       
        evalues_energy = 0.0
        for evalue in self.evalues:
            evalues_count += 1
            evalues_energy += evalue / evalues_sum

            if evalues_energy >= self.energy:
                break

        # reduce the number of eigenvectors/values to consider
        self.evalues = self.evalues[0:evalues_count]                           
        self.evectors = self.evectors[0:evalues_count]
        """
        change eigenvectors from rows to columns
        left multiply to get the correct evectors
        find the norm of each eigenvector
        normalize all eigenvectors
        """
        self.evectors = self.evectors.transpose()                               
        self.evectors = L * self.evectors                                       
        norms = np.linalg.norm(self.evectors, axis=0)                          
        self.evectors = self.evectors / norms                                   

        self.W = self.evectors.transpose() * L                                  # computing the weights

        print '> Initializing ended'

    """
    Classify an image to one of the eigenfaces.
    """
    def classify(self, path_to_img):
        img = cv2.imread(path_to_img, 0)                                        # read as a grayscale image
        img_col = np.array(img, dtype='float64').flatten()                      # flatten the image
        img_col -= self.mean_img_col                                            # subract the mean column
        img_col = np.reshape(img_col, (self.mn, 1))                             # from row vector to col vector

        S = self.evectors.transpose() * img_col                                 # projecting the normalized probe onto the
                                                                                # Eigenspace, to find out the weights

        diff = self.W - S                                                       # finding the min ||W_j - S||
        norms = np.linalg.norm(diff, axis=0)

        closest_face_id = np.argmin(norms)                                      # the id [0..240) of the minerror face to the sample
        return (closest_face_id / self.train_faces_count) + 1                   # return the faceid (1..40)

    """
    Evaluate the model using the 4 test faces left
    from every different face in the AT&T set.
    """
    def evaluate(self):
        print '> Evaluating AT&T faces started'
        results_file = os.path.join('results', 'att_results.txt')               # filename for writing the evaluating results in
        f = open(results_file, 'w')                                             # the actual file

        test_count = self.test_faces_count * self.faces_count                   # number of all AT&T test images/faces
        test_correct = 0
        for face_id in xrange(1, self.faces_count + 1):
            for test_id in xrange(1, 11):
                if (test_id in self.training_ids[face_id-1]) == False:          # we skip the image if it is part of the training set
                    path_to_img = os.path.join(self.faces_dir,
                            's' + str(face_id), str(test_id) + '.pgm')          # relative path

                    result_id = self.classify(path_to_img)
                    result = (result_id == face_id)

                    if result == True:
                        test_correct += 1
                        f.write('image: %s\nresult: correct\n\n' % path_to_img)
                    else:
                        f.write('image: %s\nresult: wrong, got %2d\n\n' %
                                (path_to_img, result_id))

        print '> Evaluating AT&T faces ended'
        self.accuracy = float(100. * test_correct / test_count)
        print 'Correct: ' + str(self.accuracy) + '%'
        f.write('Correct: %.2f\n' % (self.accuracy))
        f.close()                                                               # closing the file

    """
    Evaluate the model for the small celebrity data set.
    Returning the top 5 matches within the AT&T set.
    Images should have the same size (92,112) and are
    located in the celebrity_dir folder.
    """
    def evaluate_celebrities(self, celebrity_dir='.'):
        print '> Evaluating celebrity matches started'
        # go through all the celebrity images in the folder
        for img_name in os.listdir(celebrity_dir):                              
            path_to_img = os.path.join(celebrity_dir, img_name)
            """
            # read as a grayscale image
            # flatten the image
            # subract the mean column
            # from row vector to col vector
            """
            img = cv2.imread(path_to_img, 0)                                    
            img_col = np.array(img, dtype='float64').flatten()                  
            img_col -= self.mean_img_col                                        
            img_col = np.reshape(img_col, (self.mn, 1))  
            """                       
            # projecting the normalized probe onto the
            # Eigenspace, to find out the weights
            """
            S = self.evectors.transpose() * img_col                             
                                                                                
            # finding the min ||W_j - S||
            diff = self.W - S                                                   
            norms = np.linalg.norm(diff, axis=0)
            # first five elements: indices of top 5 matches in AT&T set
            top5_ids = np.argpartition(norms, 5)[:5]                           


            # the image file name without extension
            # path to the respective results folder
            # make a results folder for the respective celebrity
            # the file with the similarity value and id's
            name_noext = os.path.splitext(img_name)[0]                          
            result_dir = os.path.join('results', name_noext)                    
            os.makedirs(result_dir)                                             
            result_file = os.path.join(result_dir, 'results.txt')               

            f = open(result_file, 'w')                                          # open the results file for writing
            for top_id in top5_ids:
                face_id = (top_id / self.train_faces_count) + 1                 # getting the face_id of one of the closest matches
                subface_id = self.training_ids[face_id-1][top_id % self.train_faces_count]           # getting the exact subimage from the face

                path_to_img = os.path.join(self.faces_dir,
                        's' + str(face_id), str(subface_id) + '.pgm')           # relative path to the top5 face

                shutil.copyfile(path_to_img,                                    # copy the top face from source
                        os.path.join(result_dir, str(top_id) + '.pgm'))         # to destination

                f.write('id: %3d, score: %.6f\n' % (top_id, norms[top_id]))     # write the id and its score to the results file

            f.close()
        print '> Evaluating celebrity matches ended'



if __name__ == "__main__":
    ATT_DIR  = ".\\att_faces"
    CELE_DIR = ".\\celebrity_faces"

    if not os.path.exists('results'):
        os.makedirs('results')
    else:
        shutil.rmtree('results')
        os.makedirs('results')

    efaces = Eigenfaces(str(ATT_DIR), _energy=0.9)                                      
    efaces.evaluate()
                                                
    # if we have third argument (celebrity folder)
    efaces.evaluate_celebrities(str(CELE_DIR))

