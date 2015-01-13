/*
  ==============================================================================

    GuiLookAndFeel.cpp
    Created: 9 Jan 2015 11:37:13am
    Author:  kristian

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GuiLookAndFeel.h"

//==============================================================================
GuiLookAndFeel::GuiLookAndFeel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

GuiLookAndFeel::~GuiLookAndFeel()
{
}

/*Image rotary slider*/
void GuiLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                                      float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    const float radius = jmin(width / 2, height / 2) - 2.0f;
	String name = slider.getName();
	
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
	
	/*g.setColour((Colours::black).withAlpha(0.3f));
	g.drawRect(x,y,width,height,1);*/
	

	if (isMouseOver )
		slider.setMouseCursor(MouseCursor::PointingHandCursor);

	if(name == "gainSlider")
		g.setColour((Colours::yellow).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if ( name == "panSlider")
		g.setColour((Colours::coral).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if (name == "delaySlider")
		g.setColour((Colours::yellowgreen).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if (name == "delayTimeSlider")
		g.setColour((Colours::limegreen).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if (name == "hpfSlider")
		g.setColour((Colours::white).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if (name == "dfs_violet")
		g.setColour((Colours::violet).withAlpha(isMouseOver? 1.0f: 0.5f));
	else 
		g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver? 1.0f: 0.5f));

	if(!slider.isEnabled())
		g.setColour((Colours::black).withAlpha(0.3f));

	 {
            const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
            Path outlineArc;
            outlineArc.addEllipse(rx+6, ry+6, rw-12, rw-12);
			g.strokePath (outlineArc,PathStrokeType (lineThickness));
			g.setOpacity(0.5f);
			g.drawLine(rx-10,centreY,rx+3,centreY,lineThickness);      
	 }
   

    Rectangle<float> r(rx, ry, rw, rw);
    {
		g.setOpacity(1.0f);
		g.addTransform(AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));
		g.drawImage(chikenKnobImage, rx, ry, radius * 2, radius * 2, 0, 0, chikenKnobImage.getWidth(), chikenKnobImage.getHeight());
    }

        //
        //Path needle;
        //
        //Rectangle<float> r2(0.0f, 0.0f, rw*0.05f, rw * 0.3f);
        //needle.addRectangle(r2.withPosition(Point<float>(r.getCentreX() - (r2.getWidth() / 2.0f), r.getY())));

        ////g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
        //g.setGradientFill(ColourGradient(Colours::grey, 0, 0, Colours::black, 50, 50, true));
        ////g.setColour(Colours::black);
        //g.fillPath(needle, AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));
        
}
void GuiLookAndFeel::drawTickBox(Graphics& g, Component& component,
                 float x, float y, float w, float h,
                 bool ticked,
                 bool isEnabled,
                 bool isMouseOverButton,
                 bool isButtonDown) 
{
	if (isMouseOverButton){
		component.setMouseCursor(MouseCursor::PointingHandCursor);
	}

	if (ticked)
	{		
		g.drawImage(checkboxOffImage,0,0,checkboxOffImage.getWidth(),checkboxOffImage.getHeight(),0,0,checkboxOffImage.getWidth(),checkboxOffImage.getHeight());
	} else 
	{
		g.drawImage(checkboxOnImage,0,0,checkboxOffImage.getWidth(),checkboxOffImage.getHeight(),0,0,checkboxOffImage.getWidth(),checkboxOffImage.getHeight());
	}
}

void GuiLookAndFeel::drawToggleButton(Graphics& g, ToggleButton& button,
                      bool isMouseOverButton, bool isButtonDown)
{

	//g.drawRect(0,0,button.getWidth(),button.getHeight(),1);
	

    if (button.hasKeyboardFocus(true))
    {
        //g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
        //g.drawRect (0, 0, button.getWidth(), button.getHeight());
    }

    float fontSize = 10.0f;//jmin (15.0f, button.getHeight() * 0.75f);
    const float tickWidth = 19.0f;//fontSize * 1.1f;

    drawTickBox(g, button, 0, 0, button.getHeight(), button.getHeight(),
                button.getToggleState(),
                button.isEnabled(),
                isMouseOverButton,
                isButtonDown);

    g.setColour(button.findColour(ToggleButton::textColourId));
    g.setFont(fontSize);

    if (!button.isEnabled())
        g.setOpacity(0.5f);

    /*const int textX = (int)tickWidth;

    g.drawFittedText(button.getButtonText(),
                     textX, 0,
                     button.getWidth() - textX - 2, button.getHeight(),
                     Justification::centredLeft, 10);*/
}

void GuiLookAndFeel::drawGroupComponentOutline(Graphics& g, int width, int height,
                               const String& text, const Justification& position,
                               GroupComponent& group)
{
    const float textH = 10.0f;
    const float indent = 3.0f;
    const float textEdgeGap = 4.0f;
    float cs = 5.0f;

    Font f(textH);

    Path p;
    float x = indent;
    float y = f.getAscent() - 3.0f;
    float w = jmax(0.0f, width - x * 2.0f);
    float h = jmax(0.0f, height - y - indent);
    cs = jmin(cs, w * 0.5f, h * 0.5f);
    const float cs2 = 2.0f * cs;

    float textW = text.isEmpty() ? 0 : jlimit(0.0f, jmax(0.0f, w - cs2 - textEdgeGap * 2), f.getStringWidth(text) + textEdgeGap * 2.0f);
    float textX = cs + textEdgeGap;

    if (position.testFlags(Justification::horizontallyCentred))
        textX = cs + (w - cs2 - textW) * 0.5f;
    else if (position.testFlags(Justification::right))
        textX = w - cs - textW - textEdgeGap;

    p.startNewSubPath(x + textX + textW, y);
    p.lineTo(x + w - cs, y);

    p.addArc(x + w - cs2, y, cs2, cs2, 0, float_Pi * 0.5f);
    p.lineTo(x + w, y + h - cs);

    p.addArc(x + w - cs2, y + h - cs2, cs2, cs2, float_Pi * 0.5f, float_Pi);
    p.lineTo(x + cs, y + h);

    p.addArc(x, y + h - cs2, cs2, cs2, float_Pi, float_Pi * 1.5f);
    p.lineTo(x, y + cs);

    p.addArc(x, y, cs2, cs2, float_Pi * 1.5f, float_Pi * 2.0f);
    p.lineTo(x + textX, y);

    const float alpha = group.isEnabled() ? 1.0f : 0.5f;

    g.setColour(group.findColour(GroupComponent::outlineColourId)
                .withMultipliedAlpha(alpha));

    g.strokePath(p, PathStrokeType(2.0f));

    g.setColour(group.findColour(GroupComponent::textColourId)
                .withMultipliedAlpha(alpha));
    g.setFont(f);
    g.drawText(text,
               roundToInt(x + textX), 0,
               roundToInt(textW),
               roundToInt(textH),
               Justification::centred, true);
}

void GuiLookAndFeel::setImage(Image image)
{
    img = image;
}

void GuiLookAndFeel::setImages(Image rotaryImage, Image cbOnImage,Image cbOffImage)
{
    chikenKnobImage = rotaryImage;
	checkboxOffImage = cbOffImage;
	checkboxOnImage = cbOnImage;
}

void GuiLookAndFeel::setChickKnobImage(Image image)
{
    
}

void GuiLookAndFeel::drawLabel(Graphics& g, Label& label)
{
    g.fillAll(label.findColour(Label::backgroundColourId));
	Rectangle<int> textArea(label.getBorderSize().subtractedFrom(label.getLocalBounds()));
    if (!label.isBeingEdited())
    {
        const float alpha = label.isEnabled() ? 1.0f : 0.5f;
        Font font(getLabelFont(label));
		font.setHeight(10.0f);
        g.setColour(label.findColour(Label::textColourId).withMultipliedAlpha(alpha));
        g.setFont(font);
        g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
                         jmax(1, (int)(textArea.getHeight() / font.getHeight())),
                         label.getMinimumHorizontalScale());

        g.setColour(label.findColour(Label::outlineColourId).withMultipliedAlpha(alpha));
    } else if (label.isEnabled())
    {
        g.setColour(label.findColour(Label::outlineColourId));
    }

    //g.drawRect(label.getLocalBounds());
	//g.drawRect(textArea);
}