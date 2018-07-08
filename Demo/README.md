# K-Means Demo
### An implementation of the unsupervised machine learning algorithm k-means.
##### Written in C.
##### By David Gold.

Note: Average data point distance remains rather high as data points are randomly generated therefore do not cluster well.
Note: real k-means implementation is significantly faster. Program is held back by printing.

### example_k-means usage:

##### Compile with:
  make

##### Program requires two arguments:
  1) The number of dimensions the user wants randomly generated data to be.
    ex: 3 would be: [n,n,n] where n is a double.
  2) The number of centroids (or "groups") the data should be put into.
  
##### Program has optional third argument:
  
  3) The number of data points to generate.

### k-means.h usage:

##### include:
"k-means.h"

#### Call with:

`kmeans(int * min_vals, int * max_vals, int CENTROIDS, int DIMENSIONS, double ** pixel_raw_data, int data_points);`

  ###### min_vals:
  minimum values of n dimensional data. Each array location represents the given dimensions minimum value.
  
  ###### max_vals:
  maximum values of n dimensional data. Each array location represents the given dimension's maximum value.
  
  ###### CENTROIDS:
  the number of centroids to use.
  
  ###### DIMENSIONS:
  the number of dimensions the data are in (denoted n).
  
  ###### pixel_raw_data:
  a 2D array of doubles, the first dimension corresponds to a given data point. The second dimension is the given data points n dimensional data.
  
  ###### data_points:
  The number of data points being passed in (size of pixel_raw_data).
  
#### Program returns:

  ###### An array of size data_points of structs designated "pixel." Each pixel struct contains the following information:
  
  ###### pixel_num:
  the pixel's location in the array.
  
  ###### lowest_dist:
  the distance from the pixel to it's nearest centroid.
  
  ###### centroid:
  the pixel's corresponding centroid.
  
  ###### location:
  an n dimensional array of doubles passed from pixel_raw_data.

#### Files:

Makefile -- to compile code.

example_k-means.c -- all methods for example k means program.

k-means.c -- all methods for k-means program.

k-means.h -- header file for k-means program. Include when calling.
