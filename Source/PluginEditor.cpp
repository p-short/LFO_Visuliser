/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestAudioProcessorEditor::TestAudioProcessorEditor (TestAudioProcessor& p)
    : AudioProcessorEditor (&p), grabAudioProcessorValue(p.ap_oscOneBtnAlpha, p.ap_oscTwoBtnAlpha), osc1("Osc 1"), osc2("Osc 2"), audioProcessor (p)
{
    addAndMakeVisible(&osc1);
    addAndMakeVisible(&osc2);
    addAndMakeVisible(audioProcessor.LFOScope);
    audioProcessor.LFOScope.setColours(juce::Colours::black, juce::Colour::fromRGB(255, 102, 0));
    
    //getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(255, 102, 0));
    
//    osc1FrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
//    osc1FrequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    osc1FrequencySlider.setRange(0.f, 5.f, 0.01f);
//    osc1FrequencySlider.setValue(1.f);
//    //addAndMakeVisible(osc1FrequencySlider);
//    osc1FrequencySlider.addListener(this);
//
//    osc2FrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
//    osc2FrequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    osc2FrequencySlider.setRange(0.f, 5.f, 0.01f);
//    osc2FrequencySlider.setValue(1.f);
//    //addAndMakeVisible(osc2FrequencySlider);
//    osc2FrequencySlider.addListener(this);
    
    blendSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    blendSlider.setRange(0.f, 1.f, 0.01f);
    blendSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    blendSlider.setValue(0.f);
    addAndMakeVisible(blendSlider);
    blendSlider.addListener(this);
    
    audioProcessor.oscOneWavetable = SineWave;
    audioProcessor.oscTwoWavetable = SineWave;
    
    Timer::startTimerHz(60);
    
    setResizable(true, true);
    setResizeLimits(425, 425, 600, 600);
    getConstrainer()->setFixedAspectRatio(1);
    setSize (600, 600);
}

TestAudioProcessorEditor::~TestAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void TestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colour::fromRGB(204, 204, 204).darker());
}

void TestAudioProcessorEditor::paintOverChildren(juce::Graphics &g)
{
    int t = getHeight() / 3;
    juce::Rectangle <int> area(getLocalBounds());
    juce::Rectangle <int> topSection(area.removeFromTop(t));
    juce::Rectangle <int> middleSection(topSection.withLeft(topSection.getWidth() / 3).withRight(topSection.getWidth() - topSection.getWidth() / 3));

    g.setColour(juce::Colours::white);
        
    int offSet = topSection.getHeight() / 8;
    
    //slider
    juce::Rectangle <int> bottom (middleSection.removeFromBottom (getHeight() / 16));
    juce::Rectangle <int> bottomMoved (bottom.translated (0, -offSet));
    juce::Rectangle <int> forText (bottomMoved.reduced (middleSection.getWidth() / 20, bottomMoved.getHeight() / 4));
    g.drawText("Blend", forText, juce::Justification::centred);
}

