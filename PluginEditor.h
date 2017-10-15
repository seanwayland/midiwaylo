/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class Waylomiditrans1_0AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Waylomiditrans1_0AudioProcessorEditor (Waylomiditrans1_0AudioProcessor&);
    ~Waylomiditrans1_0AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Waylomiditrans1_0AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waylomiditrans1_0AudioProcessorEditor)
};
