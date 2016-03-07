
#' Quantified redundancy
#'
#' Removes redundant subspaces from the set as long as the final scoring yields
#' a higher AUC.
#'
#' @param lofactors list of LOF vectors for each subspace
#' @param label class label
#' @param combinationFun Function to combine LOF scores to final scoring.
#' @param scaleFun Function to scale LOF scores.
#'
#' @return List of \item{initialAUC}{AUC using the full set of subspaces.}
#'   \item{improvedAUC}{AUC using the remaining set of subspaces.}
#'   \item{numberInitialSpaces}{Number of initial subspaces.}
#'   \item{numberRemovedSpaces}{Number of remaining subspaces.}
#'   \item{removedSpaces}{Index of spaces removed from initial set.}
#'   \item{remainingSpaces}{Index of spaces remaining from initial set.}
#' @export
redundancyAUC <- function (lofactors, label, combinationFun, scaleFun) {

  scaledLOF <- lapply(lofactors, scaleFun)
  initialAUC <- unlist(ROCR::performance(ROCR::prediction(Reduce(combinationFun, scaledLOF), label), "auc")@y.values)
  improvedAUC <- initialAUC
  remove <- vector(mode = "numeric", length=0L)
  terminate <- F

  while(!terminate){

    terminate <- T
    for(i in 1:length(scaledLOF)){

      if(length(scaledLOF) > length(remove) + 1){
        auc <- unlist(ROCR::performance(ROCR::prediction(Reduce(combinationFun, scaledLOF[-cbind(remove,i)]), label), "auc")@y.values)
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
       "numberInitialSpaces" = length(lofactors),
       "numberRemovedSpaces" = length(remove),
       "removedSpaces" = sort(as.vector(remove)),
       "remainingSpaces" = sort(as.vector((1:length(scaledLOF))[-remove])))
}
