#include <Rcpp.h>
#include "searchBeam.h"
#include "deviationFunctions.h"

using namespace Rcpp;

void print(const std::vector<int> &vec){
  for (const auto& i: vec){
    Rcpp::Rcout << i << " ";
  }
  Rcpp::Rcout << std::endl;
}


bool containsProjection(std::set<std::vector<int> > subspaces, std::vector<int> candidate){
  for(unsigned int i=0; i < candidate.size(); i++){
    std::vector<int> tmp = candidate;
    tmp.erase(tmp.begin()+i);
    if(std::find(subspaces.begin(), subspaces.end(), tmp) == subspaces.end()) {
      return false;
    }
  }
  return true;
}

std::vector< std::vector<int> > aprioriMerge(std::vector< std::vector<int> > initialSpaces){
  typedef  std::map<std::vector<int>, std::vector<int> > MyMapType;
  MyMapType m;

  std::set<std::vector<int> > subspaces;
  for (auto it = begin (initialSpaces); it != end (initialSpaces); ++it) {

    std::vector<int> sub = *it;
    subspaces.insert(sub);

    std::vector<int> prefix(sub.begin(), sub.end() -1);
    int suffix = sub[sub.size()-1];

    std::vector<int> value {suffix};
    std::pair<MyMapType::iterator, bool> result = m.insert(std::make_pair(prefix,value));
    if(!result.second) {
      m[prefix].push_back(suffix);
    }
  }
  std::vector<std::vector<int> > candidates;
  for (auto it=m.begin(); it!=m.end(); ++it){

    std::vector<int> prefix = it->first;
    std::vector<int> sfx = m[prefix];

    for(auto i = sfx.begin(); i != sfx.end()-1; ++i){
      for(auto j = i+1; j != sfx.end(); ++j){
        std::vector<int> c = prefix;
        c.push_back(*i);
        c.push_back(*j);
        if(containsProjection(subspaces,c)){
          candidates.push_back(c);
        }
      }
    }
  }
  return candidates;
}

void updateSearchBeam(std::vector< std::vector<int> > candidates,
                 std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>& searchBeam,
                 std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>& outputBeam,
                 int topkSearch,
                 int topkOutput,
                 NumericMatrix indexMap,
                 double alpha,
                 int numRuns){
  for(auto s : candidates){
    double contrast = HiCSContrastC(indexMap, wrap(s), alpha, numRuns);
    pushFixedSize(searchBeam, {s, contrast}, topkSearch);
    pushFixedSize(outputBeam, {s, contrast}, topkOutput);
  }
}

std::vector< std::vector<int> > twoDimProjections(int dimensionality){
  std::vector< std::vector<int> > twoDimProjections;
  for(auto i = 1; i <= dimensionality; i++){
    for(auto j = i+1; j <= dimensionality; j++){
      twoDimProjections.push_back({i, j});
    }
  }
  return twoDimProjections;
}

// [[Rcpp::export]]
List HiCSSearch(NumericMatrix indexMap, double alpha, int numRuns){
  Rcpp::List outputSpaces;
  int topkSearch = 500;
  int topkOutput = 100;

  std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> searchBeam;
  std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> outputBeam;
  std::vector< std::vector<int> > candidates;

  candidates = twoDimProjections(indexMap.ncol());

  while(candidates.size()>0){
    Rcpp::Rcout << "remaining candidates: " << candidates.size() << std::endl;
    searchBeam = std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>();
    updateSearchBeam(candidates, searchBeam, outputBeam, topkSearch, topkOutput, indexMap, alpha, numRuns);
    candidates = aprioriMerge(subspaceVector(searchBeam));
  }

  std::vector< std::vector<int> > tmp = subspaceVector(outputBeam);
  for (auto it = begin (tmp); it != end (tmp); ++it) {
    outputSpaces.push_back(*it);
  }

  return outputSpaces;
}

