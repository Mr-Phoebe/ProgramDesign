import matplotlib.pyplot as plt
import numpy as np
import scipy.signal as sp
import operation

def houghLines(edged,rho_res,theta_res,thresholdVotes,filterMultiple,thresholdPixels=0):
    
    rows, columns = edged.shape
    theta = np.linspace(-90.0, 0.0, np.ceil(90.0/theta_res) + 1.0)
    theta = np.concatenate((theta, -theta[len(theta)-2::-1]))
    
    #defining empty Matrix in Hough space, where x is for theta and y is x*cos(theta)+y*sin(theta)
    diagonal = np.sqrt((rows - 1)**2 + (columns - 1)**2)
    q = np.ceil(diagonal/rho_res)
    nrho = 2*q + 1
    rho = np.linspace(-q*rho_res, q*rho_res, nrho)
    houghMatrix = np.zeros((len(rho), len(theta)))
    
    #Here we populate houghMatrix
    for rowId in range(rows):                               
        for colId in range(columns):               
          if edged[rowId, colId]>thresholdPixels:           #edged has values 0 or 255 in our case
            #for each theta we calculate rhoVal, then locate it in Hough space plane
            for thId in range(len(theta)):
              rhoVal = colId*np.cos(theta[thId]*np.pi/180.0) + \
                  rowId*np.sin(theta[thId]*np.pi/180)
              rhoIdx = np.nonzero(np.abs(rho-rhoVal) == np.min(np.abs(rho-rhoVal)))[0]
              houghMatrix[rhoIdx[0], thId] += 1  
            
   
   #cluster and filter multiple dots in Houghs plane
    if filterMultiple>0:
        clusterDiameter=filterMultiple
        values=np.transpose(np.array(np.nonzero(houghMatrix>thresholdVotes)))
        filterArray=[]
        filterArray.append(0)
        totalArray=[]
        for i in range (0, len(values)):
            if i in filterArray[1::]:
                continue
            tempArray=[i]
            for j in range (i+1, len(values)):
                if j in filterArray[1::]:
                    continue
                for k in range (0, len(tempArray)):
                    if operation.getLength(values[tempArray[k]],values[j])<clusterDiameter:
                        filterArray.append(j)
                        tempArray.append(j)
                        break
            totalArray.append(tempArray)
        
        #leave the highest value in each cluster
        for i in range (0, len(totalArray)):
             for j in range (0, len(totalArray[i])):
                 if j==0:
                     highest=houghMatrix[values[totalArray[i][j]][0],values[totalArray[i][j]][1]]
                     ii=i
                     jj=j
                 else:
                     if houghMatrix[values[totalArray[i][j]][0],values[totalArray[i][j]][1]]>=highest:
                         highest=houghMatrix[values[totalArray[i][j]][0],values[totalArray[i][j]][1]]
                         houghMatrix[values[totalArray[ii][jj]][0],values[totalArray[ii][jj]][1]]=0
                         ii=i
                         jj=j
                     else:
                         houghMatrix[values[totalArray[i][j]][0],values[totalArray[i][j]][1]]=0
                    
    return (np.where(houghMatrix>thresholdVotes)[0]-q)*rho_res, theta[np.where(houghMatrix>thresholdVotes)[1]]*np.pi/180.0
    

    
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
    

    

