/*
  ==============================================================================
    BEGIN_JUCE_MODULE_DECLARATION

    ID:            Polyverse_ADSRController
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

#define POLYVERSE_ADSRCONTROLLER_H_INCLUDED

#include <JuceHeader.h>

namespace Polyverse {
    class ADSRController
    :   public juce::Component,
        public juce::Slider::Listener
    {
    public:
        //==============================================================================
        ADSRController();
        ~ADSRController();
        
        //==============================================================================
        void paint (juce::Graphics&) override;
        void resized() override;
        
        //==============================================================================
        void mouseDown(const juce::MouseEvent& event) override;
        void mouseDrag(const juce::MouseEvent& event) override;
        void mouseUp(const juce::MouseEvent& event) override;
        
        //==============================================================================
        void sliderValueChanged(juce::Slider* s) override;
        
    private:
        //==============================================================================
        juce::Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
        
        std::vector<juce::Slider *> sliders = {
                &attackSlider,
                &decaySlider,
                &sustainSlider,
                &releaseSlider
        };
            
        //==============================================================================
        juce::Path adsr_path;
        
        bool drawTip = false;
        juce::Point<float> tipLocation;
        juce::Slider* tipSlider;
        
        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRController)
    };
}
