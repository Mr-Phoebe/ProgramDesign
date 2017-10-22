import time
begintime = time.clock()
starttime = time.clock()

import matplotlib.pyplot as plt    #Used for plotting
import matplotlib.image as mpimg   #Used for image read
import cv2                         #Used for Canny only!
import numpy as np                 #Basic calculations library

import hough
import operation
import blur

endtime = time.clock()
print "import %f\n" % (endtime - starttime)
starttime = endtime

image_rgb = mpimg.imread('parallelograms/test9.jpg')    #Reading image to array
image_gray = operation.rgb2gray(image_rgb)               #Converting rgb to gray

# image_gray = blur.gaussianblur(image_gray)               #Smooth the image using Gaussian Filter
# image_gray = blur.blurImage(image_gray)                 #Smooth the image using Mean Filter
image_gray = cv2.blur(image_gray,(5,5),0)

endtime = time.clock()
print "blur %f\n" % (endtime - starttime)
starttime = endtime

##Save smoothed picture to jpg
fig, ax1 = plt.subplots(ncols=1, nrows=1, figsize=(8, 4))
ax1.set_axis_off()
ax1.imshow(image_gray, cmap="bone")
fig.savefig("tmp/smooth.jpg")

edged = cv2.Canny(image_gray, 30, 100)                   #Finding edges, This is the only place we use OpenCV


# Sometimes images have unnecessary lines at the edges and we don't whant to find them

## Zero out the border 5px
borderLen = 5                         #The width to zero out the borders, counted in pixels
lenx, leny = edged.shape
edged[0:borderLen,0:leny] = 0
edged[lenx-borderLen:lenx,0:leny] = 0
edged[0:lenx,0:borderLen] = 0
edged[0:lenx,leny-borderLen:leny] = 0

# plt.imshow(edged)                     #Take a look at the edged picture

##Save edged picture to jpg
fig, ax1 = plt.subplots(ncols=1, nrows=1, figsize=(8, 4))
ax1.set_axis_off()
ax1.imshow(edged, cmap="bone")
fig.savefig("tmp/parallelograms_edged.jpg")


endtime = time.clock()
print "edge %f\n" % (endtime - starttime)
starttime = endtime

rho,theta = hough.houghLines(edged,
                                       rho_step=1,
                                       theta_step=1,
                                       thresholdVotes=30,
                                       filterMultiple=3,
                                       thresholdPixels=0)
                              

hough.plotHoughLines(rho,theta,image_rgb)

endtime = time.clock()
print "hough %f\n" % (endtime - starttime)
starttime = endtime

##Parameters for finding parallel lines
difference = np.pi/90
differenceRho = 2

#find parallel pairs
accumParallel=[]
for i in range (0, len(theta)):
    for j in range (i+1, len(theta)):
        if abs(theta[i] - theta[j]) < difference and abs(rho[i] - rho[j]) > differenceRho:
            accumParallel.append([i,j])


print("accumParallel", len(accumParallel))

fourLines = []

#find perpendicular pairs for parallel pairs
for i in range(len(accumParallel)):
    for j in range(i+1, len(accumParallel)):
        if (abs(theta[accumParallel[j][0]] - theta[accumParallel[i][0]]) > 10*difference) \
            and (abs(theta[accumParallel[j][0]] - theta[accumParallel[i][1]]) > 10*difference) \
            and (abs(theta[accumParallel[j][1]] - theta[accumParallel[i][0]]) > 10*difference) \
            and (abs(theta[accumParallel[j][1]] - theta[accumParallel[i][1]]) > 10*difference):
            fourLines.append(np.concatenate([accumParallel[i],accumParallel[j]]))


# fourLines = operation.unique(fourLines)



#solve 4 of equations for 4 corners
#rho_j = x cos(theta_j) + y sin(theta_j)
#rho_k = x cos(theta_k) + y sin(theta_k)
corners = []
for quads in range (0, len(fourLines)):
    flag = True
    cornersTemp = []
    for lines in range (0,4):
        if lines <= 1:
            linesi = lines
            nexti = 2
        elif lines == 2:
            linesi = 0
            nexti = 3
        else:
            linesi = 1
            nexti = 1
        b = np.array([rho[fourLines[quads][linesi]],rho[fourLines[quads][linesi+nexti]]])
        a = np.array([[np.cos(theta[fourLines[quads][linesi]]),
                     np.sin(theta[fourLines[quads][linesi]])],
                    [np.cos(theta[fourLines[quads][linesi+nexti]]),
                     np.sin(theta[fourLines[quads][linesi+nexti]])]])
        #try:
        #    ans = np.linalg.solve(a, b)
        #    cornersTemp.append([int(ans[0]),int(ans[1])])
        #except:
        #    flag = False
        #    break
        ans = np.linalg.solve(a, b)
        cornersTemp.append([int(ans[0]),int(ans[1])])
    if flag:
        corners.append(cornersTemp)

#reorder corners
corners = operation.reorderPoints(corners)

print len(corners)
out = 0
bri = 0
small = 0
stdd = 0

