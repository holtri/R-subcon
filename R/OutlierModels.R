#' Local Outlier Factor
#'
#' Implements the LOF algorithm from the original publication, simplified by
#' assuming unique distances.
#'
#' @param data n x m matrix with n objects and m dimensions
#' @param k parameter for k-neighborhood
#'
#' @return Vector of local outlier factors
#'
#' @references Breunig, Markus M., Hans-Peter Kriegel, Raymond T. Ng, and Jörg
#'   Sander. 2000. LOF: Identifying Density-Based Local Outliers. SIGMOD Rec. 29
#'   (2). New York, NY, USA: ACM: 93–104.
#'
#' @export
LOF <- function (data, k) {
  distances <- FNN::get.knn(as.matrix(data), k)
  lrd <- reachability(distances$nn.index, distances$nn.dist, k)
  lofCalculation(lrd, distances$nn.index, k)
}
