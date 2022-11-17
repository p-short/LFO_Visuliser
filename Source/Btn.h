/*
  ==============================================================================

    Btn.h
    Created: 31 Oct 2022 5:09:57pm
    Author:  Phillip Short

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
enum Icon
{
    SineIcon,
    TriIcon,
    SawIcon,
    SquareIcon,
    NoiseIcon
};

//will need mouseDown() at some point

class Btn  : public juce::Component
{
public:
    Btn();
    ~Btn() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void btnFace(Icon _btnIcon);
    void mouseEnter(const juce::MouseEvent &event) override;
    void mouseExit(const juce::MouseEvent &event) override;
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseUp(const juce::MouseEvent &event) override;
    
    bool btnState { false };    
    float r { 255 };

private:
    const int N { 32 };
    std::vector<double> sinePoints;
    double sinePointIndex { 0 };
    Icon btnIcon;
    std::vector<float> noisePoints {0, -0.26, -0.6, -0.29, -0.27, 0.51, 0.1, -1,
                                    -0.77, 1, 0.35, -0.32, 0.08, 0.78, -0.15, 0};
    bool isEntered { false };
    bool isClicked { false };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Btn)
};
