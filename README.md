# R-subcon

This project makes subspace search based outlier detection easily accessible as an R package.

So far the repository contains some of the latest subspace search approaches such as GMD, CDSS and HiCS and a fast implementation of the well known LOF algorithm for the evaluation of subspace search results. Also functionality around score combination, scaling and redundancy evaluation is implemented. Most of the key functions are written in c++ to significantly increase performance over plain R.

This package is an early stage and under development. 

## Installation

#####Prerequisites

Install RTools https://cran.r-project.org/bin/windows/Rtools/

Install devtools https://github.com/hadley/devtools

#####Package installation from github
```R
#as the package uses Rcpp with c++11, you might be required to set compiler options manually
Sys.setenv("PKG_CXXFLAGS"="-std=c++0x")

library(devtools)
devtools::install_github("holtri/R-subcon")
```

## Quick start

Let's get started with a quick running example.

#####Overview of functionality

```R
?subcon
```

#####Deviation measures

```R
library(data.table)
library(subcon)

#generate sample data
dt <- data.table(replicate(10,runif(100)))
label <- c(rep(0, 90), rep(1, 10))

#pre-process data into index map for efficient deviation calculation
indexMatrix <- sortedIndexMatrix(dt)

#deviation
averageDeviationC(indexMap = indexMatrix, subspace = c(1,2), alpha = 0.1, referenceDim = 1, numRuns = 100)
HiCSContrastC(indexMap = indexMatrix, subspace = c(1,2), alpha = 0.1, numRuns = 100)

#all two dimensional projections

deviationMatrixC(indexMap = indexMatrix, alpha = 0.1, numRuns = 100)
HiCSMatrixC(indexMap = indexMatrix, alpha = 0.1, numRuns = 100)
```

#####Subspace search algorithms

```R

#HiCS Search
hicsSearchResult <- HiCSSearch(indexMap = indexMatrix, alpha = 0.1, numRuns = 100, topkSearch = 500, topkOutput = 100)
outputSpaces <- hicsSearchResult$subspaces

#Greedy Maximum Deviation (GMD)
outputSpaces <- GMD(indexMap = indexMatrix, alpha = 0.1, numRuns = 100)

#Cumulated Deviation Subspace Search (CDSS)
dm <- deviationMatrixC(sortedIndexMatrix(dt), alpha = 0.1, numRuns = 100)
outputSpaces <- CDSS(dm, tau=1)

```

#####Subspace search evaluation
```R
# Calculate LOF score for subspaces
lofactors <- lapply(outputSpaces, function(x) {
  LOF(dt[,unlist(x), with=F], k=10)
})

# Scaling of LOF scores
scaledlofactors <- lapply(lofactors, gammaNorm)

# AUC for combined scoring
combinedScoreAUC(sumCombination, scores = lofactors, label = label)

# Redundancy measure
redundancyAUC(lofactors, label, sumCombination, scaleFun = identity)
```

##References

The package contains functions to search for subspaces in high dimensional data bases. The contrast defintion used in the code is based on [HiCS - High Contrast Subspaces for Density Based Outlier Ranking][1].

Implementation of HiCS and deviation functions is inspired by the [nim implementation of the HiCS search][2].

[1]: http://www.ipd.uni-karlsruhe.de/~muellere/publications/ICDE2012.pdf 
[2]: https://github.com/bluenote10/HiCS
