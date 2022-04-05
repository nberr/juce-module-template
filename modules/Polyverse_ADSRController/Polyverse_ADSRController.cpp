/*
  ==============================================================================



  ==============================================================================
*/

#ifdef POLYVERSE_ADSRCONTROLLER_H_INCLUDED
    #error "incorrect use of cpp file"
#endif

#include "Polyverse_ADSRController.h"

namespace Polyverse
{
    //==============================================================================
    ADSRController::ADSRController()
    {
        // initialize the sliders
        for (auto s : sliders) {
            s->setRange(0.0f, 1.0f);
            s->setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
            s->setSliderStyle(juce::Slider::LinearVertical);
            s->addListener(this);
            addAndMakeVisible(s);
        }
        
        attackSlider.setValue(0.75f);
        decaySlider.setValue(0.5f);
        sustainSlider.setValue(0.5f);
        releaseSlider.setValue(0.04f);
        
        attackSlider.setName("A");
        decaySlider.setName("D");
        sustainSlider.setName("S");
        releaseSlider.setName("R");
        
        attackSlider.setTitle("Attack");
        decaySlider.setTitle("Decay");
        sustainSlider.setTitle("Sustain");
        releaseSlider.setTitle("Release");
    }
    
    ADSRController::~ADSRController()
    {
    
    }
    
    //==============================================================================
    void ADSRController::paint (juce::Graphics& g)
    {
        g.etColour(plaf.lineColour);
        adsr_path.clear();
        adsr_path.startNewSubPath(7, getHeight()-7);
        
        // start to attack curve
        auto a_bounds = attackSlider.getBounds().reduced(12);
        adsr_path.quadraticTo(a_bounds.getX(),
                                a_bounds.getBottom(),
                                a_bounds.getX(),
                                a_bounds.getHeight() - (attackSlider.getValue() * a_bounds.getHeight()) + 35);

        // attack to decay
        auto d_bounds = decaySlider.getBounds().reduced(12);
        adsr_path.quadraticTo(a_bounds.getX(),
                                d_bounds.getHeight() - (decaySlider.getValue() * d_bounds.getHeight()) + 35,
                                d_bounds.getX(),
                                d_bounds.getHeight() - (decaySlider.getValue() * d_bounds.getHeight()) + 23);
        
        // decay to sustain
        auto s_bounds = sustainSlider.getBounds().reduced(12);
        adsr_path.lineTo(s_bounds.getX(), s_bounds.getHeight() - (sustainSlider.getValue() * s_bounds.getHeight()) + 23);
        
        // sustain to release
        auto r_bounds = releaseSlider.getBounds().reduced(12);
        adsr_path.quadraticTo(s_bounds.getX(),
                                r_bounds.getHeight() - (releaseSlider.getValue() * r_bounds.getHeight()) + 23,
                                r_bounds.getX(),
                                r_bounds.getHeight() - (releaseSlider.getValue() * r_bounds.getHeight()) + 23);
        
        // release to end
        adsr_path.lineTo(r_bounds.getX(), getHeight() - 7);
        
        // adsr gradient
        juce::FillType adsr_fill;
        adsr_fill.setGradient(juce::ColourGradient(plaf.lineColour,
                                                    getWidth()*0.5f, 200,
                                                    juce::Colour(70, 70, 70),
                                                    getWidth()*0.5f, getHeight()*0.95f,
                                                    false));
        g.setFillType(adsr_fill);
        g.setOpacity(0.9f);
        g.fillPath(adsr_path);
        
        juce::PathStrokeType adsr_stroke(7, juce::PathStrokeType::JointStyle::curved);
        adsr_stroke.setEndStyle(juce::PathStrokeType::EndCapStyle::rounded);
        g.setColour(plaf.lineColour);
        g.strokePath(adsr_path, adsr_stroke);
        
        if (drawTip) {
            g.setColour(juce::Colour(120, 22, 62));
            g.fillEllipse(tipLocation.getX()-10, tipLocation.getY()-10, 20, 20);
            
            g.setColour(juce::Colours::white);
            g.drawMultiLineText(tipSlider->getTitle() + "\nCurve\n" + juce::String(roundf(tipSlider->getValue()*100)) + "%",
                                tipLocation.getX()-50,
                                tipLocation.getY()-40,
                                120);
        
        }
    }

    void ADSRController::resized()
    {
        int x = 0,
            y = 0,
            width = 25,
            height = getHeight();
        
        attackSlider.setBounds(x + (getWidth() * 0.23f), y, width, height);
        decaySlider.setBounds(x + (getWidth() * 0.35f), y, width, height);
        sustainSlider.setBounds(x + (getWidth() * 0.8f), y, width, height);
        releaseSlider.setBounds(x + (getWidth() * 0.96), y, width, height);
    }
    
    //==============================================================================
    void ADSRController::mouseDown(const juce::MouseEvent& event)
    {
        juce::Point<float>p (event.getPosition().toFloat());
        if (adsr_path.contains(p)) {
            
            int x = p.getX();
            
            if (x > 0 && x < attackSlider.getX()) {
                tipSlider = &attackSlider;
            }
            else if (x > attackSlider.getX() && x < decaySlider.getX()) {
                tipSlider = &decaySlider;
            }
            else if (x > decaySlider.getX() && x < sustainSlider.getX()) {
                tipSlider = &sustainSlider;
            }
            else if (x > sustainSlider.getX() && x < releaseSlider.getX()) {
                tipSlider = &releaseSlider;
            }
            
            drawTip = true;
            repaint();
            tipLocation = p;
        }
    }
    

    void ADSRController::mouseDrag(const juce::MouseEvent& event)
    {
        mouseDown(event);
    }

    void ADSRController::mouseUp(const juce::MouseEvent& event)
    {
        drawTip = false;
        repaint();
    }
    
    //==============================================================================
    void ADSRController::sliderValueChanged(juce::Slider* s)
    {
        repaint();
    }
}
