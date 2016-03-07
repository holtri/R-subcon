# R-subcon
R package for subspace search

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

#Greedy maximum heuristic

GMD(indexMap = indexMatrix, alpha = 0.1, numRuns = 100)

```

##References

The package contains functions to search for subspaces in high dimensional data bases. The contrast defintion used in the code is based on [HiCS - High Contrast Subspaces for Density Based Outlier Ranking][1].

Implementation of HiCS and deviation functions is inspired by the [nim implementation of the HiCS search][2].

[1]: http://www.ipd.uni-karlsruhe.de/~muellere/publications/ICDE2012.pdf 
[2]: https://github.com/bluenote10/HiCS
