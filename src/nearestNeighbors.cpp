#include "nearestNeighbors.h"

using namespace Rcpp;

Rcpp::List reverseNearestNeighborsC(arma::mat knn) {
  std::map<int, std::set<int> > rnn;
  std::vector<std::set <int> > result;

  for(arma::uword r=0; r < knn.n_rows; ++r){
    auto it_end = knn.end_row(r);
    for(auto it = knn.begin_row(r); it!= it_end; ++it){
      rnn[*it].insert(r + 1);
    }
  }

  for (const auto &s : rnn){
    result.push_back(s.second);
  }

  return wrap(result);
}
