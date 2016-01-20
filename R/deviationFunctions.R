
deviation <- function(indexMap, subspace, referenceDim, alpha, numRuns){
  .Deprecated("deviationC")
  res <- 0
  for(i in 1:numRuns){
    res = res + KSTest(randomSubspaceSlice(indexMap, subspace, alpha, referenceDim), indexMap[,referenceDim, with=F][[1]])
  }
  res/numRuns
}

KSTest <- function(indexSelection, indexMapReferenceAttribute){
  .Deprecated("KSTestC")
  cumDistSubspace <- 0
  cumDistOriginal <- 0
  maxDistance <- 0
  numRemaining <- sum(indexSelection,na.rm = TRUE)
  numTotal <- length(indexSelection)

  for(i in 1:length(indexMapReferenceAttribute)){
    cumDistOriginal = (i+1)/numTotal
    if(indexSelection[indexMapReferenceAttribute[i]]){
      cumDistSubspace = cumDistSubspace + 1/numRemaining
    }
    maxDistance <- max(maxDistance, abs(cumDistSubspace - cumDistOriginal))
  }
  maxDistance
}

#' Index map for data set
#'
#' The index map allows to create subspace slices without working on the underlying data set but rather on the ordered index.
#'
#' @param dt data.table
#'
#' @return A data.table is returned that consists of indexes for the order of each column. E.g. a data table with the first column (0.3,0.5, 0.1) would get an index of (2,3,1), i.e. the elements sorted by (2,3,1) are in increasing order. The index starts with 1.
#' @export
sortedIndex <- function(dt){
  res <- copy(dt)
  res[,idx:=.I]
  l <- list()
  for (j in names(dt)){
    setorderv(res,c(j))
    l[[j]] <- res[,.(idx)][[1]]
  }
  data.table(do.call(cbind, l))
}

#' Index matrix for data set
#'
#' This is a wrapper for \code{\link{sortedIndex}}.
#'
#' @param dt data.table
#'
#' @return \code{\link{sortedIndex}} converted to a matrix
#' @export
sortedIndexMatrix <- function(dt){
  res <- as.matrix(sortedIndex(dt))
  colnames(res) <- colnames(dt)
  res
}

randomSubspaceSlice <- function(indexMap, subspace, alpha, referenceDim){
  .Deprecated("randomSubspaceSliceC")
  sliceSize <- ceiling(nrow(indexMap) * (alpha ^ (1/(length(subspace)-1))))
  selectionAll <- rep(T,nrow(indexMap))

  for(dim in subspace){
    if(dim != referenceDim){
      l <- ceiling(runif(1,1,nrow(indexMap)-sliceSize))
      r <- l + sliceSize
      selectionAll[indexMap[-(l:r), dim, with=F][[1]]] <- F
    }
  }
  selectionAll
}
