/*
  ==============================================================================

    WaveshapePanel.h
    Created: 28 Nov 2022 6:25:37pm
    Author:  Phillip Short

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct MyLookAndFeel : public juce::LookAndFeel_V4
{
    void drawButtonBackground (juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override
    {
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;
        buttonArea.removeFromLeft (edge);
        buttonArea.removeFromTop (edge);
  
        // shadow
        g.setColour (juce::Colours::darkgrey.withAlpha (0.5f));
        g.fillRect (buttonArea);
  
        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate (offset, offset);
  
        g.setColour ((isMouseOverButton) ? backgroundColour.withLightness(0.25f) : backgroundColour);
        g.fillRect (buttonArea);
    }
};

class WaveshapePanel  : public juce::Component
{
public:
    WaveshapePanel()
    {
        sineBtn.setLookAndFeel(&myLookAndFeel);
        triBtn.setLookAndFeel(&myLookAndFeel);
        sawBtn.setLookAndFeel(&myLookAndFeel);
        squareBtn.setLookAndFeel(&myLookAndFeel);
        noiseBtn.setLookAndFeel(&myLookAndFeel);
        
        addAndMakeVisible(&sineBtn);
        addAndMakeVisible(&triBtn);
        addAndMakeVisible(&sawBtn);
        addAndMakeVisible(&squareBtn);
        addAndMakeVisible(&noiseBtn);
        
        frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        frequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        frequencySlider.setRange(20., 100., 1.);
        addAndMakeVisible(&frequencySlider);
    }

    ~WaveshapePanel() override
    {
    }

    void paint (juce::Graphics& g) override
    {

    }

    void resized() override
    {
        float xSpace = getWidth() / 3;
        float ySpace = getHeight() / 12;
        float shrinkFactor = xSpace / 8;
        float btnArea = xSpace - shrinkFactor;
        
        
        sineBtn.setBounds(shrinkFactor, shrinkFactor + ySpace, btnArea, btnArea);
        triBtn.setBounds(xSpace + shrinkFactor, shrinkFactor + ySpace, btnArea, btnArea);
        sawBtn.setBounds((xSpace * 2) + shrinkFactor, shrinkFactor + ySpace, btnArea, btnArea);
        
        squareBtn.setBounds(xSpace - xSpace / 2 + shrinkFactor, xSpace + shrinkFactor + ySpace, btnArea, btnArea);
        noiseBtn.setBounds((xSpace * 2) - xSpace / 2 + shrinkFactor, xSpace + shrinkFactor + ySpace, btnArea, btnArea);
        
    }
    
    MyLookAndFeel myLookAndFeel;
    juce::TextButton sineBtn, triBtn, sawBtn, squareBtn, noiseBtn;
    juce::Slider frequencySlider;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveshapePanel)
};
