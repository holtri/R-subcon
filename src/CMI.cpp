#include "CMI.h"
// #include <Rcpp.h>
#include <algorithm>
#include <vector>

#include <shark/Algorithms/KMeans.h> //k-means algorithm
#include <shark/Models/Clustering/Centroids.h>//model performing hard clustering of points
#include <shark/Models/Clustering/HardClusteringModel.h>//model performing hard clustering of points

#include <Rcpp.h>
#include "utils.h" // some conversion helpers

using namespace shark;
using namespace std;

using namespace Rcpp;

NumericVector SharkKMeansTrain (NumericMatrix X, ssize_t k) {
  UnlabeledData<RealVector> data = NumericMatrixToUnlabeledData(X);

  Centroids centroids;
  kMeans (data, k, centroids);

  HardClusteringModel<RealVector> model(&centroids);
  Data<unsigned> clusters = model(data);

  return(LabelsToNumericVector(clusters));
}

// [[Rcpp::export]]
double calcHce(std::vector<double> dataVector) {
  double hce = 0.0;
  std::sort (dataVector.begin(), dataVector.end());

  for(unsigned int i=0; i<dataVector.size()-1; ++i){
    double tmp = double(i+1)/dataVector.size();
    hce += (dataVector[i+1] - dataVector[i]) * tmp * log(tmp);
  }
  return -hce;
}

double calcCHce(Rcpp::NumericMatrix data, std::vector<double> dim, unsigned int numClust){
  double chce = 0.0;
  std::vector<double> conDim = dim;

  conDim.pop_back(); // delete the refDim (per def.: the last element)
  NumericVector labels = SharkKMeansTrain(data, numClust);

  // Pro Cluster hce berechnen
  for (unsigned int i=0; i<numClust; i++){
      // chce = chce + cluster.size()/data.size() * calcHce(); // todo: vervollstaendigen
  }
  return chce;
}

double best2DimProjection(Rcpp::NumericVector subspace, Rcpp::NumericMatrix data, std::vector<int> p2dim){
  std::vector<int> best2dim;
  double maxContrast = 0.0;

  for (int i=0; i<subspace.size(); i++){
    for(int j=0; j<subspace.size(); j++){
      if(i!=j){
        NumericVector attr = data( _, i);
        std::vector<double> dat = Rcpp::as<std::vector<double> >(attr);

        // todo: when chce is complete: add it to calcul.:
        double tmpContrast = calcHce(dat); //Content from all: data[*][i]

        if(tmpContrast > maxContrast){
          best2dim.push_back(subspace[j]); //condDim
          best2dim.push_back(subspace[i]); //refDim
          maxContrast = tmpContrast;
        }
      }
    }
  }
  return maxContrast;
}

double addDimToPermutation(std::vector<int> & permutation, std::vector<int> remainingDimensions){
  double pNextdimContrast = 0.0;
  int nextDim;

  for(int i=0; i<remainingDimensions.size(); i++) {
    permutation.push_back(remainingDimensions[i]);
    double tmp = 0.0;
    // todo: vervollstaendigen: tmp = hce("subspaceVec[i]") - chce("p2dim")

    if(tmp > pNextdimContrast){
      nextDim = remainingDimensions[i];
      pNextdimContrast = tmp;
    }
    permutation.pop_back();
  }
  permutation.push_back(nextDim);
  return pNextdimContrast;
}

// [[Rcpp::export]]
 double cmi(Rcpp::NumericVector subspace, Rcpp::NumericMatrix data){
  double cmiContrast = 0.0;
  std::vector<int> permutation;

  //2-dim projections
  cmiContrast = best2DimProjection(subspace, data, permutation);

  // remaining dimensions
  std::vector<int> remainingDimensions = Rcpp::as<std::vector<int>>(subspace);
  remainingDimensions.erase(std::remove_if(remainingDimensions.begin(),
                                           remainingDimensions.end(),
                                           [permutation](int i) {return (i == permutation[0] or i == permutation[1]);}
                                   ),remainingDimensions.end());

  // add remaining dimensions to permutation
  while(remainingDimensions.size() > 0){
    cmiContrast += addDimToPermutation(permutation, remainingDimensions);
    remainingDimensions.erase(std::remove(remainingDimensions.begin(),
                                          remainingDimensions.end(),
                                          permutation[permutation.size()-1]),remainingDimensions.end());
   }
   return cmiContrast;
 }






