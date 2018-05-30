#ifndef k_means
#define k_means
struct pixel{
int pixel_num;
double lowest_dist;
int centroid;
double * location;
};
struct pixel ** pixel_data;
struct pixel ** kmeans(int * min_vals, int * max_vals, int CENTROIDS, int DIMENSIONS, double ** pixel_raw_data, int data_points);
double get_avg_dist(int data_points, struct pixel ** pixel_data);
double get_diff(double * cent, double * old_cent, int DIMENSIONS);
double update_centroid_location(double *centroid, int centroid_num, int data_points, struct pixel ** pixel_data, int DIMENSIONS);
void free_all(struct pixel ** arr, int count);
struct pixel * add_pixel(double * location);
void normalize_vals(double  *pixel_data, int size, int * min_vals, int * max_vals);
void print_pixel(struct pixel * p, int DIMENSIONS);
double normalize_val(double value, double max_vals, double min_vals);
double * place_k(int * min_vals, int * max_vals, int DIMENSIONS);
double get_distance(double * centroid_location, double * pixel_data, int DIMENSIONS);
#endif
