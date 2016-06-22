# R-subcon

[![Build Status](https://travis-ci.org/holtri/R-subcon.svg?branch=master)](https://travis-ci.org/holtri/R-subcon) [![Project Status: WIP - Initial development is in progress, but there has not yet been a stable, usable release suitable for the public.](http://www.repostatus.org/badges/latest/wip.svg)](http://www.repostatus.org/#wip)

This project makes subspace search based outlier detection easily accessible as an R package. (For Python users, see [Using the package in Python](#using-the-package-in-python))

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
combinedScoreAUC(combinationFun = sumCombination, scores = lofactors, label = label)

# Redundancy measure
redundancyAUC(lofactors, label, combinationFun = sumCombination, scaleFun = identity)
```

##Using the package in Python

R-packages can be used in Python with rpy2 which is an interface to R running embedded in a Python process. (http://rpy2.bitbucket.org/). It allows to create R objects in Python, which we can be manipulated both inside the R objects with R syntax or outside with Python syntax.

Here is a quick start guide to get the subcon package running in Python.


```Python
# Importing Python packages
import numpy as np
import scipy as sp
import pandas as pd
from rpy2.robjects.packages import importr
import rpy2.robjects as ro

# Importing R packages
importr('data.table')
importr('subcon')

# Creating R variables
ro.r("""dt <- data.table(replicate(10,runif(100)))
label <- c(rep(0, 90), rep(1, 10))
indexMatrix <- sortedIndexMatrix(dt)""")

# Working with R inside the objects
ro.r('averageDeviationC(indexMap = indexMatrix, subspace = c(1,2), alpha = 0.1, referenceDim = 1, numRuns = 100)')
ro.r('HiCSContrastC(indexMap = indexMatrix, subspace = c(1,2), alpha = 0.1, numRuns = 100)')
```

Note that the variables defined inside ro.r() exist as Python variables:
```
>>>type(label)
rpy2.robjects.vectors.FloatVector
```
Also you can easily convert them to native Python variables:
```
>>>plabel=np.array(label)
>>>type(plabel)
numpy.ndarray
```
or
```
>>>pydf = com.load_data('dt')
>>>type(pydf)
pandas.core.frame.DataFrame
```


##References

The package contains functions to search for subspaces in high dimensional data bases. The contrast defintion used in the code is based on [HiCS - High Contrast Subspaces for Density Based Outlier Ranking][1].

Implementation of HiCS and deviation functions is inspired by the [nim implementation of the HiCS search][2].

[1]: http://www.ipd.uni-karlsruhe.de/~muellere/publications/ICDE2012.pdf 
[2]: https://github.com/bluenote10/HiCS
