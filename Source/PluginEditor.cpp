/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BassPedalAudioProcessorEditor::BassPedalAudioProcessorEditor (BassPedalAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 200);

    //Input gain slider
    inputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    inputGainSlider.setRange(-24, 12, 0.2);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    inputGainSlider.setTextValueSuffix(" dB");
    inputGainSlider.setValue(0.0);

    addAndMakeVisible(&inputGainSlider);

    inputGainSlider.onValueChange = [this] {
        audioProcessor.inputGainVal = inputGainSlider.getValue();
    };
    
    //Add buttons
    fatBtn.setButtonText("Fat");
    punchBtn.setButtonText("Punch");
    darkBtn.setButtonText("Dark");
    melodyBtn.setButtonText("Melody");

    addAndMakeVisible(&fatBtn);
    addAndMakeVisible(&punchBtn);
    addAndMakeVisible(&darkBtn);
    addAndMakeVisible(&melodyBtn);

    fatBtn.onClick = [this] {
        if (!audioProcessor.melodyOn)
            audioProcessor.fatOn = !audioProcessor.fatOn;
        repaint();
    };
    punchBtn.onClick = [this] {
        if (!audioProcessor.melodyOn)
            audioProcessor.punchOn = !audioProcessor.punchOn;
        repaint();
    };
    darkBtn.onClick = [this] {
        if (!audioProcessor.melodyOn)
            audioProcessor.darkOn = !audioProcessor.darkOn;
        repaint();
    };
    melodyBtn.onClick = [this] {
        if (!audioProcessor.melodyOn) {
            //turn on 
            audioProcessor.melodyOn = true;

            //save other modes to memory
            audioProcessor.fatOn_mem = audioProcessor.fatOn;
            audioProcessor.darkOn_mem = audioProcessor.darkOn;
            audioProcessor.punchOn_mem = audioProcessor.punchOn;

            //turn off other modes
            audioProcessor.fatOn = false;
            audioProcessor.darkOn = false;
            audioProcessor.punchOn = false;
        }
        else {
            //turn off
            audioProcessor.melodyOn = false;

            //recall other modes from memory
            audioProcessor.fatOn = audioProcessor.fatOn_mem;
            audioProcessor.punchOn = audioProcessor.punchOn_mem;
            audioProcessor.darkOn = audioProcessor.darkOn_mem;
        }
        repaint();
    };
}

BassPedalAudioProcessorEditor::~BassPedalAudioProcessorEditor()
{
}

//==============================================================================
void BassPedalAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //draw LEDs
    int ledWidth = 20;

    g.setColour(juce::Colour(0xffaa0000));
    g.drawEllipse((gridX / 2) + gridX * 1 - ledWidth / 2, 50, ledWidth, ledWidth, 3);
    g.drawEllipse((gridX / 2) + gridX * 2 - ledWidth / 2, 50, ledWidth, ledWidth, 3);
    g.drawEllipse((gridX / 2) + gridX * 3 - ledWidth / 2, 50, ledWidth, ledWidth, 3);
    g.drawEllipse((gridX / 2) + gridX * 4 - ledWidth / 2, 50, ledWidth, ledWidth, 3);

    g.setColour(juce::Colour(0xffff0000));

    int ledPad = 2;

    if (audioProcessor.fatOn) g.fillEllipse((gridX / 2) + gridX * 1 - ledWidth / 2 + ledPad, 50 + ledPad, ledWidth - 2 * ledPad, ledWidth - 2 * ledPad);
    if (audioProcessor.punchOn) g.fillEllipse((gridX / 2) + gridX * 2 - ledWidth / 2 + ledPad, 50 + ledPad, ledWidth - 2 * ledPad, ledWidth - 2 * ledPad);
    if (audioProcessor.darkOn) g.fillEllipse((gridX / 2) + gridX * 3 - ledWidth / 2 + ledPad, 50 + ledPad, ledWidth - 2 * ledPad, ledWidth - 2 * ledPad);
    if (audioProcessor.melodyOn) g.fillEllipse((gridX / 2) + gridX * 4 - ledWidth / 2 + ledPad, 50 + ledPad, ledWidth - 2 * ledPad, ledWidth - 2 * ledPad);
}

void BassPedalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //Update width / grid values
    contentWidth = getWidth() - padX * 2;
    gridX = contentWidth / 5;

    int sliderH = 150, sliderW = 80;
    inputGainSlider.setBounds((gridX / 2) - sliderW / 2, getHeight() / 2 - sliderH / 2, sliderW, sliderH);

    int btnW = 100, btnH = 50;
    int buttonOffsetVertical = 15; //move it down 15 (to make room for LED indicator)

    fatBtn.setBounds((gridX/2) + gridX * 1 - btnW / 2, getHeight() / 2 - btnH / 2 + buttonOffsetVertical, btnW, btnH);
    punchBtn.setBounds((gridX / 2) + gridX * 2 - btnW / 2, getHeight() / 2 - btnH / 2 + buttonOffsetVertical, btnW, btnH);
    darkBtn.setBounds((gridX / 2) + gridX * 3 - btnW / 2, getHeight() / 2 - btnH / 2 + buttonOffsetVertical, btnW, btnH);
    melodyBtn.setBounds((gridX / 2) + gridX * 4 - btnW / 2, getHeight() / 2 - btnH / 2 + buttonOffsetVertical, btnW, btnH);

}