/*
 * Unit tests
 */

#include <testthat.h>
#include "HiCSSearch.h"
#include "searchBeam.h"


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

  test_that("generate 2-dim projections 1"){
    std::vector<std::vector<int> > result = twoDimProjections(2);
    std::vector<int> expected = {1,2};
    expect_true(result.size() == 1);
    expect_true(result[0] == expected);
  }

  test_that("generate 2-dim projections 2 "){
    expect_true(twoDimProjections(5).size() == 10);
    expect_true(twoDimProjections(30).size() == (30*29/2));
  }

  test_that("Apriori merge on two-dim projections"){
    std::vector<std::vector<int> > initialSpaces = twoDimProjections(5);
    expect_true(initialSpaces.size() == 10);
    std::vector< std::vector<int> > result = aprioriMerge(initialSpaces);
    expect_true(result.size() == 10); //10 3-dim spaces
    result = aprioriMerge(result);
    expect_true(result.size() == 5); //5 4-dim spaces
    result = aprioriMerge(result);
    expect_true(result.size() == 1); //1 5-dim spaces
  }
}

context("constructResultList"){
  test_that("keep only 2 subspaces with highest contrast") {
    std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> searchBeam;
    searchBeam = std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>();

    Subspace a = {{1,2}, 0.2};
    Subspace b = {{3,4}, 0.4};
    Subspace c = {{5,6}, 0.5};

    pushFixedSize(searchBeam, a, 2);
    pushFixedSize(searchBeam, b, 2);
    pushFixedSize(searchBeam, c, 2);

    Rcpp::List resultList = constructResultList(searchBeam);


    std::vector<int> sa = {1,2};
    std::vector<int> sb = {3,4};
    std::vector<int> sc = {5,6};

    std::vector< std::vector<int> > subspaces = Rcpp::as< std::vector< std::vector<int> > >(resultList["subspaces"]);
    expect_true(subspaces[0] == sc);
    expect_true(subspaces[1] == sb);

    std::vector<double> expected = {0.5, 0.4};
    std::vector<double> contrast = Rcpp::as< std::vector<double> >(resultList["contrast"]);
    expect_true(expected == contrast);
  }
}

