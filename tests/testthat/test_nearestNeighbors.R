library(subcon)
context("Neighborhood queries")

test_that("1+1 is 2", {
  expect_equal(1+1, 2)
})

test_that("RNN matrix fits knn",{
  knn <- matrix(c(5,2,3,
                1,4,5,
                1,2,4,
                5,2,1,
                1,2,3), 5, 3, byrow = T)

  rnn <- reverseNearestNeighborsC(knn)
  rnn_expected <- list(c(2,3,4,5), c(1,3,4,5), c(1,5), c(2,3), c(1,2,4))
  expect_equal(rnn, rnn_expected)
})
