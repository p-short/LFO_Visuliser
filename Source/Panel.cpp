/*
  ==============================================================================

    Panel.cpp
    Created: 2 Nov 2022 5:00:20pm
    Author:  Phillip Short

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Panel.h"

//==============================================================================
Panel::Panel()
{
        addAndMakeVisible(sineBtn);
        sineBtn.btnFace(SineIcon);
    
        addAndMakeVisible(triBtn);
        triBtn.btnFace(TriIcon);
    
        addAndMakeVisible(sawBtn);
        sawBtn.btnFace(SawIcon);
    
        addAndMakeVisible(squareBtn);
        squareBtn.btnFace(SquareIcon);
    
        addAndMakeVisible(noiseBtn);
        noiseBtn.btnFace(NoiseIcon);
    
        sineBtn.btnState = true;
}

Panel::~Panel()
{
}

void Panel::paint (juce::Graphics& g)
{

}

void Panel::resized()
{
    //setbounds of buttons here.
    float btnArea = (getWidth() / 25) * 5.1;
    
    float btnOneXPos = getWidth() / 25;
    float btnTwoXPos = (getWidth() / 25) * 6.9;
    float btnThreeXPos = (getWidth() / 25) * 12.8;
    float btnFourXPos = (getWidth() / 25) * 3.45;
    float btnFiveXPos = (getWidth() / 25) * 9.35;
    float btnOneToThreeYPos = getWidth() / 25; // to replace the y argument in the first three buttons
    float btnFourToFiveYPos = (getWidth() / 25) * 6.9;
    
    // 8 pixels is the spacing between the buttons
    sineBtn.setBounds(btnOneXPos, btnOneToThreeYPos, btnArea, btnArea);
    triBtn.setBounds(btnTwoXPos, btnOneToThreeYPos, btnArea, btnArea);
    sawBtn.setBounds(btnThreeXPos, btnOneToThreeYPos, btnArea, btnArea);
    squareBtn.setBounds(btnFourXPos, btnFourToFiveYPos, btnArea, btnArea);
    noiseBtn.setBounds(btnFiveXPos, btnFourToFiveYPos, btnArea, btnArea);
}


void Panel::mouseDown(const juce::MouseEvent &event)
{
    sineBtn.btnState = (sineBtn.isMouseButtonDown()) ? true : false;
    triBtn.btnState = (triBtn.isMouseButtonDown()) ? true : false;
    sawBtn.btnState = (sawBtn.isMouseButtonDown()) ? true : false;
    squareBtn.btnState = (squareBtn.isMouseButtonDown()) ? true : false;
    noiseBtn.btnState = (noiseBtn.isMouseButtonDown()) ? true : false;
    
    if (auto* pluginEditor = getParentComponent())
    {
        pluginEditor->mouseDown(event);
    }
}
