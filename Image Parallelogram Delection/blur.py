from operation import convolve
import numpy as np

def blurImage(image_gray):
    kernel = np.ones((3,3),np.float32)/9
    res = convolve(image_gray, kernel)
    return np.round(res).astype(np.uint8)

def gaussian_kernel(sigma, truncate=4.0):
    """
    Return Gaussian that truncates at the given number of standard deviations. 
    Make sure the kernel size be odd.
    """

    sigma = float(sigma)
    radius = int((truncate * sigma + 0.5)/2)
    print(radius+radius+1)
    x, y = np.mgrid[-radius:radius+1, -radius:radius+1]
    sigma = sigma**2

    k = 2*np.exp(-0.5 * (x**2 + y**2) / sigma)

    k = k / np.sum(k)
    return k

def gaussianblur(input, sigma=1, ksize=-1):
    """
    Return Image convolved with Gaussian Filter.
    :sigma: guassian standard deviations
    :ksize: the size of guassian kernel
    """
    return convolve(input, gaussian_kernel(sigma)) if ksize == -1 else convolve(input, gaussian_kernel(sigma, 2*ksize/sigma))
