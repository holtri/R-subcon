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
 double calcCHce(std::vector<double> data, std::vector<double> dim, unsigned int numClust){

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



//--------------------------------------------------------------------------------------
// CMI
//--------------------------------------------------------------------------------------

// [[Rcpp::export]]
 double cmi(Rcpp::NumericVector subspace, Rcpp::NumericMatrix data){
   double cmiContrast = 0.0;
   double tmpContrast = 0.0;
   double tmp = 0.0;
   std::vector<unsigned int> p2dim, pNextdim;
   double p2dimContrast = 0.0;
   double pNextdimContrast = 0.0;
   unsigned int nextDim;   
  
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

          
           
           if(tmpContrast > p2dimContrast){
             //store contrast & best Projection
             p2dim.push_back(subspace[j]); //condDim
             p2dim.push_back(subspace[i]); //refDim
             p2dimContrast = tmpContrast;
            
           }
       }
     }
  }
 
   cmiContrast += p2dimContrast;

   // build subspace without highest 2-Dim.
  std::vector<double> subspaceVec = Rcpp::as<std::vector<double> >(subspace);
  for (std::vector<double>::iterator it=subspaceVec.begin();it<subspaceVec.end();it++)
  {
    if ( *it == p2dim[0] or *it == p2dim[1]) {
      subspaceVec.erase(it);
    } 
  }
   
   // continue with greater projections
   pNextdim = p2dim;
   
   while(subspaceVec.size() > 0){        // while still dimensions left
     pNextdimContrast = 0.0;
     
     for(unsigned int i=0; i<subspaceVec.size(); i++) {
      
       p2dim.push_back(subspaceVec[i]);
       
       /*tmp = hCE(dt[[ subspace[i] ]]) - conditionalhCE( dt,
                                                        referenceDim = subspace[i],
                                                        conditionalDim = initialSubspace$sub,
                                                       numClusters = 10)
        */ 
       // todo: vervollstaendigen: tmp = hce("subspaceVec[i]") - chce("p2dim")
       //tmp = calcHce(data[subspace[i]]);

       if(tmp > pNextdimContrast){
        
          nextDim = subspaceVec[i];
          pNextdimContrast = tmp;
       }
       p2dim.pop_back();
     }
       cmiContrast += pNextdimContrast;
       pNextdim.push_back(nextDim);
       p2dim = pNextdim; 
       // shorten subspace
       for (std::vector<double>::iterator it=subspaceVec.begin();it<subspaceVec.end();it++)
       {
         if ( *it == nextDim) {
           subspaceVec.erase(it);
         } 
       }
   }     
   return cmiContrast;
 }