void TestAudioProcessorEditor::resized()
{
    juce::Rectangle <int> area(getLocalBounds());
    int topSpacing = area.getWidth() / 3;
    juce::Rectangle <int> topSection(area.removeFromTop(getHeight() / 3));
    int offSet = topSection.getHeight() / 8;
    juce::Rectangle <int> middleSection (topSection.withLeft (topSection.getWidth() / 3).withRight (topSection.getWidth() - topSection.getWidth() / 3));
    
    osc1.setBounds(topSection.removeFromLeft(topSpacing));
    osc2.setBounds(topSection.removeFromRight(topSpacing));
    audioProcessor.LFOScope.setBounds(middleSection.translated(0, -offSet).reduced(middleSection.getWidth() / 30, middleSection.getHeight() / 4));
    
    juce::Rectangle <int> bottom (middleSection.removeFromBottom (getHeight() / 16));
    juce::Rectangle <int> bottomMoved (bottom.translated (0, -offSet));
    juce::Rectangle <int> forText (bottomMoved.reduced (middleSection.getWidth() / 20, bottomMoved.getHeight() / 4));
    blendSlider.setBounds(forText);
    
    //panelOne.setBounds(0, yCenter - panelArea / 5, panelArea, panelArea); //yCenter - var / 5
//    panelTwo.setBounds(panel2XPos, yCenter - panelArea / 5, panelArea, panelArea);
//
//    audioProcessor.LFOScope.setBounds(xCenter - scopeWidth / 2, yCenter - scopeHeight / 2, scopeWidth, scopeHeight);
//
//    blendOscillators.setBounds(xCenter - sliderWidth / 2, yCenter + sliderHeight * 2.5, sliderWidth, sliderHeight);
//    //x = 94.5 - 100
//    osc1FrequencySlider.setBounds(osc1XPos - sliderWidth / 2, yCenter - scopeHeight * 0.7, sliderWidth, sliderHeight);
//    //x = 505.5 - 100
//    osc2FrequencySlider.setBounds(osc2XPos - sliderWidth / 2, yCenter - scopeHeight * 0.7, sliderWidth, sliderHeight);
}

void TestAudioProcessorEditor::timerCallback()
{
    repaint();
    //float oscOneMappedVal = juce::jmap(grabAudioProcessorValue.getValueOneFromAudioProcessor(), -1.f, 1.f, 0.4f, 1.f);
    //could this be handeld in panel class?
//    panelOne.sineBtn.r = oscOneMappedVal;
//    panelOne.triBtn.r = oscOneMappedVal;
//    panelOne.sawBtn.r = oscOneMappedVal;
//    panelOne.squareBtn.r = oscOneMappedVal;
//    panelOne.noiseBtn.r = oscOneMappedVal;
    
    //float oscTwoMappedVal = juce::jmap(grabAudioProcessorValue.getValueTwoFromAudioProcessor(), -1.f, 1.f, 0.4f, 1.f);
//    panelTwo.sineBtn.r = oscTwoMappedVal;
//    panelTwo.triBtn.r = oscTwoMappedVal;
//    panelTwo.sawBtn.r = oscTwoMappedVal;
//    panelTwo.squareBtn.r = oscTwoMappedVal;
//    panelTwo.noiseBtn.r = oscTwoMappedVal;
    
}

void TestAudioProcessorEditor::mouseDown(const juce::MouseEvent &event)
{
    //PANEL ONE
//    if (panelOne.sineBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscOneWavetable = SineWave;
//    }
//    
//    else if (panelOne.triBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscOneWavetable = TriangleWave;
//    }
//    
//    else if (panelOne.sawBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscOneWavetable = SawWave;
//    }
//    
//    else if (panelOne.squareBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscOneWavetable = SquareWave;
//    }
//    
//    else if (panelOne.noiseBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscOneWavetable = Noise;
//    }
//    
//    //PANEL TWO
//    if (panelTwo.sineBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscTwoWavetable = SineWave;
//    }
//    
//    else if (panelTwo.triBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscTwoWavetable = TriangleWave;
//    }
//    
//    else if (panelTwo.sawBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscTwoWavetable = SawWave;
//    }
//    
//    else if (panelTwo.squareBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscTwoWavetable = SquareWave;
//    }
//    
//    else if (panelTwo.noiseBtn.isMouseButtonDown())
//    {
//        audioProcessor.oscTwoWavetable = Noise;
//    }
}

void TestAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    
//    if (slider == &osc1FrequencySlider)
//    {
//        audioProcessor.oscOneFreq = osc1FrequencySlider.getValue();
//    }
//    
//    if (slider == &osc2FrequencySlider)
//    {
//        audioProcessor.oscTwoFreq = osc2FrequencySlider.getValue();
//    }
//    
//    if (slider == &blendOscillators)
//    {
//        audioProcessor.blend = blendOscillators.getValue();
//    }
}
