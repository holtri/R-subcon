#ifndef DEVIATIONFUNCTIONS_H
#define DEVIATIONFUNCTIONS_H

using namespace Rcpp;

//' LOF reachability distance
//'
//' Calculates reachability distance for all objects
//'
//' @param knnIndex n x k Matrix of knn indices
//' @param knnDistance n x k Matrix of knn distances
//' @param vector indices for the k-neighborhood
//' @return vector of local reachability densities
//'
//' @export
// [[Rcpp::export]]
NumericVector reachability(NumericMatrix knnIndex, NumericMatrix knnDistance, NumericVector maxkIdx);

//' Local outlier factor calculation
//'
//' Calculates LOF based on reachability densitiesfor all objects
//'
//' @param lrd vector of local reachability densities
//' @param knnIndex n x k Matrix of knn indices
//' @param vector indices for the k-neighborhood
//' @return vector of local outlier factors
//'
//' @export
// [[Rcpp::export]]
NumericVector lofCalculation(NumericVector lrd, NumericMatrix knnIndex, NumericVector maxkIdx);

#endif
