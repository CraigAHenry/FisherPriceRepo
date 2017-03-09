/*
  ==============================================================================

    Calibration.h
    Created: 9 Feb 2017 11:07:21am
    Author:  Craig Henry

  ==============================================================================
*/

#ifndef CALIBRATION_H_INCLUDED
#define CALIBRATION_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CSV.h"



int checkVolume(int amplitude);

void calibrate(AudioTransportSource& transportSource);



#endif  // CALIBRATION_H_INCLUDED
