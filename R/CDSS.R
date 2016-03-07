
#' Cumulated Deviation Subspace Search (CDSS)
#'
#' Directly mines high quality subspaces from two-dimensional projections only.
#'
#' @param dm deviation matrix, see \code{\link{deviationMatrixC}}
#'
#' @return List of subspaces
#' @export
CDSS <- function(dm, tau){
  dimensions <- 1:ncol(dm)
  outputSpaces <- list()

  referenceVector <- 1:ncol(dm)

  while(length(dimensions) > 0){
    terminationCriterion <- FALSE
    sumInterest <- rep(0,ncol(dm))
    subspace <- vector(mode="numeric", length=0L)

    idx <- runif(1, min = 0, max = length(dimensions))
    dim <- dimensions[ceiling(idx)]

    while(!terminationCriterion){

      subspace <- append(subspace, dim)
      dimensions <- dimensions[dimensions!=dim]

      sumInterest <- sumInterest + madStd(dm[,dim])

      if(max(sumInterest[-subspace]) < median(sumInterest) + tau * length(subspace) * IQR(sumInterest)){
        terminationCriterion <- TRUE
        outputSpaces <- c(outputSpaces, list(subspace))
      }
      else{
        tmp <- referenceVector[-subspace]
        dim <- tmp[which.max(sumInterest[-subspace])]
      }
    }
  }
  outputSpaces
}



