madStd <- function(x){
  medianAbsDev <- mad(x, constant=1)
  if(medianAbsDev > 0){
    abs(x - median(x)) / medianAbsDev
  }else{
    x
  }
}

#' Gamma Normalization
#'
#' Fits a gamma distribution with the moment estimators for shape and scale
#' parameter and normalizes the outlier scores as suggested by Kriegel et al.
#'
#' @param x outlier scores to normalize
#'
#' @references Kriegel, Hans-Peter, Peer Kroger, Erich Schubert, and Arthur
#'   Zimek. 2011. Interpreting and Unifying Outlier Scores. In Proceedings of
#'   the 2011 SIAM International Conference on Data Mining, p. 13 - 24.
#'
#' @return normalized outlier scores
#' @export
gammaNorm <- function(x){
  mu <- mean(x)
  s <- sd(x)
  k <- mu^2/s^2
  teta <- s^2 / mu
  mucdf <- pgamma(mu, shape = k, scale = teta)

  sapply(x, function(a){
    max(0, (pgamma(a, shape = k, scale = teta) - mucdf) / (1-mucdf))
  })
}

#' Sum Combination Function
#'
#' Wrapper to sum of two lists
#'
#' @param x,y list of values
#'
#' @return list containing the pairwise sum
#' @export
#'
sumCombination <- function(x,y) unlist(x) + unlist(y)

#' Max Combination Function
#'
#' Wrapper to take maximum of two lists
#'
#' @param x,y list of values
#'
#' @return list containing the pairwise maximum
#' @export
maxCombination <- function(x,y) pmax(unlist(x), unlist(y))
