#ifndef CMI_H
#define CMI_H

#include <Rcpp.h>
#include <queue>
#include <vector>       // std::vector

// CMI-Search

// // Subspace-Properties
// struct Subspace{
//   std::vector<int> space;
//   double hce;
//   double chce;
// };


  // calculate hce
  double calcHce(std::vector<double> space);



// calculate cond. hce
// todo: data is Rcpp::NumericMatrix
   double calcCHce(std::vector<double> data, int refDim, int conDim, unsigned int numClust);
//   //data, referenceDim, conditionalDim, numClusters = 1)


//   // calculate cmi
   double cmi(Rcpp::NumericVector subspace, Rcpp::NumericMatrix data);

#endif
