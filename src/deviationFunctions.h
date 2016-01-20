#ifndef DEVIATIONFUNCTIONS_H
#define DEVIATIONFUNCTIONS_H

using namespace Rcpp;

//' Kolmogorov-Smirnov test
//'
//' Compares marginal and conditional probability density function for a given
//' subspace slice.
//'
//' @param indexSelection Logical vector that describes the subspace slice on
//'   the data set. A random subspace slice can be genearted by \code{\link{randomSubspaceSliceC}}.
//' @param indexMapReferenceAttribute Index vector for the data objects ordered by the
//'   reference dimension. Each entry of the vector contains the index to the
//'   initial data set. The index is starting with 1.
//' @return double Supremum of the absolute distance between the marginal and
//'   conditional distribution of the reference attribute.
//' @seealso \code{\link{randomSubspaceSliceC}}, \code{\link{sortedIndexMatrix}}
//' @export
// [[Rcpp::export]]
double KSTestC(LogicalVector indexSelection, NumericVector indexMapReferenceAttribute);

//' Random selection of a subspace slice
//'
//' Creates conditions for all dimensions of a given subspace and a given
//' reference dimension. Subspace selection is not done on the data set but
//' rather on the pre calculated index map.
//'
//' @param indexMap Index matrix (see \code{\link{sortedIndexMatrix}}) for the data objects if ordered by
//'   dimension. Each entry of the vector contains the index to the
//'   initial data set. The index is starting with 1.
//' @param subspace Numerical vector consisting of the subspace dimensions. Index for dimensions starts with 1.
//' @param alpha Percentage of data objects to remain in the subspace slice (expected value).
//' @param referenceDim Reference attribute upon which the conditions for the slice will be set.
//' @return Logical Vector indicating which data objects remain in the subspace slice.
//' @seealso \code{\link{sortedIndexMatrix}}
//' @export
// [[Rcpp::export]]
LogicalVector randomSubspaceSliceC(NumericMatrix indexMap, NumericVector subspace, double alpha, int referenceDim);

//' Deviation
//'
//' Average deviation over random subspace slices for a given reference
//' attribute.
//'
//' @param indexMap Index matrix (see \code{\link{sortedIndexMatrix}}) for the
//'   data objects if ordered by dimension. Each entry of the vector contains
//'   the index to the initial data set. The index is starting with 1.
//' @param subspace Numerical vector consisting of the subspace dimensions.
//'   Index for dimensions starts with 1.
//' @param alpha Percentage of data objects to remain in the subspace slice
//'   (expected value).
//' @param referenceDim Reference attribute upon which the conditions for the
//'   slice will be set.
//' @param numRuns number of random subspace slices used to estimate the
//'   deviation.
//' @return double, the deviation for the reference dimension.
//' @seealso \code{\link{sortedIndexMatrix}}
//' @export
// [[Rcpp::export]]
double averageDeviationC(NumericMatrix indexMap, NumericVector subspace, double alpha, int referenceDim, int numRuns);

// [[Rcpp::export]]
NumericVector deviationVectorC(NumericMatrix indexMap, NumericVector subspace, double alpha, int referenceDim, int numRuns);

// [[Rcpp::export]]
List deviationStatisticsC(NumericMatrix indexMap, double alpha, int numRuns);

//' HiCS contrast
//'
//' Calculates the HiCS contrast for a given subspace.
//'
//' @param indexMap Index for the data objects if ordered by dimension. Each
//'   entry of the vector contains the index to the initial data set. The index
//'   is starting with 1.
//' @param subspace Numerical vector consisting of the subspace dimensions.
//'   Index for dimensions starts with 1.
//' @param alpha Percentage of data objects to remain in the subspace slice
//'   (expected value).
//' @param numRuns number of random subspace slices used to estimate the
//'   deviation.
//' @return double, the HiCS contrast for the subspace.
//' @export
// [[Rcpp::export]]
double HiCSContrastC(NumericMatrix indexMap, NumericVector subspace, double alpha, int numRuns);

//' Deviation matrix
//'
//' Calculates the deviation for all 2-dimensional projections of the full
//' space.
//'
//' @param indexMap Index for the data objects if ordered by dimension. Each
//'   entry of the vector contains the index to the initial data set. The index
//'   is starting with 1.
//' @param alpha Percentage of data objects to remain in the subspace slice
//'   (expected value).
//' @param numRuns number of random subspace slices used to estimate the
//'   deviation.
//' @return NumericMatrix with deviations where the row is the reference
//'   attribute, column the conditional attribute of the 2-dimensional subspace.
//'   This matrix is asymmetric in general.
//' @export
// [[Rcpp::export]]
NumericMatrix deviationMatrixC(NumericMatrix indexMap, double alpha, int numRuns);

//' HiCS matrix
//'
//' Calculates the HiCS contrast for all 2-dimensional projections of the full
//' space.
//'
//' @param indexMap Index for the data objects if ordered by dimension. Each
//'   entry of the vector contains the index to the initial data set. The index
//'   is starting with 1.
//' @param alpha Percentage of data objects to remain in the subspace slice
//'   (expected value).
//' @param numRuns number of random subspace slices used to estimate the
//'   deviation.
//' @return Symmetric NumericMatrix with HiCS contrast that is the average
//'   deviation when the reference dimension is selected randomly.
//' @export
// [[Rcpp::export]]
NumericMatrix HiCSMatrixC(NumericMatrix indexMap, double alpha, int numRuns);

#endif
