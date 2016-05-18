#' Local Outlier Factor
#'
#' Implements the LOF algorithm from the original publication, simplified by
#' assuming unique distances.
#'
#' @param data n x m matrix with n objects and m dimensions
#' @param k parameter for k-neighborhood
#' @param mode "exact" mode uses individual k-distance and k-neighborhood for
#'   each object assuming non-unique distances. For exact mode, maxK needs to be
#'   specified. "simple" mode assuming unique distances.
#' @param maxK limits up to which k-neighborhood objects are considered if they
#'   have similar distances. A full search can be achieved by setting maxK to
#'   (nrow(data) - 1). Setting maxK too high can lead to poor runtime performance.
#'
#' @return Vector of local outlier factors
#'
#' @references Breunig, Markus M., Hans-Peter Kriegel, Raymond T. Ng, and Joerg
#'   Sander. 2000. LOF: Identifying Density-Based Local Outliers. SIGMOD Rec. 29
#'   (2). New York, NY, USA: ACM: p. 93 to 104.
#'
#' @export
LOF <- function (data, k, mode = "simple", maxK=NULL) {
  kDist <- c()
  switch(mode,
         simple = {
           distances <- FNN::get.knn(as.matrix(data), k)
           kDist$nrow <- 1:nrow(distances$nn.dist)
           kDist$maxkIdx <- rep(k, nrow(distances$nn.dist))
         },
         exact = {
           if(is.null(maxK)){
             stop("function argument maxK is missing")
           }
           if(!(maxK<nrow(data))){
             stop("maxK needs to be smaller than the number of data objects")
           }
           distances <- FNN::get.knn(as.matrix(data), maxK)
           distDT <- as.data.table(distances$nn.dist)
           kDist <- distDT[, .(maxkIdx = max(which(.SD <= .SD[[1,k]]))), by=1:nrow(distDT)]
         }
      )
  lrd <- reachability(distances$nn.index, distances$nn.dist, kDist$maxkIdx)
  lof <- lofCalculation(lrd, distances$nn.index, kDist$maxkIdx)
  switch(mode,
         simple = {
           return(lof)
           },
         exact = {
           return(list("lof "= lof, "maxkIdx" = kDist$maxkIdx))
         })
}
