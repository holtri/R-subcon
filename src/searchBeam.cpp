#include <Rcpp.h>
#include <queue>
#include <algorithm>
#include <iterator>
#include "searchBeam.h"
using namespace Rcpp;

bool operator<(const Subspace& a, const Subspace& b) {
  return a.contrast < b.contrast;
}

bool operator>(const Subspace& a, const Subspace& b) {
  return a.contrast > b.contrast;
}

std::ostream& operator<<(std::ostream& os, const Subspace& subspace) {
  os << "subspace: [";
  for (const auto& i: subspace.space){
    os << i << " ";
  }
  os << "] contrast: " << subspace.contrast << std::endl;
  return os;
}

bool AscendingComp::operator()(const Subspace& a, const Subspace& b) {
    return a > b;
  };

std::vector< std::vector<int> > subspaceVector(std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> pq){
  std::vector< std::vector<int> > subspaceVector;
  while (!pq.empty()){
    subspaceVector.push_back(pq.top().space);
    pq.pop();
  }
  return subspaceVector;
}

std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>
  pushFixedSize(std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>& pq,
                Subspace s,
                unsigned int k){
    if(pq.size() < k){
      pq.push(s);
    }else{
      if(pq.top() < s){
        pq.pop();
        pq.push(s);
      }
    }
    return pq;
  }
