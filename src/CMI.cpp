#include "CMI.h"
#include <Rcpp.h>
#include <algorithm>    // std::sort

using namespace Rcpp;



double calcHce(std::vector<double> space) {
  double hce = 0;

// Sortierung
  std::sort (space.begin(), space.end());

//Hce-Berechnung
  for(unsigned int i=0; i<space.size(); i++){
    hce <- hce + ((space[i+1] - space[i]) * ((i+1)/space.size()) * log((i+1)/space.size()));
  }
    return -hce;
}

//
// double calcCHce(std::vector<double> space, int refDim, int conDim, int numClust){
//   double chce = 0;
// // Clustering des "space": todo
//
// // Pro Cluster hce berechnen
//   for (unsigned int i=0; i<numClust; i++){
//     chce = chce + cluster.size()/space.size() * calcHce(); // todo: vervollstaendigen
//   }
//
//
//   return chce;
// }

/*
 conditionalhCE <- function(data, referenceDim, conditionalDim, numClusters = 1){
 ce <- 0
 clusters <- kmeans(data[, conditionalDim, with=F], numClusters)
 print(referenceDim)
 for(c in 1:numClusters){
# hCE(data) Aufruf fuer alle Cluster: nimmt pro Cl. die Dim.(aus IMportparameter) und Cluster
 ce <- ce + clusters$size[c]/nrow(data) * hCE(data[[referenceDim]][clusters$cluster==c])
 }
 ce
 }
*/

// double cmi(std::vector<double> subspace){
//
//   //start with 2-dim projections
//   for (int i=0; i<subspace.size(); i++){
//     for(int j=0; j<subspace.size(); j++){
//       // alle Subspace-2-er-Kombis bilden:
//       if(i!=j){
//           // todo: Kontrast berechnen: hce(Xj) - chce(Xj | Xi)
//       }
//   }
//
//
// }

/*
# find starting 2-dim projection
initialSubspace <- list(sub = c(), contrast = 0)
  for(i in 1:length(subspace)){ # interate over indices of subspace dimensions
    for(j in 1:length(subspace)){
      if(i!=j){
        tmp <- hCE(dt[[ subspace[i] ]]) - conditionalhCE(dt, referenceDim = subspace[i], conditionalDim = subspace[j], numClusters = 10)
# print(list(sub = c(subspace[i], subspace[j]), contrast = tmp))
        if(tmp > initialSubspace$contrast){
          initialSubspace = list(sub = c(subspace[i], subspace[j]), contrast = tmp)
        }
      }
    }
  }
 */
