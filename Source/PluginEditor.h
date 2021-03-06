/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "FilmStrip.h"


//==============================================================================
/**
*/
class PluginEditor  : public AudioProcessorEditor,
                      public Button::Listener,
                      public Slider::Listener,
                      private Timer
{
public:
    PluginEditor (PluginProcessor&);
    ~PluginEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void buttonClicked (Button* clickedButton) override;
    void sliderValueChanged (Slider* changedSlider) override;

private:
    TextButton buttonAB;
    TextButton buttonCopyAB;
    OwnedArray<Slider> sliders;
    OwnedArray<Label> labels;

    Image backgroundImage;
    Image knobStyleImage;
    Image filmstripImage;

    FilmStrip* knob;
    
    void timerCallback() override;

    void setProcParamFromSlider (const Slider& slider) const;
    void updateSlidersFromProcParams();

    PluginProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};


namespace NonMember // Some helper functions that don't need to be inside the processor
{

void printSlidersParams(const PluginProcessor& processor,
                        const OwnedArray<Slider>& sliders);

}

#endif  // PLUGINEDITOR_H_INCLUDED
