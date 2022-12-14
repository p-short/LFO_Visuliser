/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Panel.h"


//==============================================================================
/**
*/
struct GrabAudioProcessorValue
{
    GrabAudioProcessorValue(std::atomic<float>& ap_valueOne, std::atomic<float>& ap_valueTwo) : valueOne(ap_valueOne), valueTwo(ap_valueTwo) {}
    
    float getValueOneFromAudioProcessor()
    {
        return valueOne.load();
    }
    
    float getValueTwoFromAudioProcessor()
    {
        return valueTwo.load();
    }
    std::atomic<float>& valueOne;
    std::atomic<float>& valueTwo;
};

class TestAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                  public juce::Timer,
                                  public juce::Slider::Listener
{
public:
    TestAudioProcessorEditor (TestAudioProcessor&);
    ~TestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void mouseDown(const juce::MouseEvent &event) override;
    void sliderValueChanged(juce::Slider *slider) override;
    
    GrabAudioProcessorValue grabAudioProcessorValue;
    
private:

    Panel panelOne;
    Panel panelTwo;
    juce::Slider osc1FrequencySlider;
    juce::Slider osc2FrequencySlider;
    juce::Slider blendOscillators;
    TestAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestAudioProcessorEditor)
};
