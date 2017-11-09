/*
 * Unit tests
 */

#include <testthat.h>
#include "HiCSSearch.h"

context("containsProjection") {

  test_that("Unordered candidate contained d-1 projections") {
    std::set<std::set<int> > subspaces = {{1,2}, {1,3}, {2,3}};
    std::vector<int> candidate = {1,3,2};
    expect_true(containsProjection(subspaces, candidate));
  }

  test_that("Candidate with extra dimension not included in d-1 projections") {
    std::set<std::set<int> > subspaces = {{1,2}, {1,3}, {2,3}};
    std::vector<int> candidate = {1,3,4};
    expect_false(containsProjection(subspaces, candidate));
  }

  test_that("Ordered candidate contained in unordered d-1 projections") {
    std::set<std::set<int> > subspaces = {{2,1}, {3,1}, {3,2}};
    std::vector<int> candidate = {1,2,3};
    expect_true(containsProjection(subspaces, candidate));
  }
}

context("aprioriMerge") {
  test_that("2-dim Apriori Merge 1"){
    std::vector<std::vector<int> > initialSpaces = {{1,2}, {1,3}, {2,3}};
    std::vector< std::vector<int> > result = aprioriMerge(initialSpaces);
    expect_true(result.size() ==1);
    std::vector<int> expected = {1,2,3};
    expect_true(result[0] == expected);
  }

  test_that("2-dim Apriori Merge 2"){
    std::vector<std::vector<int> > initialSpaces = {{1,2}, {1,3}, {2,3}, {2,4}};
    std::vector< std::vector<int> > result = aprioriMerge(initialSpaces);
    expect_true(result.size() ==1);
    std::vector<int> expected = {1,2,3};
    expect_true(result[0] == expected);
  }

  test_that("2-dim Apriori Merge 3"){
    std::vector<std::vector<int> > initialSpaces = {{1,2}, {1,3}, {2,4}};
    std::vector< std::vector<int> > result = aprioriMerge(initialSpaces);
    expect_true(result.size() == 0);
  }

  test_that("2-dim Apriori Merge 4"){
    std::vector<std::vector<int> > initialSpaces = {{1,3}, {1,2}, {2,3}}; // order independece of suffixes
    std::vector< std::vector<int> > result = aprioriMerge(initialSpaces);
    expect_true(result.size() ==1);

    std::vector<int> expected = {1,3,2}; // candidates must be ordered
    expect_false(result[0] == expected);

    expected = {1,2,3};
    expect_true(result[0] == expected);
  }

  test_that("3-dim Apriori Merge 1"){
    std::vector<std::vector<int> > initialSpaces = {{1,2,3}, {1,2,4}, {2,3,4}, {1,3,4}};
    std::vector< std::vector<int> > result = aprioriMerge(initialSpaces);
    expect_true(result.size() == 1);
    std::vector<int> expected = {1,2,3,4};
    expect_true(result[0] == expected);
  }

  test_that("3-dim Apriori Merge 2"){
    std::vector<std::vector<int> > initialSpaces = {{1,2,3}, {1,2}, {2,3,4}, {1,3,4}};
    std::vector< std::vector<int> > result = aprioriMerge(initialSpaces);
    expect_true(result.size() == 0);
  }
}
