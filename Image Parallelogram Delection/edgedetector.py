import cv2                         
import numpy as np
import matplotlib.pyplot as plt    #Used for plotting
import matplotlib.image as mpimg   #Used for image read
from scipy.ndimage.filters import convolve
import operation


def sobel(image_gray, thresholdVotes):
    #sobelx = cv2.Sobel(image_gray,cv2.CV_64F,1,0,ksize=3)  # x
    #sobely = cv2.Sobel(image_gray,cv2.CV_64F,0,1,ksize=3)  # y

    sobelx = operation.convolve(image_gray,np.array([[-1,0,1],[-2,0,2],[-1,0,1]]))
    sobely = operation.convolve(image_gray,np.array([[1,2,1],[0,0,0],[-1,-2,-1]]))

    img = np.round(np.power(np.power(sobelx, 2.0) + np.power(sobely, 2.0), 0.5)).astype(int)
    # img = cv2.Laplacian(image_gray, cv2.CV_64F)
    lenx, leny = img.shape

    num = 0
    for i in range(lenx):
        for j in range(leny):
            if img[i, j] > thresholdVotes:
                img[i, j] = 255
                num += 1
            else:
                img[i, j] = 0
    print(num)
    return img


 
def CannyEdgeDetector(im, lowThreshold = 31, highThreshold = 91):
    im = np.array(im, dtype=float) #Convert to float to prevent clipping values
 
    #Use sobel filters to get horizontal and vertical gradients
    #im3h = convolve(im,[[-1,0,1],[-2,0,2],[-1,0,1]]) 
    #im3v = convolve(im,[[1,2,1],[0,0,0],[-1,-2,-1]])
    im3h = operation.convolve(im,np.array([[-1,0,1],[-2,0,2],[-1,0,1]]))
    im3v = operation.convolve(im,np.array([[1,2,1],[0,0,0],[-1,-2,-1]]))

    #Get gradient and direction
    grad = np.power(np.power(im3h, 2.0) + np.power(im3v, 2.0), 0.5)
    theta = np.arctan2(im3v, im3h)
    thetaQ = (np.round(theta * (5.0 / np.pi)) + 5) % 5
 
    #Non-maximum suppression
    gradSup = grad.copy()
    for r in range(im.shape[0]):
        for c in range(im.shape[1]):
            #Suppress pixels at the image edge
            if r == 0 or r == im.shape[0]-1 or c == 0 or c == im.shape[1] - 1:
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
    for r in range(1, im.shape[0]-1):
        for c in range(1, im.shape[1]-1):    
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
 
    return grad, finalEdges