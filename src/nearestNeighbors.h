#ifndef NEARESTNEIGHBORS_H
#define NEARESTNEIGHBORS_H

#include <RcppArmadillo.h>

using namespace Rcpp;

//' Reverse Nearest Neighbors
//'
//' Extracts the reverse nearest neighbors for a given knn matrix
//'
//' @param knn n x k Matrix of knn indices
//'
//' @export
// [[Rcpp::export]]
Rcpp::List reverseNearestNeighborsC(arma::mat knn);

#endif
