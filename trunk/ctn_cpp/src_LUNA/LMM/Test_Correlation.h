#pragma once

#include "Correlation.h"

//-----------------------------------------------------------------------------------------------
//
//                                             Test 
//
//-----------------------------------------------------------------------------------------------
void test_Robonato2_Correlation  (size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType);
void test_Robonato3_Correlation  (size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType);
void test_Shosemaker2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType);
void test_Shosemaker3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType);
void test_XY_beta_Correlation    (size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType);
void test_PCAEigenVectorRobonato2(size_t fullRank, size_t reducedRank); // to print out eigenVector. // don't care about the reduced rank.
void test_PCAEigenVectorXY_beta  (size_t fullRank, size_t reducedRank); // to print out eigenVector. // don't care about the reduced rank.
void testCorrelation();


