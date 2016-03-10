#ifndef SEARCHBEAM_H
#define SEARCHBEAM_H

using namespace Rcpp;

#include <queue>

struct Subspace{
  std::vector<int> space;
  double contrast;
};

struct AscendingComp{
  bool operator()(const Subspace& a, const Subspace& b);
};

bool operator<(const Subspace& a, const Subspace& b);

bool operator>(const Subspace& a, const Subspace& b);
std::ostream& operator<<(std::ostream& os, const Subspace& subspace);

std::vector< std::vector<int> > subspaceVector(std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> pq);

std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>
  pushFixedSize(std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>& pq,
                Subspace s,
                unsigned int k);

#endif
