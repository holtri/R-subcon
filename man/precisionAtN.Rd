% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/Evaluation.R
\name{precisionAtN}
\alias{precisionAtN}
\title{Precision@n performance metric}
\usage{
precisionAtN(trueLabel, scores, n, adjusted = FALSE)
}
\arguments{
\item{trueLabel}{Binary vector with known Labels from training data, 1
indicating an outlier and 0 a regular object}

\item{scores}{Vector of score values}

\item{n}{number of top elements to consider}

\item{adjusted}{if TRUE, precision@n is adjusted for chance to allow
comparison between data sets that consist of different proportions of
outliers.}
}
\value{
Numeric precision@n value
}
\description{
See referenced paper by Campos et al. for explanation.
}
\references{
Guilherme O. Campos, Arthur Zimek, Joerg Sander, Ricardo J. G. B.
  Campello, Barbora Micenkova, Erich Schubert, Ira Assent, Michael E. Houle.
  2016. 'On the Evaluation of Unsupervised Outlier Detection: Measures,
  Datasets, and an Empirical Study.' Data Mining and Knowledge Discovery,
  January, p. 1 to 37.
}
