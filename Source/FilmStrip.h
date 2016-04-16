/*
  ==============================================================================

    FilmStrip.h
    Created: 10 Mar 2016 3:53:50pm
    Author:  John Flynn

  ==============================================================================
*/

#ifndef FILMSTRIP_H_INCLUDED
#define FILMSTRIP_H_INCLUDED


//==============================================================================
/**
    Slider that uses a PNG filmstrip for display
    --------------------------------------------
    
    Assumes:
    - Vertical filmstrip (usually containing rotating marker/texture).
    - Square image frame to calculate number of frames automatically by image
      size.
    - Using a top layer to be composited over filmstrip (usually containing
      shadows, bevels and layer styles etc.)

*/
class FilmStrip  : public Slider                                        // rename to knob?
{
public:
    FilmStrip (Image filmStripImage, Image topLayerImage /*, Image rotatingTextureImage*/)
        : Slider {},
          filmStrip {filmStripImage},
          topLayer  {topLayerImage},
          //rotatingTexture {rotatingTextureImage},
          filmStripHeight {filmStrip.getHeight()},
          width           {filmStrip.getWidth()},
          numFrames       {filmStripHeight / width}
    {
        jassert (filmStripHeight > width);
        jassert (numFrames > 1);

        setTextBoxStyle (TextBoxBelow, false, 80, 15);
        setColour (Slider::textBoxTextColourId,       Colour (0xff404040));
        setColour (Slider::textBoxBackgroundColourId, Colour (0xff707070));
        setColour (Slider::textBoxHighlightColourId,  Colour (0xffffffff));
        setColour (Slider::textBoxOutlineColourId,    Colour (0x00000000));
        setSliderStyle (RotaryHorizontalVerticalDrag);
        setTextValueSuffix(" dB");                                                      // hard coded! not general!
    }
    
    void paint(Graphics& g)
    {
        const double sliderPosition0to1 = valueToProportionOfLength (getValue());

        int frameToDisplay = static_cast<int> (sliderPosition0to1 * (numFrames - 1));

        /*const float rotateAmount = 0.05235987756f * frameToDisplay;  //  Magic X2! 3 degrees in radians

        //Logger::outputDebugString((String) sliderPosition0to1);
        //Logger::outputDebugString((String) rotateAmount);

        AffineTransform rotationTransform;
        rotationTransform = rotationTransform.rotated (rotateAmount, getSize() / 2.0f, getSize() / 2.0f);
        rotationTransform = rotationTransform.scaled (0.5, 0.5);

        //g.drawImageTransformed (rotatingTexture, rotationTransform);*/

        g.drawImage (filmStrip,                     // Draw filmstrip then draw
                     0,                             // 'topLayer' image (should have
                     0,                             // transparancies) above.
                     getSize() / 2,
                     getSize() / 2,
                     0,
                     frameToDisplay * width,
                     getSize(),
                     getSize());

        g.drawImage (topLayer, 0, 0, getSize() / 2, getSize() / 2, 0, 0, getSize(), getSize());

        if (isMouseOverOrDragging())
        {
        }
    }

    int getSize() { return width; } // return vertical/horizontal dimension of our
                                    // square component.
    
private:
    const Image filmStrip;
    const Image topLayer;
    const Image rotatingTexture;
    const int filmStripHeight;
    const int width;
    const int numFrames;
};


#endif  // FILMSTRIP_H_INCLUDED
