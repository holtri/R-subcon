#ifndef CMI_H
#define CMI_H

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


//
//   // calculate cond. hce
//   double calcCHce(std::vector<double> space, int refDim, int conDim, int numClust);
//   //data, referenceDim, conditionalDim, numClusters = 1)
//
//   // calculate cmi
//   double cmi(std::vector<double> subspace);

#endif
