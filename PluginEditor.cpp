/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Waylovst5AudioProcessorEditor::Waylovst5AudioProcessorEditor (Waylovst5AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

Waylovst5AudioProcessorEditor::~Waylovst5AudioProcessorEditor()
{
}

//==============================================================================
void Waylovst5AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    Image background = ImageCache::getFromMemory (BinaryData::waylologo3_png, BinaryData::waylologo3_pngSize);
    g.drawImageAt (background, 0, 0);
    
}

void Waylovst5AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
