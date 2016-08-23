// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// calcHce
double calcHce(std::vector<double> dataVector);
RcppExport SEXP subcon_calcHce(SEXP dataVectorSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< std::vector<double> >::type dataVector(dataVectorSEXP);
    __result = Rcpp::wrap(calcHce(dataVector));
    return __result;
END_RCPP
}
// cmi
double cmi(Rcpp::NumericVector subspace, Rcpp::NumericMatrix data);
RcppExport SEXP subcon_cmi(SEXP subspaceSEXP, SEXP dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type subspace(subspaceSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type data(dataSEXP);
    __result = Rcpp::wrap(cmi(subspace, data));
    return __result;
END_RCPP
}
// KSTestC
double KSTestC(LogicalVector indexSelection, NumericVector indexMapReferenceAttribute);
RcppExport SEXP subcon_KSTestC(SEXP indexSelectionSEXP, SEXP indexMapReferenceAttributeSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< LogicalVector >::type indexSelection(indexSelectionSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type indexMapReferenceAttribute(indexMapReferenceAttributeSEXP);
    __result = Rcpp::wrap(KSTestC(indexSelection, indexMapReferenceAttribute));
    return __result;
END_RCPP
}
// randomSubspaceSliceC
LogicalVector randomSubspaceSliceC(NumericMatrix indexMap, NumericVector subspace, double alpha, int referenceDim);
RcppExport SEXP subcon_randomSubspaceSliceC(SEXP indexMapSEXP, SEXP subspaceSEXP, SEXP alphaSEXP, SEXP referenceDimSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type indexMap(indexMapSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type subspace(subspaceSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type referenceDim(referenceDimSEXP);
    __result = Rcpp::wrap(randomSubspaceSliceC(indexMap, subspace, alpha, referenceDim));
    return __result;
END_RCPP
}
// averageDeviationC
double averageDeviationC(NumericMatrix indexMap, NumericVector subspace, double alpha, int referenceDim, int numRuns);
RcppExport SEXP subcon_averageDeviationC(SEXP indexMapSEXP, SEXP subspaceSEXP, SEXP alphaSEXP, SEXP referenceDimSEXP, SEXP numRunsSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type indexMap(indexMapSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type subspace(subspaceSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type referenceDim(referenceDimSEXP);
    Rcpp::traits::input_parameter< int >::type numRuns(numRunsSEXP);
    __result = Rcpp::wrap(averageDeviationC(indexMap, subspace, alpha, referenceDim, numRuns));
    return __result;
END_RCPP
}
// deviationVectorC
NumericVector deviationVectorC(NumericMatrix indexMap, NumericVector subspace, double alpha, int referenceDim, int numRuns);
RcppExport SEXP subcon_deviationVectorC(SEXP indexMapSEXP, SEXP subspaceSEXP, SEXP alphaSEXP, SEXP referenceDimSEXP, SEXP numRunsSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type indexMap(indexMapSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type subspace(subspaceSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type referenceDim(referenceDimSEXP);
    Rcpp::traits::input_parameter< int >::type numRuns(numRunsSEXP);
    __result = Rcpp::wrap(deviationVectorC(indexMap, subspace, alpha, referenceDim, numRuns));
    return __result;
END_RCPP
}
// deviationStatisticsC
List deviationStatisticsC(NumericMatrix indexMap, double alpha, int numRuns);
RcppExport SEXP subcon_deviationStatisticsC(SEXP indexMapSEXP, SEXP alphaSEXP, SEXP numRunsSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type indexMap(indexMapSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type numRuns(numRunsSEXP);
    __result = Rcpp::wrap(deviationStatisticsC(indexMap, alpha, numRuns));
    return __result;
END_RCPP
}
// HiCSContrastC
double HiCSContrastC(NumericMatrix indexMap, NumericVector subspace, double alpha, int numRuns);
RcppExport SEXP subcon_HiCSContrastC(SEXP indexMapSEXP, SEXP subspaceSEXP, SEXP alphaSEXP, SEXP numRunsSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type indexMap(indexMapSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type subspace(subspaceSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type numRuns(numRunsSEXP);
    __result = Rcpp::wrap(HiCSContrastC(indexMap, subspace, alpha, numRuns));
    return __result;
END_RCPP
}
// deviationMatrixC
NumericMatrix deviationMatrixC(NumericMatrix indexMap, double alpha, int numRuns);
RcppExport SEXP subcon_deviationMatrixC(SEXP indexMapSEXP, SEXP alphaSEXP, SEXP numRunsSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type indexMap(indexMapSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type numRuns(numRunsSEXP);
    __result = Rcpp::wrap(deviationMatrixC(indexMap, alpha, numRuns));
    return __result;
END_RCPP
}
// HiCSMatrixC
NumericMatrix HiCSMatrixC(NumericMatrix indexMap, double alpha, int numRuns);
RcppExport SEXP subcon_HiCSMatrixC(SEXP indexMapSEXP, SEXP alphaSEXP, SEXP numRunsSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type indexMap(indexMapSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type numRuns(numRunsSEXP);
    __result = Rcpp::wrap(HiCSMatrixC(indexMap, alpha, numRuns));
    return __result;
END_RCPP
}
// HiCSSearch
List HiCSSearch(NumericMatrix indexMap, double alpha, int numRuns, int topkSearch, int topkOutput);
RcppExport SEXP subcon_HiCSSearch(SEXP indexMapSEXP, SEXP alphaSEXP, SEXP numRunsSEXP, SEXP topkSearchSEXP, SEXP topkOutputSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type indexMap(indexMapSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type numRuns(numRunsSEXP);
    Rcpp::traits::input_parameter< int >::type topkSearch(topkSearchSEXP);
    Rcpp::traits::input_parameter< int >::type topkOutput(topkOutputSEXP);
    __result = Rcpp::wrap(HiCSSearch(indexMap, alpha, numRuns, topkSearch, topkOutput));
    return __result;
END_RCPP
}
// reachability
NumericVector reachability(NumericMatrix knnIndex, NumericMatrix knnDistance, NumericVector maxkIdx);
RcppExport SEXP subcon_reachability(SEXP knnIndexSEXP, SEXP knnDistanceSEXP, SEXP maxkIdxSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type knnIndex(knnIndexSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type knnDistance(knnDistanceSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type maxkIdx(maxkIdxSEXP);
    __result = Rcpp::wrap(reachability(knnIndex, knnDistance, maxkIdx));
    return __result;
END_RCPP
}
// lofCalculation
NumericVector lofCalculation(NumericVector lrd, NumericMatrix knnIndex, NumericVector maxkIdx);
RcppExport SEXP subcon_lofCalculation(SEXP lrdSEXP, SEXP knnIndexSEXP, SEXP maxkIdxSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericVector >::type lrd(lrdSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type knnIndex(knnIndexSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type maxkIdx(maxkIdxSEXP);
    __result = Rcpp::wrap(lofCalculation(lrd, knnIndex, maxkIdx));
    return __result;
END_RCPP
}
// GMD
std::vector<NumericVector> GMD(NumericMatrix indexMap, double alpha, int numRuns);
RcppExport SEXP subcon_GMD(SEXP indexMapSEXP, SEXP alphaSEXP, SEXP numRunsSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< NumericMatrix >::type indexMap(indexMapSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< int >::type numRuns(numRunsSEXP);
    __result = Rcpp::wrap(GMD(indexMap, alpha, numRuns));
    return __result;
END_RCPP
}
