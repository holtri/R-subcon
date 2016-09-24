library(subcon)
context("Neighborhood queries")

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

test_that("test for empty rnn",{
  knn <- matrix(c(5,4,3,
                  1,4,5,
                  1,4,5,
                  5,3,1,
                  1,4,3), 5, 3, byrow = T)

  rnn <- reverseNearestNeighborsC(knn)
  rnn_expected <- list(c(2,3,4,5), vector(mode="numeric"), c(1,4,5), c(1,2,3,5), c(1,2,3,4))
  expect_equal(rnn, rnn_expected)
})
