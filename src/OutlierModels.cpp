#include <Rcpp.h>
using namespace Rcpp;

NumericVector reachability(NumericMatrix knnIndex, NumericMatrix knnDistance, NumericVector maxkIdx) {
  NumericVector lrd(knnIndex.nrow());
  double kdistO, distOP = 0;

  for(int i = 0; i < knnIndex.nrow(); i++) {
    // Rcout << "maxkIdx for object " << i << " is " << maxkIdx(i) << std::endl;
    double sumDistances = 0;
    for(int  j=0; j < maxkIdx(i); j++) {
      kdistO = knnDistance(knnIndex(i,j)-1, maxkIdx(j)-1); // k-distance(o)
      distOP = knnDistance(i,j); // d(o,p)
      sumDistances += std::max(kdistO,distOP);
    }
    lrd(i) = 1/(sumDistances/maxkIdx(i)); // local reachability density
  }
  return lrd;
}

NumericVector lofCalculation(NumericVector lrd, NumericMatrix knnIndex, NumericVector maxkIdx) {

  double reachabilityRatioSum = 0;
  NumericVector lof(knnIndex.nrow());

  for(int i = 0; i < knnIndex.nrow(); i++) {
    reachabilityRatioSum = 0;
    for(int  j = 0; j < maxkIdx(i); j++) {
      reachabilityRatioSum += lrd(knnIndex(i, j)-1)/lrd(i);
    }
    lof(i) = reachabilityRatioSum/maxkIdx(i);
  }

  return lof;
}
