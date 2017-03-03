/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleGainAudioProcessor::SimpleGainAudioProcessor()
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

SimpleGainAudioProcessor::~SimpleGainAudioProcessor()
{
}

//==============================================================================
const String SimpleGainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleGainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleGainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double SimpleGainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleGainAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleGainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleGainAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleGainAudioProcessor::getProgramName (int index)
{
    return String();
}

void SimpleGainAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimpleGainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SimpleGainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleGainAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void SimpleGainAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    
    // channelDataL and channelDataR are pointers to arrays of length numSamples which
    // contain the audio for one channel.  You repeat this for each channel
    float *channelDataL = buffer.getWritePointer(0);
    float *channelDataR = buffer.getWritePointer(1);
    
    // Loop runs from 0 to number of samples in the block
    for (int i = 0; i < numSamples; ++i)
    {
        // Reduce the amplitude of each sample in the block for the
        // left and right channels
        channelDataL[i] = channelDataL[i] * 0.5;
        channelDataR[i] = channelDataR[i] * 0.25;
        
        // Another way of achieveing the same gain change per channel
        //buffer.applyGain(0, 0, numSamples, 0.5);
        //buffer.applyGain(0, 0, numSamples, 0.25);
    }

}

//==============================================================================
bool SimpleGainAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleGainAudioProcessor::createEditor()
{
    return new SimpleGainAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleGainAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleGainAudioProcessor();
}
