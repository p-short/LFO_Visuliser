/*
  ==============================================================================

    LFO.cpp
    Created: 6 Nov 2022 8:08:31pm
    Author:  Phillip Short

  ==============================================================================
*/

#include "LFO.h"
#include "Noise.h"
#include <cmath>

LFO::LFO() {}

LFO::~LFO () {}

void LFO::updateFrequency(float _frequency, float _sampRate)
{
    frequency = _frequency;
    sampRate = _sampRate;
}

float LFO::getWaveType(int _waveType)
{
    waveType = _waveType;
    reset = (int)sampRate / frequency;
    t += frequency / sampRate;
    
    double fullPeriodTime = frequency / frequency;
    double halfPeriodTime = fullPeriodTime / 2.0;
    double localTime = fmod(t, fullPeriodTime);
    double value = localTime / fullPeriodTime;
    double res = 0.0;
    
    switch (waveType) {
        case 0:  { //sine
            outPut = sin(2 * M_PI * t);
            break;
        }
            
        case 1: { //tri
            if (value < 0.25)
            {
                res = value * 4;
            }
            else if (value < 0.75)
            {
                res = 2.0 - (value * 4.0);
            }
            else
            {
                res = value * 4 - 4.0;
            }
            outPut = res;
            break;
        }
            
        case 2: { //saw
            outPut = ((localTime / fullPeriodTime) * 2 - 1.0);
            break;
        }
            
        case 3: { //square
            outPut = (localTime < halfPeriodTime) ? 1 : -1;
            break;
        }
            
        case 4: { //noise
            outPut = perlinNoise(t);
            break;
        }
    }
    //reset t to zero so it dosent tend to infinity over time
    if (t >= reset) { t = 0; }
        
    //smooths out the output so its not so jaggy
    smoothWave.reset(sampRate, 1 / frequency);
    smoothWave.setTargetValue(outPut);
    return smoothWave.getNextValue();;
}
