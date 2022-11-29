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
    WaveshapePanel(juce::String _nameForLabel)
    {
        nameForLabel = _nameForLabel;
        
        double step = juce::MathConstants<double>::twoPi / N;
        for (int i = 0; i < N + 1; i++)
        {
            sinePoints.push_back(sin(sinePointIndex) * -1);
            sinePointIndex += step;
        }
        
        title.setColour(juce::Label::textColourId, juce::Colours::black);
        title.setText(nameForLabel, juce::dontSendNotification);
        title.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(&title);
        
        for (int b = 0; b < buttons.size(); b++)
        {
            buttons[b]->setLookAndFeel(&myLookAndFeel);
            addAndMakeVisible(buttons[b]);
        }
        
        frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
        frequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        frequencySlider.setRange(20., 100., 0.01);
        addAndMakeVisible(&frequencySlider);
    }

    ~WaveshapePanel() override
    {
        buttons.clear();
    }

    void paintOverChildren(juce::Graphics &g) override
    {
        //text over freq slider
        juce::Rectangle <int> myArea(getLocalBounds());
        juce::Rectangle <int> top(myArea.removeFromTop(getHeight() / 8));
        juce::Rectangle <int> movedTop(top.translated(myArea.getWidth() / 16, getHeight() / 8).withWidth(myArea.getWidth() - myArea.getWidth() / 8));
        g.setColour(juce::Colours::white);
        g.drawText("Frequency", movedTop.reduced(movedTop.getHeight() / 8), juce::Justification::centred);
        
        //paint over buttons
        juce::Point <float> b1 = sineBtn.getBounds().getCentre().toFloat();
        float b1Click = (sineBtn.isDown()) ? -edge / 2 : -edge;
        float btnArea = (sineBtn.getWidth() / 5.1);
        float iconPos = btnArea * 1.4;
        g.setOrigin(b1.x + b1Click - sineBtn.getWidth() / 3.8, b1.y + b1Click + sineBtn.getHeight() / 16);
        juce::Path sinePath;
        sinePath.startNewSubPath(0, 0);
        for (int i = 0; i < N + 1; i++)
        {
            juce::Point<float> plot(i * btnArea * 0.1, sinePoints[i] * iconPos);
            sinePath.lineTo(plot);
        }
        g.strokePath(sinePath, juce::PathStrokeType(1.f));
    }

    void resized() override
    {
        //Component area
        juce::Rectangle<int> pannelArea(getLocalBounds());
        
        //label
        juce::Rectangle<int> top(pannelArea.removeFromTop(getHeight() / 8));
        title.setBounds(top);
        
        //frequency slider
        juce::Rectangle <int> movedTop(top.translated(pannelArea.getWidth() / 16, getHeight() / 8).withWidth(pannelArea.getWidth() - pannelArea.getWidth() / 8));
        frequencySlider.setBounds(movedTop.reduced(0, movedTop.getHeight() / 8));
        
        //buttons
        juce::Rectangle <int> buttonBorder(pannelArea.removeFromBottom(pannelArea.getHeight() / 4 * 3));
        juce::Rectangle <int> movedButtonBorder(buttonBorder.translated(0, -getHeight() / 16).reduced(pannelArea.getHeight() / 8));
        int spacing = movedButtonBorder.getWidth() / 2.9;
        juce::Rectangle <int> btnTop(movedButtonBorder.removeFromTop(movedButtonBorder.getHeight() / 2));
        juce::Rectangle <int> btnReduction(btnTop.reduced(movedButtonBorder.getHeight() / 16));
        
        //buttons row one
        juce::Rectangle <int> btnOne(btnReduction.withWidth(btnReduction.getHeight())); //width and height = 59,
        juce::Rectangle <int> btnTwo(btnOne.translated(spacing, 0));
        juce::Rectangle <int> btnThree(btnOne.translated(spacing * 2, 0));
        
        //buttons row two
        juce::Rectangle <int> btnBottom(movedButtonBorder.removeFromTop(movedButtonBorder.getHeight()));
        juce::Rectangle <int> btnFour(btnOne.translated(spacing - spacing / 2, btnBottom.getHeight()));
        juce::Rectangle <int> btnFive(btnOne.translated(spacing * 2 - spacing / 2 , btnBottom.getHeight()));
        
        sineBtn.setBounds(btnOne);
        triBtn.setBounds(btnTwo);
        sawBtn.setBounds(btnThree);
        squareBtn.setBounds(btnFour);
        noiseBtn.setBounds(btnFive);
    }
    
    MyLookAndFeel myLookAndFeel;
    juce::TextButton sineBtn, triBtn, sawBtn, squareBtn, noiseBtn;
    std::vector <juce::TextButton*> buttons = { &sineBtn, &triBtn, &sawBtn, &squareBtn, &noiseBtn };
    juce::Slider frequencySlider;
    juce::Label title;
    juce::String nameForLabel;

private:
    const int N { 32 };
    std::vector<double> sinePoints;
    double sinePointIndex { 0 };
    std::vector<float> noisePoints {0, -0.26, -0.6, -0.29, -0.27, 0.51, 0.1, -1,
                                    -0.77, 1, 0.35, -0.32, 0.08, 0.78, -0.15, 0};
    int edge { 4 };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveshapePanel)
};
