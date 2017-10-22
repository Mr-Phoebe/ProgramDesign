import numpy as np
import math

def print_item(input):
    print(input.shape[0], input.shape[1], input)

def rgb2gray(image_rgb):
    """
    Return the gray image from the rgb image.
    """
    r, g, b = image_rgb[:,:,0], image_rgb[:,:,1], image_rgb[:,:,2]
    image_gray = np.round(0.3 * r + 0.59 * g + 0.11 * b).astype(np.uint8)

    return image_gray

def getLength(startPoint,secondPoint):
    """
    :Return the length between two points
    """
    v1x = secondPoint[0] - startPoint[0]
    v1y = secondPoint[1] - startPoint[1]
    lenv = math.sqrt(v1x*v1x + v1y*v1y)
    return lenv
    
def unique(a):
    ##Inputs:
    #a - list of 1xN arrays

    ##Outputs:
    #b - filtered array

    #Example
    # a=[array([ 1,  3, 12, 17]),
    #    array([ 1,  3, 17, 12]),
    #    array([ 1,  3, 18, 20])]
    # b -> [array([ 1,  3, 12, 17]),
    #       array([ 1,  3, 18, 20])]

    if a == []:
        return []
    b = np.array(a)
    a = np.sort(np.array(a))
    order = np.lexsort(a.T)
    a = a[order]
    b = b[order]
    diff = np.diff(a, axis=0)
    ui = np.ones(len(a), 'bool')
    ui[1:] = (diff != 0).any(axis=1) 
    return b[ui]
    
def reorderPoints(corners):
    """
        Return reordered corners array
    """
    reordered = []
    for i in range(len(corners)):
        pointArray=[]
        length1 = getLength(corners[i][0],corners[i][1])
        length2 = getLength(corners[i][0],corners[i][2])
        length3 = getLength(corners[i][0],corners[i][3])
        lenArr = np.array([length1,length2,length3])
        lenArr[np.where(np.array(lenArr)==np.min(lenArr))[0][0]] -= 10     # get minimun one
        pointArray.append(corners[i][0])
        pointArray.append(corners[i][1+np.where(np.array(lenArr)==np.min(lenArr))[0][0]])
        pointArray.append(corners[i][1+np.where(np.array(lenArr)==np.max(lenArr))[0][0]])
        pointArray.append(corners[i][1+np.where(np.array(lenArr)==np.median(lenArr))[0][0]])
        reordered.append(pointArray)
    return reordered
    
def getAngle(startPoint,secondPoint,thirdPoint, absol=True):
    """
    Return angle between vector(startPoint,secondPoint) and vector(secondPoint,thirdPoint)
    """
    v1x = secondPoint[0] - startPoint[0]
    v1y = secondPoint[1] - startPoint[1]
    v2x = thirdPoint[0] - startPoint[0]
    v2y = thirdPoint[1] - startPoint[1]
    
    lenv1 = np.sqrt(v1x*v1x+v1y*v1y)
    lenv2 = np.sqrt(v2x*v2x+v2y*v2y)
    
    angle = np.arccos((v1x*v2x+v1y*v2y)/(lenv1*lenv2))
    
    a = 1
    if not absol:
        a = np.sign((v1x) * (v2y) - (v1y) * (v2x))
    
    if np.absolute(angle) < 0.02:
        angle = 0
    return a*angle

def extended_boundary(input):
    """
    Make 3x3 tiled array. Central area is 'input', 
    surrounding areas are reflected.
    """

    # Get a 3x3 tiles
    output = np.tile(input, (3, 3))

    rows = input.shape[0]
    cols = input.shape[1]

     
    # Left hand side and right hand side need to be flipped left-to-right. 
    for i in range(3):
        output[i*rows:(i + 1)*rows, 0:cols] = \
            np.fliplr(output[i*rows:(i + 1)*rows, 0:cols])
        output[i*rows:(i + 1)*rows, -cols:] = \
            np.fliplr(output[i*rows:(i + 1)*rows, -cols:])

    # Top and bottom row need to be flipped up-to-down
    for i in range(3):
        output[0:rows, i*cols:(i + 1)*cols] = \
            np.flipud(output[0:rows, i*cols:(i + 1)*cols])
        output[-rows:, i*cols:(i + 1)*cols] = \
            np.flipud(output[-rows:, i*cols:(i + 1)*cols])

    # The central array shouldn't be changed. 
    assert(np.array_equal(input, output[rows:2*rows, cols:2*cols]))

    # All sides of the middle array should be the same as those bordering them.
    # Check this starting at the top and going around clockwise. This can be
    # visually checked by plotting the 'output' array.
    assert(np.array_equal(input[0, :],  output[rows-1, cols:2*cols]))
    assert(np.array_equal(input[:, -1], output[rows:2*rows, 2*cols]))
    assert(np.array_equal(input[-1, :], output[2*rows, cols:2*cols]))
    assert(np.array_equal(input[:, 0],  output[rows:2*rows, cols-1]))

    return output

def convolve(input, weights):
    """
    2 dimensional convolution.
    """

    assert(len(input.shape) == 2)
    assert(len(weights.shape) == 2)    
    assert(weights.shape[0] < input.shape[0] + 1)
    assert(weights.shape[1] < input.shape[1] + 1)
    
    output = np.copy(input)
    tiled_input = extended_boundary(input)

    rows = input.shape[0]
    cols = input.shape[1]

    # Stands for half weights row. 
    hw_row = weights.shape[0] / 2
    hw_col = weights.shape[1] / 2

    # Now do convolution on central array.
    # Iterate over tiled_input. 
    for i, io in zip(range(rows, rows*2), range(rows)):
        for j, jo in zip(range(cols, cols*2), range(cols)):
            # The current central pixel is at (i, j)

            average = 0.0
         
            # Find the part of the tiled_input array that overlaps with the
            # weights array.
            overlapping = tiled_input[i - hw_row:i + hw_row + 1, j - hw_col:j + hw_col + 1]
            assert(overlapping.shape == weights.shape)

            tmp_weights = weights
            merged = tmp_weights[:] * overlapping
            average = np.sum(merged)

            # Set new output value.
            output[io, jo] = average

    return output