/*
 * Unit tests
 */

#include <testthat.h>
#include "searchBeam.h"

context("pushFixedSize") {

  test_that("order 3 subspaces") {
    std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> searchBeam;
    searchBeam = std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>();

    Subspace a = {{1,2}, 0.2};
    Subspace b = {{3,4,5}, 0.4};
    Subspace c = {{6,7}, 0.3};
    pushFixedSize(searchBeam, a, 3);
    pushFixedSize(searchBeam, b, 3);
    pushFixedSize(searchBeam, c, 3);

    std::vector<int> expected = {1,2};
    expect_true(searchBeam.top().space == expected);
    searchBeam.pop();

    expected = {6,7};
    expect_true(searchBeam.top().space == expected);
    searchBeam.pop();

    expected = {3,4,5};
    expect_true(searchBeam.top().space == expected);
  }

  test_that("keep only 2 subspaces with highest contrast") {
    std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp> searchBeam;
    searchBeam = std::priority_queue<Subspace, std::vector<Subspace>, AscendingComp>();

    Subspace a = {{1,2}, 0.2};
    Subspace b = {{3,4,5}, 0.4};
    Subspace c = {{6,7}, 0.3};
    pushFixedSize(searchBeam, a, 2); //  keep only 2 subspaces with highest contrast
    pushFixedSize(searchBeam, b, 2);
    pushFixedSize(searchBeam, c, 2);

    std::vector<int> expected = {6,7};
    expect_true(searchBeam.top().space == expected);
    searchBeam.pop();

    expected = {3,4,5};
    expect_true(searchBeam.top().space == expected);
  }
}


