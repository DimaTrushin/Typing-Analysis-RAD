//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitApproximation.h"
//---------------------------------------------------------------------------
//#include <vcl.h>
namespace NSApplication {
namespace NSKernel {
/*
class CApproximationTester {
public:
  CApproximationTester()
    : Text(L"Approximation Test:\n") {
    CSpeedApproximation Approximation;
    std::vector<double> Data;
    Data.push_back(400.0);
    Approximation.setApproximation(Data);
    //printApproximationBaseInformation(Approximation);
    evaluateTest(Approximation, Approximation);
    evaluateUniformTest(Approximation, Approximation);
    ShowMessage(Text.c_str());
  }
private:
  template<class TApproximation>
  void printApproximationBaseInformation(const TApproximation& Approximation) {
    Text += L"ApproximationBase:\n";
    Text += L"evaluateHistogram(400, 50) = ";
    Text += Approximation.evaluateHistogram(400.0, 50.0);
    Text += L"\nNumberOfSamples = ";
    Text += Approximation.getNumberOfSamples();
    Text += L"\nNumberOfSamplesLessThan(400) = ";
    Text += Approximation.getNumberOfSamplesLessThan(400);
    Text += L"\nIsEmpty = ";
    Text += Approximation.isEmpty();
    Text += L"\nDiscreteMean = ";
    Text += Approximation.getDiscreteMean();
    Text += L"\nDiscreteDeviation = ";
    Text += Approximation.getDiscreteDeviation();
    Text += L"\n";
  }
  void evaluateTest(const CSpeedApproximation& Approximation,
                    const CSpeedApproximation& ApproximationT) {
    Text += L"EvaluateTest:\n";
    double difference0 = 0.0;
    for (int index = 0; index < 2500; ++index) {
      double argument = static_cast<double>(index);
      difference0 += std::fabs(Approximation.evaluate0(argument) -
                              ApproximationT.evaluate<0>(argument));
    }
    Text += L"Difference0 = ";
    Text += difference0;
    double difference1 = 0.0;
    for (int index = 0; index < 2500; ++index) {
      double argument = static_cast<double>(index);
      difference1 += std::fabs(Approximation.evaluate1(argument) -
                              ApproximationT.evaluate<1>(argument));
    }
    Text += L"\nDifference1 = ";
    Text += difference1;
    double difference2 = 0.0;
    for (int index = 0; index < 2500; ++index) {
      double argument = static_cast<double>(index);
      difference2 += std::fabs(Approximation.evaluate2(argument) -
                              ApproximationT.evaluate<2>(argument));
    }
    Text += L"\nDifference2 = ";
    Text += difference2;
    double difference3 = 0.0;
    for (int index = 0; index < 2500; ++index) {
      double argument = static_cast<double>(index);
      difference3 += std::fabs(Approximation.evaluate3(argument) -
                              ApproximationT.evaluate<3>(argument));
    }
    Text += L"\nDifference3 = ";
    Text += difference3;
    Text += L"\n";
  }
  void evaluateUniformTest( const CSpeedApproximation& Approximation,
                            const CSpeedApproximation& ApproximationT) {
    Text += L"EvaluateUniformTest:\n";
    double difference0 = 0.0;
    for (int index = 0; index < 2500; ++index) {
      double argument = static_cast<double>(index);
      difference0 += std::fabs(Approximation.evaluateUniform0(argument) -
                              ApproximationT.evaluateUniform<0>(argument));
    }
    Text += L"Difference0 = ";
    Text += difference0;
    double difference1 = 0.0;
    for (int index = 0; index < 2500; ++index) {
      double argument = static_cast<double>(index);
      difference1 += std::fabs(Approximation.evaluateUniform1(argument) -
                              ApproximationT.evaluateUniform<1>(argument));
    }
    Text += L"\nDifference1 = ";
    Text += difference1;
    double difference2 = 0.0;
    for (int index = 0; index < 2500; ++index) {
      double argument = static_cast<double>(index);
      difference2 += std::fabs(Approximation.evaluateUniform2(argument) -
                              ApproximationT.evaluateUniform<2>(argument));
    }
    Text += L"\nDifference2 = ";
    Text += difference2;
    double difference3 = 0.0;
    for (int index = 0; index < 2500; ++index) {
      double argument = static_cast<double>(index);
      difference3 += std::fabs(Approximation.evaluateUniform3(argument) -
                              ApproximationT.evaluateUniform<3>(argument));
    }
    Text += L"\nDifference3 = ";
    Text += difference3;
    Text += L"\n";
  }

  UnicodeString Text;
};
CApproximationTester ApproximationTester;*/
//---------------------------------------------------------------------------
// Definition of CSpeedDefinitions
//---------------------------------------------------------------------------

double CSpeedDefinitions::getDeviation(double mean) const {
  return std::sqrt(mean) * kDeviationCoefficient;
}
//---------------------------------------------------------------------------

CSpeedDefinitions::CDoublePair
              CSpeedDefinitions::getChunkOfValues(double argument,
                                                  double chunk) const {
  if (!(argument > 0.0))
    return CDoublePair(0.0, 0.0);
  double chunkNumber = std::floor(directRescale(argument) / chunk);
  double minimalBound = reverseRescale(chunkNumber * chunk);
  double maximalBound = reverseRescale((chunkNumber + 1.0) * chunk);
  return CDoublePair(minimalBound, maximalBound);
}
//---------------------------------------------------------------------------

double CSpeedDefinitions::directRescale(double argument) const {
  return kDeviationCoefficient * std::sqrt(argument);
}
//---------------------------------------------------------------------------

double CSpeedDefinitions::reverseRescale(double argument) const {
  return  (argument / kDeviationCoefficient) *
          (argument / kDeviationCoefficient);
}
//---------------------------------------------------------------------------
// Global Functions
//---------------------------------------------------------------------------

double StandardDistribution(double argument) {
  double result = argument * argument;
  result /= -2.0;
  result = std::exp(result);
  result /= std::sqrt(2.0 * M_PI);
  return result;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)

