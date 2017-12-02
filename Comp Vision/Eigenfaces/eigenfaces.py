# -*- coding: utf-8 -*-
# @Author: Haonan Wu
# @Date:   2017-12-02 13:36:23
# @Last Modified by:   Haonan Wu
# @Last Modified time: 2017-12-02 14:06:09

import os
import cv2
import sys
import shutil
import random
import numpy as np
import matplotlib.pyplot as plt

"""
Algorithm Reference:
    http://docs.opencv.org/modules/contrib/doc/facerec/facerec_tutorial.html
"""
class Eigenfaces(object):
    
    # number of labels
    faces_count = 9
    faces_dir = '.'

    train_faces_count = 1
    test_faces_count = 1
    face_train_ids = [1, 2, 3, 7, 10, 11, 12, 14, 15]

    # training images count
    l = train_faces_count * faces_count
    # number of columns of the image
    m = 195                                   
    # number of rows of the image                                   
    n = 231
    # length of the column vector
    mn = m * n                                                                  

    """
    Initializing the Eigenfaces model.
    """
    def __init__(self, _faces_dir = '.', _threshold = 0.85):
        print '> Training started'

        self.faces_dir = _faces_dir
        self.threshold = _threshold
        self.training_ids = []

        L = np.empty(shape=(self.l, self.mn), dtype='float64')
        cur_img = 0

        for face_id in self.face_train_ids:
            training_ids = [1]
            self.training_ids.append(training_ids)
            for training_id in training_ids:
                path_to_img = os.path.join(self.faces_dir,
                        's' + str(face_id), str(training_id) + '.jpg')
                img = cv2.imread(path_to_img, 0)
                img_row = np.array(img, dtype='float64').flatten()
                L[cur_img] = img_row
                cur_img += 1

        """
        get the mean of all images / over the rows of L
        subtract from all training images
        """
        self.mean_img_row = np.mean(L, axis=0)


        # output the mean image
        fig, ax1 = plt.subplots(frameon=False)
        ax1.set_axis_off()
        tmp = np.reshape(self.mean_img_row, (self.n, self.m))
        ax1.imshow(tmp, cmap="bone")
        fig.savefig("image/mean.jpg", bbox_inches='tight', pad_inches=0)
                              
        L -= self.mean_img_row
        """
        print(L.shape)
        for j in range(len(self.face_train_ids)):
            fig, ax1 = plt.subplots(ncols=1, nrows=1, figsize=(4, 4))
            ax1.set_axis_off()
            tmp = np.reshape(L[j], (self.n, self.m))
            ax1.imshow(tmp, cmap="bone")
            fig.savefig("image/train_"+str(self.face_train_ids[j])+".jpg")
        """
        C = np.matrix(L) * np.matrix(L.transpose())                            
        C /= L.shape[0]


        """
        Eigenvectors/values of the covariance matrix.
        And set them into decreasing order of values.
        """

        self.evalues, self.evectors = np.linalg.eig(C)
        sort_indices = self.evalues.argsort()[::-1]
        self.evalues = self.evalues[sort_indices]
        self.evectors = self.evectors[sort_indices]

        """
        include only the first k evectors/values so
        that they include approx.
        """
        evalues_sum = sum(self.evalues[:])
        evalues_count = 0
        evalues_radio = 0.0
        for evalue in self.evalues:
            evalues_count += 1
            evalues_radio += evalue / evalues_sum

            if evalues_radio >= self.threshold:
                break

        # truncate the number of eigenvectors/values to consider
        self.evalues = self.evalues[0:evalues_count]                           
        self.evectors = self.evectors[0:evalues_count]

        """
        change eigenvectors from rows to columns
        left multiply to get the correct evectors
        find the norm of each eigenvector
        normalize all eigenvectors
        """                         
        self.evectors = self.evectors * L
        norms = np.linalg.norm(self.evectors, axis=1)                  
        self.evectors = self.evectors.transpose() / norms
        """
        # output the eigen face
        print(self.evectors.shape)
        for j in range(self.evectors.shape[1]):
            fig, ax1 = plt.subplots(ncols=1, nrows=1, figsize=(4, 4))
            ax1.set_axis_off()
            tmp = np.reshape(self.evectors[:, j], (self.n, self.m))
            ax1.imshow(tmp, cmap="bone")
            fig.savefig("image/"+str(j)+".jpg")
        """
        self.W = L * self.evectors

        print '> Training ended'

    """
    Classify an image to one of the eigenfaces.
    """
    def classify(self, path_to_img):
        img = cv2.imread(path_to_img, 0)
        img_row = np.array(img, dtype='float64').flatten()
        img_row -= self.mean_img_row
        

        S =  img_row * self.evectors

        """
        projecting the normalized probe onto the
        Eigenspace, to find out the weights
        """
        diff = self.W - S                                                       # finding the min ||W_j - S||
        norms = np.linalg.norm(diff, axis=0)

        closest_face_id = np.argmin(norms)                                      # the id [0..240) of the minerror face to the sample
        return self.face_train_ids[(closest_face_id / self.train_faces_count)]

    def validate(self):
        print '> Evaluating faces started'
        results_file = os.path.join('results', 'results.txt')
        f = open(results_file, 'w')

        test_count = self.test_faces_count * self.faces_count
        test_correct = 0
        for face_id in self.face_train_ids:
            for test_id in xrange(1, self.test_faces_count+1):
                path_to_img = os.path.join(self.faces_dir,
                        's' + str(face_id), str(test_id) + '.jpg')

                result_id = self.classify(path_to_img)
                result = (result_id == face_id)

                if result == True:
                    test_correct += 1
                    f.write('image: %s\nresult: correct, got %2d\n\n' % (path_to_img, result_id))
                else:
                    f.write('image: %s\nresult: wrong, got %2d\n\n' %
                            (path_to_img, result_id))

        print '> Evaluating faces ended'
        self.accuracy = float(100. * test_correct / test_count)
        print 'Correct: ' + str(self.accuracy) + '%'
        f.write('Correct: %.2f\n' % (self.accuracy))
        f.close()                                                               # closing the file


    def evaluate(self, celebrity_dir='.'):
        print '> Evaluating test data set matches started'
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
            img_row = np.array(img, dtype='float64').flatten()                  
            img_row -= self.mean_img_row
                                        
            """                       
            # projecting the normalized probe onto the
            # Eigenspace, to find out the weights
            """
            S = img_row * self.evectors
                                                                                
            # finding the min ||W_j - S||
            diff = self.W - S                                                   
            norms = np.linalg.norm(diff, axis=1)                      
            top_ids = np.argpartition(norms, 1)[:1]

            """
            the image file name without extension
            path to the respective results folder
            make a results folder for the respective celebrity
            the file with the similarity value and id's
            """
            name_noext = os.path.splitext(img_name)[0]
            result_dir = 'results' #os.path.join('results', name_noext)
            # os.makedirs(result_dir)                                             
            result_file = os.path.join(result_dir, 'results_' + name_noext + '.txt')               

            """
            # output the reconstruction image
            # and the origin image subtracts the mean image
            print(S.shape)
            print(self.W.shape)

            fig, ax1 = plt.subplots(ncols=1, nrows=1, figsize=(4, 4))
            ax1.set_axis_off()            
            tmp = S * self.evectors.transpose() + self.mean_img_row
            tmp = np.reshape(tmp, (self.n, self.m))
            #tmp = np.reshape(img_row, (self.n, self.m))
            ax1.imshow(tmp, cmap="bone")
            fig.savefig("image/"+name_noext+".jpg")
            """
            f = open(result_file, 'w')

            for top_id in top_ids:
                # getting the face_id of one of the closest matches
                face_id = (top_id / self.train_faces_count) + 1
                # getting the exact subimage from the face
                subface_id = self.training_ids[face_id-1][top_id % self.train_faces_count]
                face_idx = self.face_train_ids[face_id-1]
                path_to_img = os.path.join(self.faces_dir,
                        's' + str(face_idx), str(subface_id) + '.jpg')           # relative path to the top5 face

                #shutil.copyfile(path_to_img,                                    # copy the top face from source
                #        os.path.join(result_dir, str(top_id) + '_' + str(face_idx) + '.jpg'))         # to destination                
                shutil.copyfile(path_to_img,                                    
                        os.path.join(result_dir, 'results_' + name_noext + '.jpg'))

                f.write('id: %3d, score: %.6f\n' % (top_id, norms[top_id]))     # write the id and its score to the results file
            f.close()
        print '> Evaluating test data set matches ended'



if __name__ == "__main__":
    TRAIN_DATA_DIR  = ".\\train_data"
    TEST_DATA_DIR = ".\\test_data"

    if not os.path.exists('results'):
        os.makedirs('results')
    else:
        shutil.rmtree('results')
        os.makedirs('results')

    efaces = Eigenfaces(str(TRAIN_DATA_DIR), _threshold=0.7)                                      
    #efaces.validate()
                                                
    # if we have third argument (celebrity folder)
    efaces.evaluate(str(TEST_DATA_DIR))

