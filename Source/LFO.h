/*
  ==============================================================================

    LFO.h
    Created: 6 Nov 2022 8:08:31pm
    Author:  Phillip Short

  ==============================================================================
*/

#include <JuceHeader.h>

class LFO {
public:
    LFO();
    ~LFO();
    
    void updateFrequency(float _frequency, float _sampRate);
    float getWaveType(int _waveType);

private:
    
    double t { 0.0 };
    float sampRate;
    float frequency;
    int waveType;
    float outPut { 0 };
    int reset;
    juce::SmoothedValue<float> smoothWave;
    
};
