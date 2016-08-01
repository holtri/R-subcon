#include <Rcpp.h>

context("Tests about CMI")


  test_that("calcHCE", {
    expect_equal(calcHce(c(1.0,2.0,9.0,5.0,455.0)), 82.26504)
  })

# cmi-Signature: Rcpp::NumericVector subspace, Rcpp::NumericMatrix data
  test_that("CMI", {
    #data<-Rcpp::NumericMatrix(2,3)
    matr <- matrix(1:10, nrow=5, ncol=2)
    #NumericMatrix nm = Rcpp::as(matr)
    expect_equal(cmi(c(3,4,5,6),matr), 82.26504)
  })




