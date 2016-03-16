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
#'   \item{numberRemovedSpaces}{Number of remaining subspaces.}
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
       "removedSpaces" = sort(as.vector(remove)),
       "remainingSpaces" = sort(as.vector((1:length(scaledLOF))[-remove])))
}
