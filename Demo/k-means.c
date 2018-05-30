#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "k-means.h"
#include <math.h>
#include <time.h>
#include <float.h>
//An implementation of k-means by David Gold.
//
struct pixel ** kmeans(int * min_vals, int * max_vals, int CENTROIDS, int DIMENSIONS, double ** pixel_raw_data, int data_points){
pixel_data=malloc(sizeof(struct pixel)*data_points);
struct pixel * centroids[CENTROIDS];
time_t t;
srand((unsigned) time(&t));
//placing centroids in random initial locations
for(int i=0;i<CENTROIDS;i++){
	centroids[i]= add_pixel(place_k(min_vals, max_vals, DIMENSIONS));
	normalize_vals(centroids[i]->location, DIMENSIONS, min_vals, max_vals);
	printf("Centroid %i initial location: ",i);print_pixel(centroids[i], DIMENSIONS);
}
for(int i=0;i<data_points;i++){
	pixel_data[i]=add_pixel(pixel_raw_data[i]);
	normalize_vals(pixel_data[i]->location, DIMENSIONS, min_vals, max_vals);
    }
    //for how much centroids are moving
    double largest_change=0;
    double comp=0;
		int iteration=0;
    //keep updating centroids and recalculating all given pixels distances to said centroids until the centroids stop moving, that is once largest_chage<0.01;
    do{
		iteration++;
    largest_change=0;
    //gets each pixels centroid distance
    for(int i=0;i<data_points;i++){
	for(int j=0;j<CENTROIDS;j++){
	comp=get_distance(centroids[j]->location, pixel_data[i]->location, DIMENSIONS);
	if(pixel_data[i]->lowest_dist>comp){
	pixel_data[i]->lowest_dist=comp;
	pixel_data[i]->centroid=j;
	}
	}
    }
    //updating each centroid
    double temp=0;
  for(int l=0;l<CENTROIDS;l++){
		temp=update_centroid_location(centroids[l]->location, l, data_points, pixel_data, DIMENSIONS);
		printf("Centroid %i moved %f on iteration %i: ",l, temp, iteration);print_pixel(centroids[l], DIMENSIONS);
		if(temp>largest_change)
	    largest_change=temp;
  }
	printf("Avg data point distance after iteration %i: %f\n", iteration, get_avg_dist(data_points, pixel_data));
    } while(largest_change>0.0001);
    free_all(centroids, CENTROIDS);
    free_all(pixel_data,data_points);
    return pixel_data;
}
double get_avg_dist(int data_points, struct pixel ** pixel_data){
    double avg=0;
    for(int i=0;i<data_points;i++){
	avg+=pixel_data[i]->lowest_dist;
    }
    return (avg/data_points);
}
//returns difference between the centroid
//useful to know how a centroid is changing
double update_centroid_location(double *centroid, int centroid_num, int data_points, struct pixel ** pixel_data, int DIMENSIONS){
    double old_cent[DIMENSIONS];
    memcpy(old_cent,centroid,DIMENSIONS*sizeof(double));
    double *sum=malloc(DIMENSIONS*sizeof(double));
    if(!sum){
    perror("couldnt allocate memory");
    exit(4);
    }
    memset(sum, 0, DIMENSIONS*sizeof(double));
    int pixcount=0;
    for(int i=0;i<data_points;i++){
	if(pixel_data[i]->centroid==centroid_num){
	    pixcount++;
	    for(int j=0;j<DIMENSIONS;j++){
		sum[j]+=pixel_data[i]->location[j];
	    }
	}
    }
    for(int m=0;m<DIMENSIONS;m++){
    sum[m]=(sum[m]/data_points);
    }
    memcpy(centroid,sum,DIMENSIONS*sizeof(double));
    free(sum);
    return get_diff(centroid, old_cent, DIMENSIONS);
}
double get_diff(double * cent, double * old_cent, int DIMENSIONS){
    double diff=0;
    for(int i=0;i<DIMENSIONS; i++){
	diff+=sqrt(pow(cent[i]-old_cent[i],2));
    }
    return diff;
}
void free_all(struct pixel ** arr, int count){
  for(int i=0;i<count;i++){
	   free(arr[i]->location);
	    free(arr[i]);
  }
}
struct pixel * add_pixel(double * location){
    struct pixel * new=malloc(sizeof(struct pixel));
    if(!new){
    perror("Could not allocate space for pixel");
    exit(4);
    }
    new->lowest_dist=DBL_MAX;
    new->centroid=0;
    new->location=location;
    return new;
}
void print_pixel(struct pixel * p, int DIMENSIONS){
    printf("Location: [");
    for(int i=0;i<DIMENSIONS;i++){
	printf("%f,", p->location[i]);
    }
    printf("]\n");
}
void normalize_vals(double  *pixel_data, int size, int * min_vals, int * max_vals){
    for(int i=0;i<size; i++){
	pixel_data[i]=normalize_val(pixel_data[i],max_vals[i],min_vals[i]);
    }
}
double normalize_val(double value, double max_vals, double min_vals){
    return (value-min_vals)/(max_vals-min_vals);
}
double * place_k(int * min_vals, int * max_vals, int DIMENSIONS){
    double * tmp= malloc(DIMENSIONS*sizeof(double));
    if(!tmp){
    perror("Could not allocate space");
    exit(4);
    }
    for(int i=0;i<DIMENSIONS;i++){
	     tmp[i]=rand() % (max_vals[i]+1 - min_vals[i])+min_vals[i];
    }
    return tmp;
}
double get_distance(double * centroid_location, double * pixel_data, int DIMENSIONS){
    double total=0;
    for(int i=0; i<DIMENSIONS;i++){
	total+=pow(centroid_location[i]-pixel_data[i],2);
    }
    return sqrt(total);
}
