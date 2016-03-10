#ifndef HICSSEARCH_H
#define HICSSEARCH_H

using namespace Rcpp;

//' HiCS Search
//'
//' HiCS search following the apriori search scheme. The implementation is
//' according to the original publication and inspired by the nim-implemtation
//' \url{https://github.com/bluenote10/HiCS}.
//'
//' @param Index for the data objects if ordered by dimension. Each
//'   entry of the vector contains the index to the initial data set. The index
//'   is starting with 1.
//' @param alpha Percentage of data objects to remain in the subspace slice
//'   (expected value).
//' @param numRuns number of random subspace slices used to estimate the
//'   subspace contrast.
//' @param topkSearch top-k contrast subspaces in the search beam.
//' @param topkOutput top-k contrast subspaces in the final output.
//'
//'@return List of
//'\item{subspaces}{List of top-k final subspaces ordered by contrast.}
//'\item{contrast}{Vector of contrast values of the top-k final subspaces.}
//' @seealso \code{\link{HiCSContrastC}}, \code{\link{sortedIndexMatrix}}
//'
//' @references Keller, Fabian, Emmanuel Muller, and Klemens Bohm. 2012. HiCS:
//'   High Contrast Subspaces for Density-Based Outlier Ranking. In 2012 IEEE
//'   28th International Conference on Data Engineering, 1037 – 48. IEEE.
//'
//' @export
// [[Rcpp::export]]
List HiCSSearch(NumericMatrix indexMap, double alpha, int numRuns, int topkSearch, int topkOutput);

#endif
