/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BassPedalAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BassPedalAudioProcessorEditor (BassPedalAudioProcessor&);
    ~BassPedalAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BassPedalAudioProcessor& audioProcessor;

    juce::Slider inputGainSlider;
    juce::TextButton fatBtn;
    juce::TextButton punchBtn;
    juce::TextButton darkBtn;
    juce::TextButton melodyBtn;

    // GUI size values
    int padX = 10;
    int contentWidth = getWidth() - padX * 2;
    int gridX = contentWidth / 5;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BassPedalAudioProcessorEditor)
};
