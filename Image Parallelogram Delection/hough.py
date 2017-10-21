import matplotlib.pyplot as plt
import numpy as np
import scipy.signal as sp
import operation

def houghLines(edged,rho_step,theta_step,thresholdVotes,filterMultiple,thresholdPixels=0):
    rows, columns = edged.shape
    theta = np.linspace(-90.0, 0.0, np.ceil(90.0/theta_step) + 1.0)
    theta = np.concatenate((theta, -theta[len(theta)-2::-1]))
    theta = theta*np.pi/180.0
   
    diagonal = np.sqrt((rows - 1)**2 + (columns - 1)**2)
    q = np.ceil(diagonal/rho_step)
    nrho = 2*q + 1
    rho = np.linspace(-q*rho_step, q*rho_step, nrho) 
    # defining empty Matrix in Hough space, where x is for theta and y is x*cos(theta)+y*sin(theta)
    houghMatrix = np.zeros((len(rho), len(theta)))
    
    # Here we populate houghMatrix
    y_idxs, x_idxs = np.nonzero(edged > thresholdPixels)  # (row, col) indexes to edges
    cos_t = np.cos(theta)
    sin_t = np.sin(theta)
    for i in range(len(x_idxs)):
        colId = x_idxs[i]
        rowId = y_idxs[i]
        for thId in range(len(theta)):
            rhoVal = colId*cos_t[thId] + rowId*sin_t[thId]
            diff = np.abs(rho-rhoVal)
            rhoIdx = np.nonzero(diff == np.min(diff))[0]            
            houghMatrix[rhoIdx[0], thId] += 1  
            
   
    # cluster and filter multiple dots in Houghs plane
    if filterMultiple > 0:
        clusterDiameter = filterMultiple
        values = np.transpose(np.array(np.nonzero(houghMatrix>thresholdVotes)))
        filterTable={}
        totalArray=[]
        for i in range (0, len(values)):
            if i in filterTable:
                continue
            tempArray=[i]
            for j in range (i+1, len(values)):
                if j in filterTable:
                    continue
                for k in range (0, len(tempArray)):
                    if operation.getLength(values[tempArray[k]],values[j])<clusterDiameter:
                        filterTable[j] = 1
                        tempArray.append(j)
                        break
            totalArray.append(tempArray)
        
    # leave the highest value in each cluster
    for i in range(len(totalArray)):
        ii = i
        jj = 0
        highest = houghMatrix[values[totalArray[i][0]][0],values[totalArray[i][0]][1]]
        for j in range(1, len(totalArray[i])):
            if houghMatrix[values[totalArray[i][j]][0],values[totalArray[i][j]][1]] > highest:
                highest = houghMatrix[values[totalArray[i][j]][0],values[totalArray[i][j]][1]]
                houghMatrix[values[totalArray[ii][jj]][0],values[totalArray[ii][jj]][1]] = 0
                ii = i
                jj = j
            else:
                houghMatrix[values[totalArray[i][j]][0],values[totalArray[i][j]][1]] = 0
        
    return (np.where(houghMatrix>thresholdVotes)[0]-q)*rho_step, theta[np.where(houghMatrix>thresholdVotes)[1]]
    

    
def plotHoughLines(rho,theta,image):
  
    a = np.cos(theta)
    b = np.sin(theta)
    x0 = a*rho
    y0 = b*rho

    fig2, ax1 = plt.subplots(ncols=1, nrows=1)
    ax1.imshow(image)
    
    for i in range (0, len(rho)):   
        ax1.plot( [x0[i] + 1000*(-b[i]), x0[i] - 1000*(-b[i])],
                  [y0[i] + 1000*(a[i]), y0[i] - 1000*(a[i])], 
                  'xb-',linewidth=3)
    
    ax1.set_ylim([image.shape[0],0])
    ax1.set_xlim([0,image.shape[1]])
    
    plt.show()
    

    

