/*
  ==============================================================================

    Btn.cpp
    Created: 31 Oct 2022 5:09:57pm
    Author:  Phillip Short

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Btn.h"

//==============================================================================
Btn::Btn()
{
    double step = juce::MathConstants<double>::twoPi / N;
    for (int i = 0; i < N + 1; i++)
    {
        sinePoints.push_back(sin(sinePointIndex) * -1);
        sinePointIndex += step;
    }
}

Btn::~Btn()
{
}

void Btn::paint (juce::Graphics& g)
{
    float click = (getWidth() / 5.1) * 0.17;
    float btnArea = (getWidth() / 5.1) * 4.8;
    float iconPos = (getWidth() / 5.1) * 1.6;
    float strokeWeight = (getWidth() / 5.1) * 0.075;
    
    // LOOK AT paintOverChilden() 
    g.saveState();
    
    float clickDist = (isClicked) ? click : 0.f;
    g.setColour(isEntered ? juce::Colours::black.brighter() : juce::Colours::black);
    g.fillRect(0.f + clickDist, 0.f + clickDist, btnArea, btnArea);

    g.setColour(isEntered ? juce::Colours::white.brighter() : juce::Colours::white);
    g.drawRect(0.f + clickDist, 0.f + clickDist, btnArea, btnArea);
              
    switch (btnIcon)
    {
        case SineIcon: {
            //use jmap() to convert the amplitude -1 to 1 from LFO to 100 to 255 so it can be used on the alpha channle of the red?
            g.setColour(btnState ? juce::Colour::fromFloatRGBA(1.f, 0.395f, 0.f, r) : juce::Colours::white);
            g.setOrigin((btnArea / 2) - iconPos + clickDist, (btnArea / 2) + clickDist);
            juce::Path sinePath;
            sinePath.startNewSubPath(0.f, 0.f);
            
            float sineWidth = (getWidth() / 5.1) * 0.1;
            for (int i = 0; i < N + 1; i++)
            {
                juce::Point<float> plot(i * sineWidth, sinePoints[i] * iconPos);
                sinePath.lineTo(plot);
            }
            g.strokePath(sinePath, juce::PathStrokeType(strokeWeight));
            g.restoreState();
            break;
        }
            
        case TriIcon: {
            g.setColour(btnState ? juce::Colour::fromFloatRGBA(1.f, 0.395f, 0.f, r) : juce::Colours::white);
            g.setOrigin((btnArea / 2) + clickDist, (btnArea / 2) + clickDist);
            juce::Path triPath;
            triPath.startNewSubPath(-iconPos, iconPos);
            triPath.lineTo(0, -iconPos);
            triPath.lineTo(iconPos, iconPos);
            g.strokePath(triPath, juce::PathStrokeType(strokeWeight));
            g.restoreState();
            break;
        }
            
        case SawIcon: {
            g.setColour(btnState ? juce::Colour::fromFloatRGBA(1.f, 0.395f, 0.f, r) : juce::Colours::white);
            g.setOrigin((btnArea / 2) + clickDist, (btnArea / 2) + clickDist);
            juce::Path sawPath;
            sawPath.startNewSubPath(-iconPos, iconPos);
            sawPath.lineTo(iconPos, -iconPos);
            sawPath.lineTo(iconPos, iconPos);
            g.strokePath(sawPath, juce::PathStrokeType(strokeWeight));
            g.restoreState();
            break;
        }
            
        case SquareIcon: {
            g.setColour(btnState ? juce::Colour::fromFloatRGBA(1.f, 0.395f, 0.f, r) : juce::Colours::white);
            g.setOrigin((btnArea / 2) + clickDist, (btnArea / 2) + clickDist);
            juce::Path rectPath;
            rectPath.startNewSubPath(-iconPos, 0);
            rectPath.lineTo(-iconPos, -iconPos);
            rectPath.lineTo(0, -iconPos);
            rectPath.lineTo(0, iconPos);
            rectPath.lineTo(iconPos, iconPos);
            rectPath.lineTo(iconPos, 0);
            g.strokePath(rectPath, juce::PathStrokeType(strokeWeight));
            g.restoreState();
            break;
        }
            
        case NoiseIcon: {
            g.setColour(btnState ? juce::Colour::fromFloatRGBA(1.f, 0.395f, 0.f, r) : juce::Colours::white);
            g.setOrigin((btnArea / 2) - iconPos + clickDist, (btnArea / 2) + clickDist);
            juce::Path noisePath;
            noisePath.startNewSubPath(0, 0);
            
            float x = (getWidth() / 5.1) * 0.2;
            for (int i = 0; i < N / 2; i++)
            {
                juce::Point<float> noisePlot(i * x, noisePoints[i] * iconPos);
                noisePath.lineTo(noisePlot);
            }
            g.strokePath(noisePath, juce::PathStrokeType(strokeWeight));
            g.restoreState();
            break;
        }
    }
}

void Btn::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void Btn::btnFace(Icon _btnIcon)
{
   btnIcon = _btnIcon;
}

void Btn::mouseEnter(const juce::MouseEvent &event)
{
    isEntered = true;
}

void Btn::mouseExit(const juce::MouseEvent &event)
{
    isEntered = false;
}

void Btn::mouseDown(const juce::MouseEvent &event)
{
    isClicked = true;
    
    if (auto* parent = getParentComponent())
    {
        parent->mouseDown(event);
    }
}

void Btn::mouseUp(const juce::MouseEvent &event)
{
    isClicked = false;
}
