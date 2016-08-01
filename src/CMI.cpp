#include "CMI.h"
#include <Rcpp.h>
#include <algorithm>    // std::sort
#include <vector>
using namespace Rcpp;

//--------------------------------------------------------------------------------------
// HCE
//--------------------------------------------------------------------------------------
// [[Rcpp::export]]
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

    double zv = double(i+1.0)/double(space.size());
    std::cout<<"zv:"<<zv<<std::endl;
    double logar = zv * log(zv);
    std::cout<<"logar:"<<logar<<std::endl;


    hce = hce + ((space[i+1] - space[i]) * logar);

    std::cout<<"hce:"<<hce<<std::endl;
    std::cout<<"i:"<<i<<std::endl;

  }

      return -hce;
}

/*
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
*/

//--------------------------------------------------------------------------------------
//  cHce
//--------------------------------------------------------------------------------------
 double calcCHce(std::vector<double> data, int refDim, int conDim, unsigned int numClust){

   double chce = 0;
   // Clustering of "data": todo


// Pro Cluster hce berechnen
   for (unsigned int i=0; i<numClust; i++){
//     chce = chce + cluster.size()/data.size() * calcHce(); // todo: vervollstaendigen
   }
//
//
   return chce;
 }

/*
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
*/

/*
double conditionalHce(NumericMatrix x, ...){
  kmeans(x)
}
 */


//--------------------------------------------------------------------------------------
// CMI
//--------------------------------------------------------------------------------------
 double cmi(Rcpp::NumericVector subspace, Rcpp::NumericMatrix data){
    double cmiContrast = 0.0;
   double tmpContrast = 0.0;

 std::cout<<"subspace.size:"<<subspace.size()<<std::endl;

   //start with 2-dim projections
   for (unsigned int i=0; i<subspace.size(); i++){
     for(unsigned int j=0; j<subspace.size(); j++){
       if(i!=j){
           // todo: Kontrast berechnen: tmpContrast = 1.) hce(Xi) - chce(Xi | Xj) oder 2.) hce(Xj) - chce(Xj | Xi) ???

           // hCE(dt[[ subspace[i] ]]) in R: liefert einen Vektor einer Spalte (der subspace[i].-Spalte) des dt, d.h. hCE wird nur fuer diese Spalte berechnet, richtig?
           //j.th column of data is copied to a numeric vector
           NumericVector attr = data( _, j);
           //conversion to std::vector
           std::vector<double> dat = Rcpp::as<std::vector<double> >(attr);

           tmpContrast = calcHce(dat); //Content from all: data[*][j]
       }
     }
  }
   // todo:

   cmiContrast += tmpContrast;


   return cmiContrast;
 }

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


 // [[Rcpp::export]]
 double testcMI(){

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

