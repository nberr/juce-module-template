/*
  ==============================================================================
    BEGIN_JUCE_MODULE_DECLARATION

    ID:            juce_MidiProcessor
    vendor:
    version:        1.0.0
    name:
    description:
    website:
    license:

    dependencies:

    END_JUCE_MODULE_DECLARATION


  ==============================================================================
*/

#define JUCE_MIDIPROCESSOR_H_INCLUDED
namespace juce {
    class MidiProcessor
    {
    public:
        MidiProcessor();
        ~MidiProcessor();
        
        void processBlock(juce::MidiBuffer& midiBuffer, int bufferSize);
    private:
    
    };
}
