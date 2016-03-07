#include <Rcpp.h>
using namespace Rcpp;

NumericVector reachability(NumericMatrix knnIndex, NumericMatrix knnDistance, int k) {
  NumericVector lrd(knnIndex.nrow());
  double kdistO, distOP = 0;

  for(int i = 0; i < knnIndex.nrow(); i++) {
    double sumDistances = 0;
    for(int  j=0; j < k; j++) {
      kdistO = knnDistance(knnIndex(i,j)-1, k-1); // k-distance(o)
      distOP = knnDistance(i,j); // d(o,p)
      sumDistances += std::max(kdistO,distOP);
    }
    lrd(i) = 1/(sumDistances/k); // local reachability density
  }
  return lrd;
}

NumericVector lofCalculation(NumericVector lrd, NumericMatrix knnIndex, int k) {

  double reachabilityRatioSum = 0;
  NumericVector lof(knnIndex.nrow());

  for(int i = 0; i < knnIndex.nrow(); i++) {
    reachabilityRatioSum = 0;
    for(int  j = 0; j < k; j++) {
      reachabilityRatioSum += lrd(knnIndex(i, j)-1)/lrd(i);
    }
    lof(i) = reachabilityRatioSum/k;
  }

  return lof;
}
