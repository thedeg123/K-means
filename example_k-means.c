#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include "k-means.h"
#include <string.h>
/* A example program for the k-means algorithm to show it in action.
program requires 2 inputs: number of dimensions for random data (ex: x,y) or (x,y,z,a,b)
followed by number of centorids
optional third input is the number of data points. If no value is specified it will
assume 150.*/
int main(int argc, char * argv[]){
int dimensions=0;
int centroids=0;
int data_points=150;
if(argc<3){
  printf("Please enter number of dimensions for data followed by number of centroids.\n");
  exit(1);
}
else{
  dimensions=atoi(argv[1]);
  centroids=atoi(argv[2]);
  if(argc==4)
    data_points=atoi(argv[3]);
}
//seeding random number generator
time_t t;
srand((unsigned) time(&t));
//int * min_vals, int * max_vals, int CENTROIDS, int DIMENSIONS, double ** pixel_raw_data
double ** raw_data=malloc(sizeof(double)*data_points);
int * min_vals=malloc(sizeof(int)*dimensions);
int * max_vals=malloc(sizeof(int)*dimensions);
if(!raw_data || !min_vals || !max_vals){
  perror("");
  exit(4);
}
//setting initial values for min/max arrays
for(int i=0;i<dimensions;i++){
  min_vals[i]=INT_MAX;
  max_vals[i]=0;
}
//giving each data point random values.
for(int i=0;i<data_points;i++){
    raw_data[i]=malloc(sizeof(double)*dimensions);
    if(!raw_data[i]){
      perror("");
      exit(4);
    }
    for(int j=0;j<dimensions;j++){
      //values can be between 0 and any value for any dimension.
      //This is just for simplicity of the example
      raw_data[i][j]=rand() % 1000;
      if(raw_data[i][j]>max_vals[j])
        max_vals[j]=raw_data[i][j];
      if(raw_data[i][j]<min_vals[j])
          min_vals[j]=raw_data[i][j];
    }
}
kmeans(min_vals,max_vals,centroids,dimensions, raw_data, data_points);
free(min_vals);
free(max_vals);
free(raw_data);
return 0;
}
