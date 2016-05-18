
is.binary <- function(x){
  identical(as.vector(x),as.numeric(as.logical(x)))
}

on_failure(is.binary) <- function(call, env){
  paste0(deparse(call$x), " is not binary")
}

#' Area under the ROC curve for combined scoring
#'
#' Wrapper to calculate the AUC of a combined scoring.
#'
#' @param combinationFun Function to combine LOF scores to final scoring.
#' @param scores List of scoring vectors for each subspace.
#' @param label Class label.
#'
#' @return Area under the ROC curve
combinedScoreAUC <- function(combinationFun, scores, label){
  unlist(ROCR::performance(ROCR::prediction(Reduce(combinationFun, scores), label), "auc")@y.values)
}

redundancy <- function(auc, maxauc){
  (maxauc - auc)/(maxauc-0.5)
}

#' Quantified redundancy
#'
#' Removes redundant subspaces from the set as long as the final scoring yields
#' a higher AUC.
#'
#' @param scores List of scoring vectors for each subspace.
#' @param label Class label.
#' @param combinationFun Function to combine scores to final scoring.
#' @param scaleFun Function to scale scores.
#'
#' @return List of \item{initialAUC}{AUC using the full set of subspaces.}
#'   \item{improvedAUC}{AUC using the remaining set of subspaces.}
#'   \item{numberInitialSpaces}{Number of initial subspaces.}
#'   \item{redundancy}{(maxAUC - initialAUC) / (maxAUC - 0.5).}
#'   \item{numberRemovedSpaces}{Number of removed subspaces.}
#'   \item{removedSpaces}{Index of spaces removed from initial set.}
#'   \item{remainingSpaces}{Index of spaces remaining from initial set.}
#' @export
redundancyAUC <- function (scores, label, combinationFun, scaleFun) {

  scaledLOF <- lapply(scores, scaleFun)
  initialAUC <- combinedScoreAUC(combinationFun, scores=scaledLOF, label)
  improvedAUC <- initialAUC
  remove <- vector(mode = "numeric", length=0L)
  terminate <- F

  while(!terminate){

    terminate <- T
    for(i in 1:length(scaledLOF)){

      if(length(scaledLOF) > length(remove) + 1){
        auc <- combinedScoreAUC(combinationFun, scores = scaledLOF[-cbind(remove,i)], label)
        auc <- ifelse(auc < 0.5, 1 - auc, auc)

        if(auc > improvedAUC){
          remove <- cbind(remove,i)
          improvedAUC <- auc
          terminate <- F
        }
      }
    }
  }

  list("initialAUC" = initialAUC,
       "maximumAUC" = improvedAUC,
       "redundancy" = redundancy(initialAUC, improvedAUC),
       "numberInitialSpaces" = length(scores),
       "numberRemovedSpaces" = length(remove),
       "numberRemainingSpaces" = length(scores) - length(remove),
       "removedSpaces" = sort(as.vector(remove)),
       "remainingSpaces" = sort(as.vector((1:length(scaledLOF))[-remove])))
}

#' Precision@n performance metric
#'
#' See referenced paper by Campos et al. for explanation.
#'
#' @param trueLabel Binary vector with known Labels from training data, 1
#'   indicating an outlier and 0 a regular object
#' @param scores Vector of score values
#' @param n number of top elements to consider
#' @param adjusted if TRUE, precision@n is adjusted for chance to allow
#'   comparison between data sets that consist of different proportions of
#'   outliers.
#'
#' @return Numeric precision@n value
#'
#' @references Guilherme O. Campos, Arthur Zimek, Joerg Sander, Ricardo J. G. B.
#'   Campello, Barbora Micenkova, Erich Schubert, Ira Assent, Michael E. Houle.
#'   2016. 'On the Evaluation of Unsupervised Outlier Detection: Measures,
#'   Datasets, and an Empirical Study.' Data Mining and Knowledge Discovery,
#'   January, p. 1 to 37.
#'
#' @export
precisionAtN <- function(trueLabel, scores, n, adjusted = FALSE){
  assert_that(length(trueLabel) == length(scores))
  assert_that(is.binary(trueLabel))
  assert_that(n <= length(trueLabel))

  idx <- sort.int(scores, index.return = T, decreasing = T)
  prec <- sum(label[idx$ix][1:n])/n
  if(adjusted){
    numOutliers <- sum(trueLabel)
    N <- length(trueLabel)
    prec <- (prec - numOutliers/N )/ (min(1, numOutliers/n) - (numOutliers/N))
    prec <- max(prec,0)
  }
  prec
}

#' Average Precision performance metric
#'
#' See referenced paper by Campos et al. for explanation.
#'
#' @param trueLabel Binary vector with known Labels from training data, 1
#'   indicating an outlier and 0 a regular object
#' @param scores Vector of score values
#' @param adjusted adjusted if TRUE, the average precision is adjusted for
#'   chance to allow comparison between data sets that consist of different
#'   proportions of outliers.
#'
#' @return Numeric Average Precision value
#'
#' @references Guilherme O. Campos, Arthur Zimek, Joerg Sander, Ricardo J. G. B.
#'   Campello, Barbora Micenkova, Erich Schubert, Ira Assent, Michael E. Houle.
#'   2016. 'On the Evaluation of Unsupervised Outlier Detection: Measures,
#'   Datasets, and an Empirical Study.' Data Mining and Knowledge Discovery,
#'   January, p. 1 to 37.
#'
#' @export
averagePrecision <- function(trueLabel, scores, adjusted = FALSE){
  precSum <- 0
  for(k in seq_along(trueLabel)[trueLabel==1]){
    precSum <- precSum + precisionAtN(trueLabel, scores, k)
  }
  precSum / sum(trueLabel)
}
