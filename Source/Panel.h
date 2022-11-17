/*
  ==============================================================================

    Panel.h
    Created: 2 Nov 2022 5:00:20pm
    Author:  Phillip Short

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Btn.h"

//==============================================================================
/*
*/
class Panel  : public juce::Component
{
public:
    Panel();
    ~Panel() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent &event) override;
    
    Btn sineBtn;
    Btn triBtn;
    Btn sawBtn;
    Btn squareBtn;
    Btn noiseBtn;

private:

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Panel)
};
