/*
  ==============================================================================

    Calibration.cpp
    Created: 9 Feb 2017 11:07:21am
    Author:  Craig Henry

  ==============================================================================
*/

#include "Calibration.h"
int checkVolume(int amplitude)
{

    if(amplitude > 70)
    {
        return -1;
    }
    else if ( amplitude < 70)
    {
        return 1;
    }


    return 0;
}

bool calibrate(AudioTransportSource& transportSource, float currentGain, int currentPosition, float* calibrationSettings)
{

    while(checkVolume(1) == 1)
    {
        transportSource.setGain(currentGain += 0.1);
        //increasevolume

    }
    while(checkVolume(1) == -1)
    {
        transportSource.setGain(currentGain -= 0.1);
        //decreasevolume
    }

    if(checkVolume(1) == 0)
    {
        calibrationSettings[currentPosition] = currentGain;
        writeCalibrationCSV(calibrationSettings);
        return true;
    }
    else
    {
        return false;
    }

}
