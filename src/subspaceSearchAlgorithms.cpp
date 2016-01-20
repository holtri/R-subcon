#include <Rcpp.h>
#include "deviationFunctions.h"
using namespace Rcpp;

//Sys.setenv("PKG_CXXFLAGS"="-std=c++0x")
//Sys.unsetenv('PKG_CXXFLAGS')

// [[Rcpp::plugins(cpp11)]]

std::vector<int> sortIndices(const NumericVector &input){
  std::vector<int> idx(input.size());
  std::iota(idx.begin(), idx.end(), 0);
  std::sort(idx.begin(), idx.end(), [&input](int a, int b){return input[a] > input[b];});
  return idx;
}

std::vector<NumericVector> GMD(NumericMatrix indexMap, double alpha, int numRuns){

  std::vector<NumericVector> outputSpaces(indexMap.ncol());

  List deviationStatistics2Dim = deviationStatisticsC(indexMap, alpha, numRuns);
  NumericMatrix avgDeviation2Dim = deviationStatistics2Dim["avg"];

  for(int refDim = 0; refDim<indexMap.ncol(); refDim++){
    std::vector<int> sortedIdx = sortIndices(avgDeviation2Dim(refDim,_));
    std::vector<int> subspace;
    subspace.push_back(refDim + 1); //subspace construction starts with reference dimension, remember to add 1 to match R indices
    double max = - 1.0;
    for(std::vector<int>::iterator it = sortedIdx.begin(); it != sortedIdx.end(); ++it){
      if(*it != refDim){
        subspace.push_back(*it + 1); //add dimension to subspace, remember to add 1 to match R indices

        double tmp = averageDeviationC(indexMap, Rcpp::wrap(subspace), alpha, refDim + 1, numRuns);
        if(tmp < max){
          subspace.pop_back();
        }else{
          max = tmp;
        }

      }
    }
    outputSpaces[refDim] = Rcpp::wrap(subspace);
  }

  // return List::create(_["subspaces"] = outputSpaces, _["referenceDim"]);
  return outputSpaces;
}

//   outputSpaces.push_back(LogicalVector::create(1,0,0,1));
//   outputSpaces.push_back(LogicalVector::create(1,0,1,0));
//   List deviationTwoDim = deviationStatisticsC(indexMap, alpha, numRuns);
//
//   double avg = m(1,2);
//   Rcout << avg << std::endl;
