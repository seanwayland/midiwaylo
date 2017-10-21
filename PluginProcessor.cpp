/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Waylovst5AudioProcessor::Waylovst5AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Waylovst5AudioProcessor::~Waylovst5AudioProcessor()
{
}

int waylotrans = 0;
int playing[127];
//==============================================================================
const String Waylovst5AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Waylovst5AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Waylovst5AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Waylovst5AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Waylovst5AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Waylovst5AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Waylovst5AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Waylovst5AudioProcessor::setCurrentProgram (int index)
{
}

const String Waylovst5AudioProcessor::getProgramName (int index)
{
    return {};
}

void Waylovst5AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Waylovst5AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Waylovst5AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Waylovst5AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Waylovst5AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    //for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //    buffer.clear (i, 0, buffer.getNumSamples());
    //MidiBuffer processedMidi; // our processed MIDI output
    //int time; // the timestamp of the current MIDI message in the for loop
    MidiMessage m; // the current MIDI message in the for loop
    //int NoteNumberWaylo ;
    
    /* iterate through the input buffer, process our MIDI, add it to the output buffer
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        
        if (m.isNoteOn())
        {
            m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber()+1, m.getVelocity());
        }
        processedMidi.addEvent (m, time);
        if (m.isNoteOff())
        {
            m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber()+1, m.getVelocity());
        }
        processedMidi.addEvent (m, time);
        
    }
    */
    {
        buffer.clear();
        
        
        MidiBuffer processedMidi;
        int time;
        MidiMessage m;
        
        for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
        {
            if (m.isNoteOn() && m.getNoteNumber() < 60 )
            
                
                {
                    waylotrans = m.getNoteNumber() - 48;
                    m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
                    
                }
             
            
            else if (m.isNoteOff() && m.getNoteNumber() < 60)
            
                
                {
                    waylotrans = 0;
                    m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
                }
                
            else if (m.isNoteOn() && m.getNoteNumber() >= 60)
                    
                {
                    int NewNote = m.getNoteNumber() + waylotrans -12;
                    playing[m.getNoteNumber()]= NewNote;
                    m = MidiMessage::noteOn(m.getChannel(), NewNote , m.getVelocity());
                    
                }
            else if (m.isNoteOff() && m.getNoteNumber() >= 60)
                
            {
                int NewNote = playing[m.getNoteNumber()];
                 playing[m.getNoteNumber()] = NULL;
                m = MidiMessage::noteOff(m.getChannel(), NewNote , m.getVelocity());
                
            }
            
            
            else if (m.isAftertouch())
            {
            }
            else if (m.isPitchWheel())
            {
            }
            
            processedMidi.addEvent (m, time);
        }
        
        midiMessages.swapWith (processedMidi);
    }
    
    // replace the outgoing MIDI buffer with our processed MIDI buffer
    //midiMessages.swapWith (processedMidi);
    

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Waylovst5AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Waylovst5AudioProcessor::createEditor()
{
    return new Waylovst5AudioProcessorEditor (*this);
}

//==============================================================================
void Waylovst5AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Waylovst5AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Waylovst5AudioProcessor();
}
