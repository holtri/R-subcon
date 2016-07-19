#include "CMI.h"
#include <Rcpp.h>
#include <algorithm>    // std::sort
#include <vector>
using namespace Rcpp;



double calcHce(std::vector<double> space) {
  double hce = 0.0000;

// Sort
  std::sort (space.begin(), space.end());

// Print after sort
  std::vector<double>::const_iterator i;
  std::cout<<"Vektor nach Sortierung:"<<std::endl;
  for(i=space.begin(); i!=space.end(); ++i){
    std::cout<<(*i)<<std::endl;
  }



//Hce-Calculation
  for(unsigned int i=0; i<space.size()-1; ++i){
   // hce = hce + ((space[i+1] - space[i]) * ((i+1)/space.size()) * log((i+1)/space.size()));
  //  std::cout<<hce<<std::endl;


    double zv = double(i+1.0)/double(space.size());
    std::cout<<"zv:"<<zv<<std::endl;
    double logar = zv * log(zv);
    std::cout<<"logar:"<<logar<<std::endl;


    hce = hce + ((space[i+1] - space[i]) * logar);

  //  std::cout<<"(i+1):"<<(i+1)<<", space.size():"<<space.size()<<std::endl;
    std::cout<<"hce:"<<hce<<std::endl;
    std::cout<<"i:"<<i<<std::endl;
  //  std::cout<<"space[i]:"<<space[i]<<std::endl;
  }

      return -hce;
}

// [[Rcpp::export]]
double testHce(){
    std::vector<double> s;
  //  s.push_back(999);
    s.push_back(1.0);
    s.push_back(2.0);
    s.push_back(9.0);
    s.push_back(5.0);
    s.push_back(455.0);


    double Hces = calcHce(s);
    return Hces;
}

// calc cHce
 double calcCHce(std::vector<double> space, int refDim, int conDim, unsigned int numClust){
  
   double chce = 0;
   // Clustering of "space": todo
  
  /*** R
    clusters <- kmeans(space[, conDim, with=F], numClust)
  */
  

// Pro Cluster hce berechnen
   for (unsigned int i=0; i<numClust; i++){
//     chce = chce + cluster.size()/space.size() * calcHce(); // todo: vervollstaendigen
   }
//
//
   return chce;
 }


// [[Rcpp::export]]
double testcHce(){
  
  std::vector<double> s;
  

  s.push_back(1.0);
  s.push_back(2.0);
  s.push_back(5.0);
  s.push_back(9.0);
  s.push_back(455.0);
  s.push_back(999);
  double cHce = calcCHce(s,3,4,2);
  return cHce;
}  
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
