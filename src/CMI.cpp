#include "CMI.h"
#include <Rcpp.h>
#include <algorithm>    // std::sort
#include <vector>
#include <Rcpp.h>
//#include "RcppMLPACK.h"
using namespace Rcpp;
//using namespace mlpack::kmeans;

/*** R
# This is R code
#List mlkmeans(const arma::mat& data, const int& clusters)
#age <- c(17, 30, 30, 25, 23, 21)
#data<-matrix(age, nrow=3, ncol=2, byrow=FALSE)
# list<-mlpack::kmeans::mlkmeans(data, 3)
#print('Test')
# print(result)
*/


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
struct Projection
{
  unsigned int refDim;
  std::vector<unsigned int> condDim;
  double contrast;
};

// [[Rcpp::export]]
 double cmi(Rcpp::NumericVector subspace, Rcpp::NumericMatrix data){
   double cmiContrast = 0.0;
   double tmpContrast = 0.0;
   double tmp = 0.0;
   Projection p2dim;
   p2dim.contrast = 0.0;
   Projection pNextdim;
   pNextdim.contrast = 0.0;
   
   std::cout<<"subspace.size:"<<subspace.size()<<std::endl;

   
   //start with 2-dim projections
   for (unsigned int i=0; i<subspace.size(); i++){
     for(unsigned int j=0; j<subspace.size(); j++){
       if(i!=j){
           // todo: Kontrast berechnen: tmpContrast =    1.) hce(Xi) - chce(Xi | Xj) oder 2.) hce(Xj) - chce(Xj | Xi) ???
            // 1: Implement. in CMI.R und 2: Formel aus Paper (?)
           // hCE(dt[[ subspace[i] ]]) in R: liefert einen Vektor einer Spalte (der subspace[i].-Spalte) des dt, 
           //     d.h. hCE wird nur fuer diese Spalte berechnet, richtig?
           //j.th column of data is copied to a numeric vector
           NumericVector attr = data( _, j);
           //conversion to std::vector
           std::vector<double> dat = Rcpp::as<std::vector<double> >(attr);

           // todo: when chce is complete: add it to calcul.:
           tmpContrast = calcHce(dat); //Content from all: data[*][j]

          
           
           if(tmpContrast > p2dim.contrast){
             //store contrast
             
             p2dim.refDim = subspace[i];
             std::vector<unsigned int> cd;
             cd.push_back(subspace[j]);
             p2dim.condDim = cd;
             p2dim.contrast = tmpContrast;
            
           }
       }
     }
  }
 
   cmiContrast += p2dim.contrast;

   // todo: subspace kürzen: Komplement bilden: Subspace ohne die Dim. mit höchstem Kontrast
   // in R: subspace <- ... -which(subspace %in% initialSubspace$sub)
  
  std::vector<double> subspaceVec = Rcpp::as<std::vector<double> >(subspace);
  for (std::vector<double>::iterator it=subspaceVec.begin();it<subspaceVec.end();it++)
  {
    if ( *it == p2dim.refDim) {
      subspaceVec.erase(it);
    } 
     else {
      for (unsigned int i=0; i<2; i++) 
      if ( *it == p2dim.condDim[i]) {
        subspaceVec.erase(it);
      }  
    }
  }
   
   while(subspaceVec.size() > 0){        // while still dimensions left
     for(unsigned int i=0; i<subspaceVec.size(); i++) {
       
       /*tmp = hCE(dt[[ subspace[i] ]]) - conditionalhCE( dt,
                                                        referenceDim = subspace[i],
                                                        conditionalDim = initialSubspace$sub,
                                                       numClusters = 10)
        */ 
       // todo: vervollstaendigen:
       //tmp = calcHce(data[subspace[i]]);

       if(tmp > pNextdim.contrast){
          pNextdim.refDim = subspace[i];
          std::list<unsigned int> cdn;
          //cdn.push_back(p2dim.condDim);
          
          pNextdim.condDim = p2dim.condDim;
         // = list(sub = c(subspace[i], initialSubspace$sub), 
          pNextdim.contrast = tmp;
       }
     }
       cmiContrast += pNextdim.contrast;
       p2dim = pNextdim;
       
       /*
       totalContrast <- totalContrast + nextSubspace$contrast
       initialSubspace <- nextSubspace //# update subspace
       nextSubspace <- list(sub = c(), contrast = 0) //# we only take the best dimension level wise
       subspace <- subspace[-which(subspace %in% initialSubspace$sub)] // remove added dimension from remaining dimensions
      */
   }     
   return cmiContrast;
 }


