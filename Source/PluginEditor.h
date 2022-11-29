/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveshapePanel.h"


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
    void paintOverChildren(juce::Graphics &g) override;
    void resized() override;
    void timerCallback() override;
    void mouseDown(const juce::MouseEvent &event) override;
    void sliderValueChanged(juce::Slider *slider) override;
    
    GrabAudioProcessorValue grabAudioProcessorValue;
    
private:

    WaveshapePanel osc1, osc2;
    juce::Slider blendSlider;
    
    TestAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestAudioProcessorEditor)
};
