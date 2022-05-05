/*
  ==============================================================================



  ==============================================================================
*/

#ifdef JUCE_MIDIPROCESSOR_H_INCLUDED
    #error "incorrect use of cpp file"
#endif

#include "juce_MidiProcessor.h"

namespace juce
{
    MidiProcessor::MidiProcessor()
    {
        
    }
    
    MidiProcessor::~MidiProcessor()
    {
    
    }

    void MidiProcessor::processBlock(juce::MidiBuffer& midiBuffer, int bufferSize)
    {
        // don't do anything if the buffer is empty
        // remove this if processing still needs to be done for timed events
        // for something like an arpeggiator
        if (midiBuffer.isEmpty()) {
            return;
        }
        
        MidiBuffer processedMidi;
        
        for (auto const meatadata : midiBuffer) {
            
            auto const msg = metadata.getMessage();
            
            // process the midi here
            
            if (msg.noteOn()) {
                processedMidi.addEvent(juce::MidiMessage::noteOn(1, negative_note, msg.getVelocity()), msg.getTimeStamp());
            }
            else if (msg.isNoteOff()) {
                processedMidi.addEvent(juce::MidiMessage::noteOff(1, negative_note, msg.getVelocity()), msg.getTimeStamp());
            }
            
        }
        
        midiBuffer.swapWith(processedMidi);
        
        // use this for timed events
        for (int i = 0; i < bufferSize; i++) {
            
        }
    }
}
