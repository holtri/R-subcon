#include "CMI.h"
#include <Rcpp.h>
#include <algorithm>    
#include <vector>
#include <Rcpp.h>
using namespace Rcpp;




//--------------------------------------------------------------------------------------
// HCE
//--------------------------------------------------------------------------------------
// [[Rcpp::export]]
double calcHce(std::vector<double> space) {
  double hce = 0.0000;

  std::sort (space.begin(), space.end());


//Hce-Calculation
  for(unsigned int i=0; i<space.size()-1; ++i){

    double zv = double(i+1.0)/double(space.size());
    double logar = zv * log(zv);
    hce = hce + ((space[i+1] - space[i]) * logar);
  }

      return -hce;
}


//--------------------------------------------------------------------------------------
//  cHce
//--------------------------------------------------------------------------------------
 double calcCHce(std::vector<double> data, int refDim, int conDim, unsigned int numClust){

   double chce = 0.0;
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
           
           //i.th column of data is copied to a numeric vector
           NumericVector attr = data( _, i);
           //conversion to std::vector
           std::vector<double> dat = Rcpp::as<std::vector<double> >(attr);

           // todo: when chce is complete: add it to calcul.:
           tmpContrast = calcHce(dat); //Content from all: data[*][i]

          
           
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
    // todo: vector statt struct (konvention: letztes Element = refDim)
    if ( *it == p2dim.refDim or *it == p2dim.condDim[0]) {
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
          pNextdim.refDim = subspaceVec[i];
          
          // add refDim and condDim from old vector to the new one
          pNextdim.condDim.push_back(p2dim.refDim);
          pNextdim.condDim.insert(pNextdim.condDim.end(), p2dim.condDim.begin(), p2dim.condDim.end());
         
          pNextdim.contrast = tmp;
       }
     }
       cmiContrast += pNextdim.contrast;
       p2dim = pNextdim;
       // todo: pNextdim initialisieren und subspaceVec kuerzen
       
       /*
       totalContrast <- totalContrast + nextSubspace$contrast
       initialSubspace <- nextSubspace //# update subspace
       nextSubspace <- list(sub = c(), contrast = 0) //# we only take the best dimension level wise
       subspace <- subspace[-which(subspace %in% initialSubspace$sub)] // remove added dimension from remaining dimensions
      */
   }     
   return cmiContrast;
 }


