/*
  ==============================================================================

    RoundsandSliders.h
    Created: 17 Nov 2016 2:21:12pm
    Author:  Craig Henry

  ==============================================================================
*/

#ifndef ROUNDSANDSLIDERS_H_INCLUDED
#define ROUNDSANDSLIDERS_H_INCLUDED

#include "CSV.h"

enum roundSettings
{
    RoundOne,
    RoundTwo,
    RoundThree,
    RoundFour,
    RoundFive,
    RoundSix,
    RoundSeven,
    RoundEight
};

void changeRound(roundSettings& currentRound,double (*roundValues2D)[9],  int& roundNumber);




#endif  // ROUNDSANDSLIDERS_H_INCLUDED
