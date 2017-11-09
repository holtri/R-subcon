#include <Rcpp.h>
#include <algorithm>
#include "searchBeam.h"
#include "deviationFunctions.h"

using namespace Rcpp;

void print(const std::vector<int> &vec){
  for (const auto& i: vec){
    Rcpp::Rcout << i << " ";
  }
  Rcpp::Rcout << std::endl;
}

std::string toString(const std::vector<int> &vec){
  std::stringstream ss;
  for (const auto& i: vec){
    ss << i << " ";
  }
  return ss.str();
}

bool containsProjection(std::set<std::set<int> > subspaces, std::vector<int> candidate){
  for(unsigned int i=0; i < candidate.size(); i++){
    std::vector<int> tmp = candidate;
    tmp.erase(tmp.begin()+i);
    std::set<int> tmpset(tmp.begin(),tmp.end());
    if(std::find(subspaces.begin(), subspaces.end(), tmpset) == subspaces.end()) {
      return false;
    }
  }
  return true;
}

std::vector< std::vector<int> > aprioriMerge(std::vector< std::vector<int> > initialSpaces){
  typedef  std::map<std::vector<int>, std::vector<int> > PrefixMap;
  PrefixMap m;

  std::set<std::set<int> > subspaces;
  for (auto it = begin (initialSpaces); it != end (initialSpaces); ++it) {

    std::vector<int> sub = *it;
    std::set<int> subtmp(sub.begin(), sub.end());
    subspaces.insert(subtmp);

    std::vector<int> prefix(sub.begin(), sub.end() -1);
    int suffix = sub[sub.size()-1];

    std::vector<int> value {suffix};
    std::pair<PrefixMap::iterator, bool> result = m.insert(std::make_pair(prefix,value));
    if(!result.second) {
      m[prefix].push_back(suffix);
    }
  }
  std::vector<std::vector<int> > candidates;
  for (auto it=m.begin(); it!=m.end(); ++it){

    std::vector<int> prefix = it->first;
    std::vector<int> sfx = m[prefix];
    std::sort(sfx.begin(), sfx.end());
    for(auto i = sfx.begin(); i != sfx.end()-1; ++i){
      for(auto j = i+1; j != sfx.end(); ++j){
        std::vector<int> c = prefix;
        c.push_back(*i);
        c.push_back(*j);
        std::sort(c.begin(), c.end()); // keep order for apriori
        // Rcpp::Rcout << "prefix: " << toString(prefix) << "suffix i:" << *i << " suffix j: " << *j <<std::endl;
        if(containsProjection(subspaces, c)){
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

Rcpp::List constructResultList(std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> outputBeam){
  Rcpp::List result;

  std::vector< std::vector<int> > tmp = subspaceVector(outputBeam);
  Rcpp::List outputSpaces;
  for (auto it = tmp.rbegin(); it != tmp.rend(); ++it) {
    outputSpaces.push_back(*it);
  }

  result["subspaces"] = outputSpaces;
  std::vector<double> contrast = contrastVector(outputBeam);
  std::reverse(contrast.begin(), contrast.end());
  result["contrast"] = contrast;

  return result;
}

List HiCSSearch(NumericMatrix indexMap, double alpha, int numRuns, int topkSearch, int topkOutput, int seed = -1){

  if(seed>0){
    srand(seed);
  }

  std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> searchBeam;
  std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> outputBeam;
  std::vector< std::vector<int> > candidates;

  candidates = twoDimProjections(indexMap.ncol());
  int dim = 2;
  while(candidates.size()>0){
    searchBeam = std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>();
    updateSearchBeam(candidates, searchBeam, outputBeam, topkSearch, topkOutput, indexMap, alpha, numRuns);
    Rcpp::Rcout << "number of " << dim <<  "-dim candidates: " << subspaceVector(searchBeam).size() << std::endl;
    candidates = aprioriMerge(subspaceVector(searchBeam));
    dim ++;
  }

  return constructResultList(outputBeam);
}

