import cv2                         
import numpy as np
import matplotlib.pyplot as plt    #Used for plotting
import matplotlib.image as mpimg   #Used for image read
import operation


def sobel(image_gray, thresholdVotes):
    #sobelx = cv2.Sobel(image_gray,cv2.CV_64F,1,0,ksize=3)  # x
    #sobely = cv2.Sobel(image_gray,cv2.CV_64F,0,1,ksize=3)  # y

    sobelx = operation.convolve(image_gray,np.array([[-1,0,1],[-2,0,2],[-1,0,1]]))
    sobely = operation.convolve(image_gray,np.array([[1,2,1],[0,0,0],[-1,-2,-1]]))

    img = np.round(np.power(np.power(sobelx, 2.0) + np.power(sobely, 2.0), 0.5)).astype(int)
    lenx, leny = img.shape

    for i in range(lenx):
        for j in range(leny):
            if img[i, j] > thresholdVotes:
                img[i, j] = 255
            else:
                img[i, j] = 0
    return img


 
def CannyEdgeDetector(img, lowThreshold = 31, highThreshold = 91):
    img = np.array(img, dtype=float) #Convert to float to prevent clipping values
 
    #Use sobel operators to get horizontal and vertical gradients
    #from scipy.ndimage.filters import convolve
    #sobelx = convolve(img,[[-1,0,1],[-2,0,2],[-1,0,1]]) 
    #sobely = convolve(img,[[1,2,1],[0,0,0],[-1,-2,-1]])
    sobelx = operation.convolve(img,np.array([[-1,0,1],[-2,0,2],[-1,0,1]]))
    sobely = operation.convolve(img,np.array([[1,2,1],[0,0,0],[-1,-2,-1]]))

    #Get gradient and direction
    grad = np.power(np.power(sobelx, 2.0) + np.power(sobely, 2.0), 0.5)
    theta = np.arctan2(sobely, sobelx)
    #thetaQ = (np.round(theta * (4.0 / np.pi)) + 4) % 4
    thetaQ = (np.round(theta * (5.0 / np.pi)) + 5) % 5

    #Non-maximum suppression
    lenx, leny = img.shape
    gradSup = grad.copy()
    for r in range(lenx):
        for c in range(leny):
            #Suppress pixels at the image edge
            if r == 0 or r == lenx-1 or c == 0 or c == leny - 1:
                gradSup[r, c] = 0
                continue
            tq = thetaQ[r, c] % 4
 
            if tq == 0:
                if grad[r, c] <= grad[r, c-1] or grad[r, c] <= grad[r, c+1]:
                    gradSup[r, c] = 0
            elif tq == 1:
                if grad[r, c] <= grad[r-1, c+1] or grad[r, c] <= grad[r+1, c-1]:
                    gradSup[r, c] = 0
            elif tq == 2:
                if grad[r, c] <= grad[r-1, c] or grad[r, c] <= grad[r+1, c]:
                    gradSup[r, c] = 0
            elif tq == 3:
                if grad[r, c] <= grad[r-1, c-1] or grad[r, c] <= grad[r+1, c+1]:
                    gradSup[r, c] = 0
 
    #Double threshold
    strongEdges = (gradSup > highThreshold)
 
    #Strong has value 2, weak has value 1
    thresholdedEdges = np.array(strongEdges, dtype=np.uint8) + (gradSup > lowThreshold)
 
    #Tracing edges with hysteresis    
    #Find weak edge pixels near strong edge pixels
    finalEdges = strongEdges.copy()
    currentPixels = []
    for r in range(1, lenx-1):
        for c in range(1, leny-1):    
            if thresholdedEdges[r, c] != 1:
                continue #Not a weak pixel
 
            #Get 3x3 patch    
            localPatch = thresholdedEdges[r-1:r+2,c-1:c+2]
            patchMax = localPatch.max()
            if patchMax == 2:
                currentPixels.append((r, c))
                finalEdges[r, c] = 1
 
    #Extend strong edges based on current pixels
    while len(currentPixels) > 0:
        newPix = []
        for r, c in currentPixels:
            for dr in range(-1, 2):
                for dc in range(-1, 2):
                    if dr == 0 and dc == 0: continue
                    r2 = r+dr
                    c2 = c+dc
                    if thresholdedEdges[r2, c2] == 1 and finalEdges[r2, c2] == 0:
                        #Copy this weak pixel to final result
                        newPix.append((r2, c2))
                        finalEdges[r2, c2] = 1
        currentPixels = newPix
 
    gradthr = grad
    lenx, leny = gradthr.shape
    for i in range(lenx):
        for j in range(leny):
            if gradthr[i, j] > lowThreshold:
                gradthr[i, j] = 255
            else:
                gradthr[i, j] = 0
    return gradthr, finalEdges