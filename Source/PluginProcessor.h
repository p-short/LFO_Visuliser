/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LFO.h"
//==============================================================================
/**
*/

enum WaveTable {
    SineWave,
    TriangleWave,
    SawWave,
    SquareWave,
    Noise
};

class TestAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    TestAudioProcessor();
    ~TestAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioVisualiserComponent LFOScope;
    std::atomic<float> ap_oscOneBtnAlpha;
    std::atomic<float> ap_oscTwoBtnAlpha;
    WaveTable oscOneWavetable;
    WaveTable oscTwoWavetable;
    float oscOneFreq { 1 };
    float oscTwoFreq { 1 };
    float blend { 0 };
    float blendedOut;
    
private:
    
    LFO LFO_One;
    LFO LFO_Two;
    juce::AudioBuffer<float> LFOBuffer;
    juce::SmoothedValue<float> blendValToSmooth;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestAudioProcessor)
};
