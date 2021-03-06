% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{reachability}
\alias{reachability}
\title{LOF reachability distance}
\usage{
reachability(knnIndex, knnDistance, maxkIdx)
}
\arguments{
\item{knnIndex}{n x k Matrix of knn indices}

\item{knnDistance}{n x k Matrix of knn distances}

\item{vector}{indices for the k-neighborhood}
}
\value{
vector of local reachability densities
}
\description{
Calculates reachability distance for all objects
}