if len(corners) > 0:
    #check if valid parallelograms
    for i in range (len(corners)-1,-1,-1):
        xlin = np.array(np.linspace(corners[i][0][0],corners[i][2][0],20)).astype(int)
        ylin = np.array(np.linspace(corners[i][0][1],corners[i][2][1],20)).astype(int)
        xlin2 = np.array(np.linspace(corners[i][1][0],corners[i][3][0],20)).astype(int)
        ylin2 = np.array(np.linspace(corners[i][1][1],corners[i][3][1],20)).astype(int)
    
        # remove wrong parallelogram if std
        try:
            std = np.std(np.concatenate([image_gray[ylin[2:-2],xlin[2:-2]],image_gray[ylin2[2:-2],xlin2[2:-2]]]))
            if std > 7:
                stdd += 1
                del corners[i]
                continue
        except:
        # remove wrong parallelogram if out of image
            out += 1
            del corners[i]
            continue
        
        minx = np.min(np.array(corners[i])[:,0])
        maxx = np.max(np.array(corners[i])[:,0])
        miny = np.min(np.array(corners[i])[:,1])
        maxy = np.max(np.array(corners[i])[:,1]) 
    
        height = operation.getLength(corners[i][0],corners[i][1])
        width = operation.getLength(corners[i][2],corners[i][1])
    
        #remove wrongs parallelogram if small
        if height < 20 or width < 20 or maxy-miny < 10 or maxx-minx < 10:
            small += 1
            del corners[i]
            continue
        
        #remove wrongs if brighter
        averageInside = np.average(np.concatenate([image_gray[(ylin[2:-2]),(xlin[2:-2])],image_gray[(ylin2[2:-2]),(xlin2[2:-2])]]))
        corners[i].append(corners[i][0])
        delete = False
        pixelsFromBorder = 5
        middlePoint = np.array([(corners[i][0][0]+corners[i][2][0])/2,(corners[i][0][1]+corners[i][2][1])/2])
        for j in range (0,4):        
            y = pixelsFromBorder*np.sin(operation.getAngle([0,0],[1,0],
                                                          (np.array(corners[i][j+1])+np.array(corners[i][j]))/2-middlePoint,False))
            x = pixelsFromBorder*np.cos(operation.getAngle([0,0],[1,0.01],
                                                          (np.array(corners[i][j+1])+np.array(corners[i][j]))/2-middlePoint,False))
            try:
                a = (np.array(corners[i][j+1])+np.array(corners[i][j]))/2+[int(x),int(y)]            
                if image_gray[a[1],a[0]] - averageInside < 5:
                    delete = True
                    break
            except:
                delete = True
                break
        if delete:
            bri += 1
            del corners[i]
            continue

print("out ", out, " std ", stdd, " brighter ", bri, " small", small)
print(len(corners))

if len(corners) > 0:        
    # Removing duplicates
    # Here we remove duplicate parallelograms by finding the overlapping ones
    sumi = np.zeros(len(corners))
    middlePoint = np.zeros((len(corners),2))
    for i in range (len(corners)-1,-1,-1):
        middlePoint[i] = np.array([(corners[i][0][0]+corners[i][2][0])/2,(corners[i][0][1]+corners[i][2][1])/2])
        #check for edges
        for j in range (0,4):
            x1 = corners[i][j][0]
            x2 = corners[i][j+1][0]
            y1 = corners[i][j][1]
            y2 = corners[i][j+1][1]
            if x1 != x2:
                m = (y2-y1)/(1.0*(x2-x1))
                q = y2-m*x2
                x = np.linspace(np.min([x1,x2]),np.min([np.max([x1,x2]),edged.shape[1]-5]),np.absolute(x2-x1)+1)
                y = m*x+q
            else:
                y = np.linspace(np.min([y1,y2]),np.min([np.max([y1,y2]),edged.shape[1]-5]),np.max([y1,y2])-np.min([y1,y2])+1)
                x = x1*np.ones(len(y))
            sumi[i] += np.sum(edged[np.round(y).astype(int),np.round(x).astype(int)])/255.0
    maxDistance = 10
    corners2 = []
    corners2.append(len(corners)-1)
    for i in range(len(corners)-2,-1,-1):
        found = 0
        for j in range (len(corners2)-1,-1,-1):
            if operation.getLength(middlePoint[corners2[j]],middlePoint[i])<=maxDistance:
                found = 1
                if sumi[i] > sumi[corners2[j]]:
                    corners2[j] = i
        if found == 0:
            corners2.append(i)

if len(corners) > 0:
            
    fig2, ax1 = plt.subplots(ncols=1, nrows=1, figsize=(8, 4))
    ax1.imshow(image_rgb)
    ax1.set_axis_off()
    for i in corners2:
        for j in range (0,4):
            ax1.plot( [corners[i][j][0],corners[i][j+1][0]],[corners[i][j][1],corners[i][j+1][1]], 'xb-',linewidth=3)
    ax1.set_ylim([image_gray.shape[0],0])
    ax1.set_xlim([0,image_gray.shape[1]])
    fig2.savefig("tmp/output.jpg")
    # plt.show()
else:
    print ('No parallelograms were found')

endtime = time.clock()
print "time4 %f\n" % (endtime - begintime)