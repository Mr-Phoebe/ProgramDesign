import os
import cv2
import sys
import shutil
import random
import numpy as np
import matplotlib.pyplot as plt


class Eigenfaces(object):
    
    # number of labels
    faces_count = 8
    # directory path to the AT&T faces
    faces_dir = '.'

    train_faces_count = 1
    test_faces_count = 1
    face_train_ids = [1, 2, 3, 7, 10, 11, 14, 15]

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
        print '> Initializing started'

        self.faces_dir = _faces_dir
        self.threshold = _threshold
        self.training_ids = []

        L = np.empty(shape=(self.mn, self.l), dtype='float64')
        cur_img = 0

        for face_id in self.face_train_ids:
            training_ids = [1]
            self.training_ids.append(training_ids)
            for training_id in training_ids:
                path_to_img = os.path.join(self.faces_dir,
                        's' + str(face_id), str(training_id) + '.jpg')
                #print '> reading file: ' + path_to_img
                img = cv2.imread(path_to_img, 0)
                img_col = np.array(img, dtype='float64').flatten()
                L[:, cur_img] = img_col[:]
                cur_img += 1
        # get the mean of all images / over the rows of L
        self.mean_img_col = np.mean(L, axis=1)

        """
        # output the mean image
        fig, ax1 =  plt.subplots(ncols=1, nrows=1, figsize=(4, 4))
        ax1.set_axis_off()
        tmp = np.reshape(self.mean_img_col, (self.n, self.m))
        ax1.imshow(tmp, cmap="bone")
        fig.savefig("image/mean.jpg")
        """

        # subtract from all training images
        for j in xrange(0, self.l):                                             
            L[:, j] -= self.mean_img_col[:]

        """
        print(L.shape)
        for j in range(len(self.face_train_ids)):
            fig, ax1 = plt.subplots(ncols=1, nrows=1, figsize=(4, 4))
            ax1.set_axis_off()
            tmp = np.reshape(L[:, j], (self.n, self.m))
            ax1.imshow(tmp, cmap="bone")
            fig.savefig("image/train_"+str(self.face_train_ids[j])+".jpg")
        """

        """
        Because L's columns represent the image vector,
        we set C = L^T*L
        """
        C = np.matrix(L.transpose()) * np.matrix(L)      
        C /= L.shape[1]                       
        
        """
        Eigenvectors/values of the covariance matrix.
        And set them into decreasing order of values.
        """
        self.evalues, self.evectors = np.linalg.eig(C)
        sort_indices = self.evalues.argsort()[::-1]
        self.evalues = self.evalues[sort_indices]
        self.evectors = self.evectors[:, sort_indices]

        """
        include only the first k evectors/values so
        that they include approx.
        evalues_count = 0
        evalues_sum = sum(self.evalues[:])        
        evalues_radio = 0.0
        for evalue in self.evalues:
            evalues_count += 1
            evalues_radio += evalue / evalues_sum

            if evalues_radio >= self.threshold:
                break
        """
        evalues_count = 5
        # truncate the number of eigenvectors/values to consider
        self.evalues = self.evalues[0:evalues_count]                         
        self.evectors = self.evectors[:, 0:evalues_count]

        """
        change eigenvectors from rows to columns
        left multiply to get the correct evectors
        find the norm of each eigenvector
        normalize all eigenvectors
        """                             
        self.evectors = L * self.evectors
        norms = np.linalg.norm(self.evectors, axis=0)
        self.evectors = self.evectors / norms

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
        self.W = self.evectors.transpose() * L
        print '> Initializing ended'

    """
    Classify an image to one of the eigenfaces.
    """
    def classify(self, path_to_img):
        img = cv2.imread(path_to_img, 0)
        img_col = np.array(img, dtype='float64').flatten()
        img_col -= self.mean_img_col
        img_col = np.reshape(img_col, (self.mn, 1))                             # from row vector to col vector

        S = self.evectors.transpose() * img_col                                 
        """
        projecting the normalized probe onto the
        Eigenspace, to find out the weights
        """
        diff = self.W - S                                                       # finding the min ||W_j - S||
        norms = np.linalg.norm(diff, axis=0)

        closest_face_id = np.argmin(norms)                                      # the id [0..240) of the minerror face to the sample
        return self.face_train_ids[(closest_face_id / self.train_faces_count)]

    """
    Evaluate the model using the 4 test faces left
    from every different face in the AT&T set.
    """
    def validate(self):
        print '> Evaluating faces started'
        results_file = os.path.join('results', 'results.txt')               # filename for writing the evaluating results in
        f = open(results_file, 'w')                                             # the actual file

        test_count = self.test_faces_count * self.faces_count                   # number of all AT&T test images/faces
        test_correct = 0
        for face_id in self.face_train_ids:
            for test_id in xrange(1, self.test_faces_count+1):
                # if (test_id in self.training_ids[face_id-1]) == False:          # we skip the image if it is part of the training set
                path_to_img = os.path.join(self.faces_dir,
                        's' + str(face_id), str(test_id) + '.jpg')          # relative path

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

    """
    Evaluate the model for the small celebrity data set.
    Returning the top 5 matches within the AT&T set.
    Images should have the same size (92,112) and are
    located in the celebrity_dir folder.
    """
    def evaluate(self, celebrity_dir='.'):
        print '> Evaluating test data set matches started'
        # go through all the celebrity images in the folder
        flag = -1.0
        for img_name in os.listdir(celebrity_dir):                              
            path_to_img = os.path.join(celebrity_dir, img_name)
            name_noext = os.path.splitext(img_name)[0]
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
                                                                     
            reconsturction = self.evectors * S 
            """
            # output the reconstruction image
            # and the origin image subtracts the mean image
            print(S.shape)
            print(self.W.shape)

            fig, ax1 = plt.subplots(ncols=1, nrows=1, figsize=(4, 4))
            ax1.set_axis_off()            
            tmp = np.reshape(reconsturction, (self.n, self.m))
            #tmp = np.reshape(img_col, (self.n, self.m))
            ax1.imshow(tmp, cmap="bone")
            fig.savefig("image/"+name_noext+".jpg")
            """

            diff = reconsturction - img_col
            dis0 = np.linalg.norm(diff, ord=1)            
            
            if flag < 0:
                flag = dis0
            
            if dis0 >= flag:
                #print(dis0)
                result_dir = 'results' #os.path.join('results', name_noext)
                # os.makedirs(result_dir)                                             
                result_file = os.path.join(result_dir, 'results_no_face_' + name_noext + '.txt')    
                f = open(result_file, 'w')                 
                f.write('Not a face')
                continue
                       
            # finding the min ||W_j - S||
            diff = self.W - S                                                   
            norms = np.linalg.norm(diff, axis=0, ord=1)
            mean_dis = np.mean(norms)
            top_ids = [np.argmin(norms)]#np.argpartition(norms, 1)[:1]

            # the image file name without extension
            # path to the respective results folder
            # make a results folder for the respective celebrity
            # the file with the similarity value and id's
            name_noext = os.path.splitext(img_name)[0]
            result_dir = 'results' #os.path.join('results', name_noext)
            # os.makedirs(result_dir)                                             
            result_file = os.path.join(result_dir, 'results_' + name_noext + '.txt')               

            f = open(result_file, 'w')                                          # open the results file for writing

            for top_id in top_ids:
                if norms[top_id] < 13988:
                    face_id = (top_id / self.train_faces_count) + 1                 # getting the face_id of one of the closest matches
                    subface_id = self.training_ids[face_id-1][top_id % self.train_faces_count]           # getting the exact subimage from the face
                    face_idx = self.face_train_ids[face_id-1]
                    path_to_img = os.path.join(self.faces_dir,
                            's' + str(face_idx), str(subface_id) + '.jpg')           # relative path to the top5 face
        
                    shutil.copyfile(path_to_img,                                    # copy the top face from source
                            os.path.join(result_dir, 'results_' + name_noext + '.jpg'))         # to destination

                    f.write('id: %3d, score: %.6f\n' % (top_id, norms[top_id]))     # write the id and its score to the results file
                else:
                    f.write("Unkown Face")
                    #print(name_noext, norms[top_id], mean_dis)
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

