#ifndef SUBSPACESEARCHALGORITHMS_H
#define SUBSPACESEARCHALGORITHMS_H

using namespace Rcpp;

std::vector<int> sortIndices(const NumericVector &input);

//' Greedy Maximum Deviation  Heuristic
//'
//' Constructs one deviation maximizing subspace for each dimension. The search
//' is based on the two dimensional deviations. For each dimension r, the
//' heuristic orders the two dimensional projections [r, s_i] by deviation, with
//' s_i being the conditional attribute. The search starts with the highest two
//' dimensional projection as the initial subspace. The next candidate to be
//' added to that subspace is the dimension that has the second highest
//' deviation. If the deviation for r increases by adding a dimension, the
//' subspace will be updated, else that dimension is discarded.
//'
//' @examples
//'
//' reference dimension: 1
//' 2-dim projections (ordered by deviation):
//' [1,3] deviation(1|3) = 0.6
//' [1,2] deviation(1|2) = 0.5
//' [1,5] deviation(1|5) = 0.4
//' [1,4] deviation(1|4) = 0.3
//'
//' Initial subspace: [1,3]
//'
//' add dimension 2
//' [1,2,3] deviation(1|2,3) = 0.65 -> increases the deviation for the reference dimension
//'
//' add dimension 5
//' [1,2,3,5] deviation(1|2,3) = 0.62 -> decreases the deviation for the reference dimension
//'
//' add dimension 5
//' [1,2,3,5] deviation(1|2,3,5) = 0.62 -> decreases the deviation for the reference dimension
//'
//' add dimension 4
//' [1,2,3,4] deviation(1|2,3,4) = 0.67 -> increases the deviation for the reference dimension
//'
//' Output space for reference dimension 1: [1,2,3,4]
//'
//'
//' @param indexMap Index for the data objects if ordered by dimension. Each
//'   entry of the vector contains the index to the initial data set. The index
//'   is starting with 1.
//' @param alpha Percentage of data objects to remain in the subspace slice
//'   (expected value).
//' @param numRuns number of random subspace slices used to estimate the
//'   deviation.
//' @return List of subspaces for each reference dimension.
//' @export
// [[Rcpp::export]]
std::vector<NumericVector> GMD(NumericMatrix indexMap, double alpha, int numRuns);

#endif
