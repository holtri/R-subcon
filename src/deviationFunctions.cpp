#include <Rcpp.h>
using namespace Rcpp;


double KSTestC(LogicalVector indexSelection, NumericVector indexMapReferenceAttribute){
  double cumDistSubspace = 0;
  double maxDistance = 0;
  int numRemaining = sum(indexSelection);
  int numTotal = indexSelection.size();

  for(int i=0; i < numTotal; i++){
    if(indexSelection[indexMapReferenceAttribute[i]-1]){
      cumDistSubspace += 1.0/numRemaining;
    }
    double currentDiff = std::abs(((i + 1.0)/numTotal) - cumDistSubspace);
    if(currentDiff > maxDistance){
      maxDistance = currentDiff;
    }
  }
  return maxDistance;
}

LogicalVector randomSubspaceSliceC(NumericMatrix indexMap, NumericVector subspace, double alpha, int referenceDim) {

  int sliceSize = std::ceil(indexMap.rows() * (std::pow(alpha,(1.0/(subspace.size()-1)))));
  LogicalVector selectionAll(indexMap.rows());
  selectionAll.fill(1);

  NumericVector::iterator it;
  for(it = subspace.begin(); it != subspace.end(); ++it){
    if(*it != referenceDim){
      int l = std::rand() % (indexMap.rows() - sliceSize);
      int r = l + sliceSize;
      for(int j=0; j< l; j++){
        selectionAll[indexMap(j,*it - 1) -1] = 0;
      }
      for(int j=r; j< indexMap.rows(); j++){
        selectionAll[indexMap(j,*it - 1) -1] = 0;
      }
    }
  }
  return selectionAll;
}

double averageDeviationC(NumericMatrix indexMap, NumericVector subspace, double alpha, int referenceDim, int numRuns){
  double result = 0;
  for(int i=0; i<numRuns; i++){
    result += KSTestC(randomSubspaceSliceC(indexMap, subspace, alpha, referenceDim), indexMap.column(referenceDim - 1));
  }
  return result/numRuns;
}

NumericVector deviationVectorC(NumericMatrix indexMap, NumericVector subspace, double alpha, int referenceDim, int numRuns){
  NumericVector result(numRuns);
  for(int i=0; i<numRuns; i++){
    result[i] = KSTestC(randomSubspaceSliceC(indexMap, subspace, alpha, referenceDim), indexMap.column(referenceDim - 1));
  }
  return result;
}

List deviationStatisticsC(NumericMatrix indexMap, double alpha, int numRuns){
  NumericMatrix outAverage(indexMap.ncol(), indexMap.ncol());
  colnames(outAverage) = colnames(indexMap);
  rownames(outAverage) = colnames(indexMap);

  NumericMatrix outSD(indexMap.ncol(), indexMap.ncol());
  colnames(outSD) = colnames(indexMap);
  rownames(outSD) = colnames(indexMap);

  for(int i=0; i< outAverage.ncol(); i++){
    for(int j=0; j< outAverage.ncol(); j++){
      if(i==j){
        outAverage(i,j) = 0;
      }
      else{
        NumericVector subspace = NumericVector::create(i+1,j+1);
        NumericVector deviatioVector = deviationVectorC(indexMap, subspace, alpha, i+1, numRuns);
        outAverage(i,j) = mean(deviatioVector);
        outSD(i,j) = sd(deviatioVector);
      }
    }
  }
  return List::create(Named("avg") = outAverage, Named("sd") = outSD);
}

double HiCSContrastC(NumericMatrix indexMap, NumericVector subspace, double alpha, int numRuns){
  double result = 0;
  for(int i=0; i<numRuns; i++){
    int referenceDim = subspace[std::rand() % (subspace.size())];
    result += KSTestC(randomSubspaceSliceC(indexMap, subspace, alpha, referenceDim), indexMap.column(referenceDim - 1));
  }
  return result/numRuns;
}

NumericMatrix deviationMatrixC(NumericMatrix indexMap, double alpha, int numRuns){
  NumericMatrix out(indexMap.ncol(), indexMap.ncol());
  colnames(out) = colnames(indexMap);
  rownames(out) = colnames(indexMap);

  for(int i=0; i< out.ncol(); i++){
    for(int j=0; j< out.ncol(); j++){
      if(i==j){
        out(i,j) = 0;
      }
      else{
        NumericVector subspace = NumericVector::create(i+1,j+1);
        out(i,j) = averageDeviationC(indexMap, subspace, alpha, i+1, numRuns);
      }
    }
  }
  return out;
}

NumericMatrix HiCSMatrixC(NumericMatrix indexMap, double alpha, int numRuns){
  NumericMatrix out(indexMap.ncol(), indexMap.ncol());
  colnames(out) = colnames(indexMap);
  rownames(out) = colnames(indexMap);

  for(int i=0; i< out.ncol(); i++){
    for(int j=i; j< out.ncol(); j++){
      if(i==j){
        out(i,j) = 0;
      }
      else{
        NumericVector subspace = NumericVector::create(i+1,j+1);
        out(i,j) = HiCSContrastC(indexMap, subspace, alpha, numRuns);
        out(j,i) = out(i,j);
      }
    }
  }
  return out;
}
