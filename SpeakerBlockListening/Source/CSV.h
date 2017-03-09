/*
 ==============================================================================

 CSV.h
 Created: 8 Nov 2016 5:03:10pm
 Author:  Craig Henry

 ==============================================================================
 */

#ifndef CSV_H_INCLUDED
#define CSV_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <random>


bool readCSV(const String& fileName, double(*roundValues2D)[8]);

void writeIndividualCSV(const String& name, const String& otherFileName, double(*roundValues2D)[8], double (*speakerOrder)[8], String* roundValues, String* Comment, bool& read);

void attributeCSV(const String& name,const String& fileName, const int& roundNumber, const String* roundValues,const String* Comment);


void updateRowString(double (*roundValues2D)[8], double (*speakerOrder)[8], String* roundVales, String* Comment, const int& roundNumber);

void update2DArray(const double* sliderValues, double (*roundValues2D)[8], const int& roundNumber);

void createRandomOrder(double (*speakerOrder)[8]);

void speakerOrderCSV(double (*speakerOrderCSV)[8], const String& name, bool& read);

void writeCalibrationCSV(float* calibrationSettings);


#endif  // CSV_H_INCLUDED
