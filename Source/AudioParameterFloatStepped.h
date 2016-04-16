/*
  ==============================================================================

    AudioParameterFloatStepped.h
    Created: 7 Feb 2016 1:37:26pm
    Author:  John Flynn

  ==============================================================================
*/

#ifndef AUDIOPARAMETERFLOATSTEPPED_H_INCLUDED
#define AUDIOPARAMETERFLOATSTEPPED_H_INCLUDED


//==============================================================================
/**
    AudioParameterFloat with variable step size
    -------------------------------------------

    - Supports range changing with setRange()
    - Optional tag as step size master control
    - Optional tag as slaved to step size

*/
class AudioParameterFloatStepped   : public AudioParameterFloat {
public:
    enum Stepping {
        none,       // Continuous or directly-set, static step size
        stepMaster, // Sets the step size of all stepSlave controls
        stepSlave   // Variable step size set by stepMaster
    };

    AudioParameterFloatStepped (String name,
                                float min = 0.0f,
                                float max = 1.0f,
                                float def = 0.0f,
                                float step = 0.0f,
                                Stepping stepSetting = none)
        : AudioParameterFloat (name, name, min, max, def),
          stepSetting_ (stepSetting)

    {
        if (step > 0.0f)
            range = NormalisableRange<float> {min, max, step};  // skew can be added later
    }

    ~AudioParameterFloatStepped() {};

    void setRange (float min, float max, float step)
    {
        range = NormalisableRange<float> {min, max, step};      // skew can be added later

        // Then snap value to new interval/range
        const float snappedValue = range.snapToLegalValue (get());
        const float snappedValue0to1 = range.convertTo0to1 (snappedValue);
        setValueNotifyingHost (snappedValue0to1);
    }

    Stepping stepSetting() const { return stepSetting_; }

private:
    Stepping stepSetting_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioParameterFloatStepped)
};


#endif  // AUDIOPARAMETERFLOATSTEPPED_H_INCLUDED
