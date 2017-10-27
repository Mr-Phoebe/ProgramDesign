import matplotlib.pyplot as plt
import numpy as np
import operation
import math
    
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
    #print(len(x_idxs))
    print("take ", len(x_idxs)*len(theta)*int(math.log(len(rho), 2)))
    cos_t = np.cos(theta)
    sin_t = np.sin(theta)
    for i in range(len(x_idxs)):
        colId = x_idxs[i]
        rowId = y_idxs[i]
        for thId in range(len(theta)):
            rhoVal = colId*cos_t[thId] + rowId*sin_t[thId]
            rhoId = np.searchsorted(rho, rhoVal)
            if rhoId != 0 and rho[rhoId] + rho[rhoId-1] > rhoVal*2:
                rhoId -= 1
            houghMatrix[rhoId, thId] += 1  

    # cluster and filter multiple dots in Houghs plane
    if filterMultiple > 0:
        clusterDiameter = filterMultiple
        lineValue = np.transpose(np.array(np.nonzero(houghMatrix>thresholdVotes)))
        filterTable = {}
        totalArray = []
        print(len(lineValue))
        for i in range(len(lineValue)):
            if i in filterTable:
                continue
            tempArray = [i]
            for j in range (i+1, len(lineValue)):
                if j in filterTable:
                    continue
                for k in range(len(tempArray)):
                    if operation.getLength(lineValue[tempArray[k]],lineValue[j])<clusterDiameter:
                        filterTable[j] = 1
                        tempArray.append(j)
                        break
            totalArray.append(tempArray)
        
        # leave the highest value in each cluster
        for i in range(len(totalArray)):
            ii = i
            jj = 0
            highest = houghMatrix[lineValue[totalArray[i][0]][0],lineValue[totalArray[i][0]][1]]
            for j in range(1, len(totalArray[i])):
                if houghMatrix[lineValue[totalArray[i][j]][0],lineValue[totalArray[i][j]][1]] > highest:
                    highest = houghMatrix[lineValue[totalArray[i][j]][0],lineValue[totalArray[i][j]][1]]
                    houghMatrix[lineValue[totalArray[ii][jj]][0],lineValue[totalArray[ii][jj]][1]] = 0
                    ii = i
                    jj = j
                else:
                    houghMatrix[lineValue[totalArray[i][j]][0],lineValue[totalArray[i][j]][1]] = 0
        
    return (np.where(houghMatrix>thresholdVotes)[0]-q)*rho_step, theta[np.where(houghMatrix>thresholdVotes)[1]]
    

    
def plotHoughLines(rho,theta,image):
  
    a = np.cos(theta)
    b = np.sin(theta)
    x0 = a*rho
    y0 = b*rho

    fig2, ax1 = plt.subplots(ncols=1, nrows=1)
    ax1.imshow(image)
    
    for i in range(len(rho)):   
        ax1.plot( [x0[i] + 1000*(-b[i]), x0[i] - 1000*(-b[i])],
                  [y0[i] + 1000*(a[i]), y0[i] - 1000*(a[i])], 
                  'xb-',linewidth=3)
    
    ax1.set_ylim([image.shape[0],0])
    ax1.set_xlim([0,image.shape[1]])
    
    plt.show()
    

    

