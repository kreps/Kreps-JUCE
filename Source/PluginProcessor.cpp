/*
==============================================================================

This file was auto-generated by the Jucer!

It contains the basic startup code for a Juce application.

author: kreps
yea
more
and then
==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioProcessor* JUCE_CALLTYPE createPluginFilter();

const float wetOnDefault = 1.0f;
const float dryOnDefault = 1.0f;
const float wetGainDefault = 0.2f;
const float delayDefault = 0.0f;
const float delayTimeDefault = 0.01f;
const float panDefault = 0.5f;
const float widthDefault = 1.0f;
//const float hpfQDefaultValue = 0.001f;
const float hpfFreqDefaultValue = 0.01f;
const int delayBufferMaxLength = 1024;
const float midOnDefault = 1.0f;
const float roomsizeDefault = 0.1f;
const float roomDampDefault = 0.5f;
const float saturationDefault = 0.01f;
const float lpfFreqDefaultValue = 1.0f;
//const float lpfQDefaultValue = 1.0f;

//==============================================================================
JuceDemoPluginAudioProcessor::JuceDemoPluginAudioProcessor()
    : delayBuffer(2, delayBufferMaxLength)
{
    // Set up some default values..
    wetGain = wetGainDefault;
    delayAmount = delayDefault;
    delayTime = delayTimeDefault;
    pan = panDefault;
    wetOn = wetOnDefault;
    dryOn = dryOnDefault;
    midSide = widthDefault;
	saturationAmount = saturationDefault;
    roomSize = roomsizeDefault;
	roomDamp = roomDampDefault;
	hpfFreq = hpfFreqDefaultValue;
    midOn = midOnDefault;
    lpfFreqValue = lpfFreqDefaultValue;
    /*lastUIWidth = 400;
    lastUIHeight = 200;
*/
    lastPosInfo.resetToDefault();
    delayPosition = 0;
    // "1024" is the number of samples over which to fade parameter changes
    //dspFilter = new Dsp::SmoothedFilterDesign<Dsp::RBJ::Design::HighPass, 2>(1024);
    //dspFilterParams[2] = 1.25; // Q
    //dspFilter->setParams(dspFilterParams);

    reverbParams = reverb.getParameters();
    reverbParams.dryLevel = 0.0f;
	reverbParams.wetLevel = 1.0f; 
	reverbParams.width = 1.0f;
	reverbParams.damping = roomDampDefault;
}

JuceDemoPluginAudioProcessor::~JuceDemoPluginAudioProcessor()
{}

//==============================================================================
int JuceDemoPluginAudioProcessor::getNumParameters()
{
    return TOTALPARAMCOUNT;
}

float JuceDemoPluginAudioProcessor::getParameter(int index)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case WETON:
            return wetOn;
        case DRYON:
            return dryOn;
        case WETAMOUNT:
            return wetGain;
        case DELAYAMOUNT:
            return delayAmount;
        case DELAYTIME:
            return delayTime;
        case PAN:
            return pan;
        case WIDTH:
            return midSide;
        case SATURATION:
            return saturationAmount;
        case HPFFREQ:
            return hpfFreq;
        case ROOMSIZE:
            return roomSize;
		case ROOMDAMP:
			return roomDamp;
		case MIDON:
			return midOn;
        case LPFFREQ:
            return lpfFreqValue;
        case LPFQ:
            return lpfQValue;
        default:
            return 0.0f;
    }
}

void JuceDemoPluginAudioProcessor::setParameter(int index, float newValue)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case WETON:
            wetOn = newValue;
            break;
        case DRYON:
            dryOn = newValue;
            break;
        case WETAMOUNT:
            wetGain = newValue;
            break;
        case DELAYAMOUNT:
            delayAmount = newValue;
            break;
        case DELAYTIME:
            delayTime = newValue;
            break;
        case PAN:
            pan = newValue;
            break;
        case WIDTH:
            midSide = newValue;
            break;
		case MIDON:
			midOn = newValue;
			break;
        case SATURATION:
            saturationAmount = newValue;
            break;
        case HPFFREQ:
            hpfFreq = newValue;
            break;
        case HPFQ:
            hpfQ = newValue;
            break;
        case ROOMSIZE:
            roomSize = newValue;
            break;
		case ROOMDAMP:
			roomDamp = newValue;
            break;
        case LPFFREQ:
            lpfFreqValue = newValue;
            break;
        case LPFQ:
            lpfQValue = newValue;
            break;
        default:
            break;
    }
}

float JuceDemoPluginAudioProcessor::getParameterDefaultValue(int index)
{
    switch (index)
    {
        case WETON: return wetOnDefault;
        case DRYON: return dryOnDefault;
        case WETAMOUNT:     return wetGainDefault;
        case DELAYAMOUNT:    return delayDefault;
        case DELAYTIME:    return delayTimeDefault;
        case PAN:    return panDefault;
        case WIDTH:    return widthDefault;
		case MIDON: return midOnDefault;
        case SATURATION: return saturationDefault;
        case HPFFREQ: return hpfFreqDefaultValue;
        //case HPFQ: return hpfQDefaultValue;
		case ROOMSIZE: return roomsizeDefault;
		case ROOMDAMP: return roomDampDefault;
        case LPFFREQ:return lpfFreqDefaultValue;
        //case LPFQ: return lpfQDefaultValue;
        default:            break;
    }

    return 0.0f;
}

const String JuceDemoPluginAudioProcessor::getParameterName(int index)
{
    switch (index)
    {
        case WETON:		return "bypass";
        case DRYON:		return "dry on";
        case WETAMOUNT:			return "gain";
        case DELAYAMOUNT:		return "delay";
        case DELAYTIME:    return "delay time";
        case PAN:			return "pan";
        case WIDTH:		return "mid/side";
		case MIDON: return "mid on";
        case SATURATION:	return "threshold";
        case HPFFREQ:			return "hpf freq";
        case ROOMSIZE: return "room size";
		case ROOMDAMP: return "room damp";
        case LPFFREQ: return "lpf freq";
        case LPFQ: return "lpf q";
        default:				break;
    }

    return String::empty;
}

const String JuceDemoPluginAudioProcessor::getParameterText(int index)
{
    return String(getParameter(index), 2);
}

//==============================================================================
void JuceDemoPluginAudioProcessor::prepareToPlay(double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    delayBuffer.clear();
}

void JuceDemoPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    //keyboardState.reset();
}

void JuceDemoPluginAudioProcessor::reset()
{
    // Use this method as the place to clear any delay lines, buffers, etc, as it
    // means there's been a break in the audio's continuity.
    delayBuffer.clear();
    //m_Reverb.reset();
}

float JuceDemoPluginAudioProcessor::sigmoid(float x)
{
    if (fabs(x) < 1)
        return x*(1.5f - 0.5f*x*x);
    else
        return x > 0.f ? 1.f : -1.f;
}

float JuceDemoPluginAudioProcessor::distortion(float in, float threshold)
{
    if (in > threshold || in < -threshold)
    {
        in = (in + fabs(fabs(fmod(in - threshold, threshold * 4)) - threshold * 2) - threshold) / 2.0f;
    }
    return in;
}

float JuceDemoPluginAudioProcessor::Saturate(float x, float t)
{
    if (abs(x) < t)
        return x;
    else
    {
        if (x > 0.0f)
            return   t + (1.f - t)*sigmoid((x - t) / ((1 - t)*1.5f));
        else
            return -(t + (1.f - t)*sigmoid((-x - t) / ((1 - t)*1.5f)));
    }
}



void JuceDemoPluginAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    inputBuffer = buffer;
    if (wetOn == 0.0f || getNumInputChannels() < 2)
    {
        return;
    }

    const int numSamples = buffer.getNumSamples();
    int dp = 0;
    //dspFilterParams[0] = getSampleRate(); // sample rate
    //dspFilterParams[1] = hpfFrequency; // cutoff frequency
    //dspFilter->setParams(dspFilterParams);
    //dspFilter->process(numSamples, buffer.getArrayOfWritePointers());
    //calculate left and right gain according to pan param
    float lGain = (pan > 0.5f) ? 1.0f - (pan - 0.5f) * 2.0f : 1.0f;
    float rGain = (pan < 0.5f) ? 1.0f - (0.5f - pan) * 2.0f : 1.0f;

    //float fMidGain = (midSide > 0.5f) ? 1.0f - (midSide - 0.5f) * 2.0f : 1.0f;
    //float fSideGain = midSide < 0.5f) ? 1.0f - (0.5f - midSide) * 2.0f:1.0f;

    float* leftData = buffer.getWritePointer(0);
    float* leftInData = inputBuffer.getWritePointer(0);

    float* rightData = buffer.getWritePointer(1);
    float* rightInData = inputBuffer.getWritePointer(1);

    float* leftDelayData = delayBuffer.getWritePointer(0);
    float* rightDelayData = delayBuffer.getWritePointer(1);
    dp = delayPosition;
	
    //m_ic = juce::IIRCoefficients::makeHighPass (getSampleRate(), hpfFrequency);
   /* m_ic = juce::IIRCoefficients::makeLowShelf(getSampleRate(), hpfFreq,hpfQ,0.001f);
    m_filterL.setCoefficients( m_ic );
    m_filterR.setCoefficients( m_ic );
    m_filterL.processSamples(leftData,numSamples);
    m_filterR.processSamples(rightData,numSamples);*/

    hpfCoefs = juce::IIRCoefficients::makeHighPass(getSampleRate(), hpfFreq*15000.0f);
    hpfLeft.setCoefficients(hpfCoefs);
    hpfRight.setCoefficients(hpfCoefs);
    hpfLeft.processSamples(leftData, numSamples);
    hpfRight.processSamples(rightData, numSamples);

    lpfCoefs = juce::IIRCoefficients::makeLowPass(getSampleRate(), lpfFreqValue*15000.0f);
    lpfL.setCoefficients(lpfCoefs);
    lpfR.setCoefficients(lpfCoefs);
    lpfL.processSamples(leftData, numSamples);
    lpfR.processSamples(rightData, numSamples);

    reverbParams.roomSize = roomSize;
	reverbParams.damping = roomDamp;
	reverb.setParameters(reverbParams);
    reverb.processStereo(leftData, rightData, numSamples);
	
    for (int i = 0; i < numSamples; ++i)
    {

		float m = midOn*(leftData[i] + rightData[i]) / 2;
		float s = midSide*((rightData[i] - leftData[i]) / 2);

        leftData[i] = distortion((m - s)*lGain*wetGain*5.0f, saturationAmount);
        rightData[i] = distortion((m + s)*rGain*wetGain*5.0f, saturationAmount);

        const float inLeft = leftData[i];
        leftData[i] += leftDelayData[dp];
        leftDelayData[dp] = (inLeft)* delayAmount;

        const float inRight = rightData[i];
        rightData[i] += rightDelayData[dp];
        rightDelayData[dp] = (inRight)* delayAmount;

        if (dryOn == 1.0f)
        {
            leftData[i] += leftInData[i];
            rightData[i] += rightInData[i];
        }

        leftData[i] = clipper.clip(leftData[i], -1.0f, 1.0f);
        rightData[i] = clipper.clip(rightData[i], -1.0f, 1.0f);

        if (++dp >= static_cast<int>(delayTime * delayBufferMaxLength))
            dp = 0;
    }
    delayPosition = dp;

    //	// In case we have more outputs than inputs, we'll clear any output
    //	// channels that didn't contain input data, (because these aren't
    //	// guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
}

//==============================================================================
AudioProcessorEditor* JuceDemoPluginAudioProcessor::createEditor()
{
    return new JuceDemoPluginAudioProcessorEditor(this);
}

//==============================================================================
void JuceDemoPluginAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // Here's an example of how you can use XML to make it easy and more robust:

    // Create an outer XML element..
    XmlElement xml("MYPLUGINSETTINGS");

    // add some attributes to it..
    xml.setAttribute("uiWidth", lastUIWidth);
    xml.setAttribute("uiHeight", lastUIHeight);
    xml.setAttribute("wetGain", wetGain);
    xml.setAttribute("delayAmount", delayAmount);
    xml.setAttribute("delayTime", delayTime);
    xml.setAttribute("pan", pan);
    xml.setAttribute("dryOn", dryOn);
    xml.setAttribute("midSide", midSide);
    xml.setAttribute("roomSize", roomSize);
	xml.setAttribute("roomDamp", roomDamp);
    xml.setAttribute("hpfFreq", hpfFreq);
    xml.setAttribute("hpfQ", hpfQ);
	xml.setAttribute("saturation", saturationAmount);
	xml.setAttribute("midOn", midOn);
    xml.setAttribute("lpfFreq", lpfFreqValue);
    xml.setAttribute("lpfQ", lpfQValue);

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary(xml, destData);
}

void JuceDemoPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName("MYPLUGINSETTINGS"))
        {
            // ok, now pull out our parameters..
            lastUIWidth = xmlState->getIntAttribute("uiWidth", lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute("uiHeight", lastUIHeight);
            wetGain = (float)xmlState->getDoubleAttribute("wetGain", wetGain);
            delayAmount = (float)xmlState->getDoubleAttribute("delayAmount", delayAmount);
            delayTime = (float)xmlState->getDoubleAttribute("delayTime", delayTime);
            pan = (float)xmlState->getDoubleAttribute("pan", pan);
            dryOn = (float)xmlState->getDoubleAttribute("dryOn", dryOn);
            midSide = (float)xmlState->getDoubleAttribute("midSide", midSide);
            roomSize = (float)xmlState->getDoubleAttribute("roomSize", roomSize);
			roomDamp = (float)xmlState->getDoubleAttribute("roomDamp", roomDamp);
            hpfFreq = (float)xmlState->getDoubleAttribute("hpfFreq", hpfFreq);
            hpfQ = (float)xmlState->getDoubleAttribute("hpfQ", hpfQ);
			saturationAmount = (float)xmlState->getDoubleAttribute("saturation",saturationAmount);
			midOn = (float)xmlState->getDoubleAttribute("midOn",midOn);
            lpfFreqValue = (float)xmlState->getDoubleAttribute("lpfFreq", lpfFreqValue);
            lpfQValue = (float)xmlState->getDoubleAttribute("lpfQ", lpfQValue);
        }
    }
}

const String JuceDemoPluginAudioProcessor::getInputChannelName(const int channelIndex) const
{
    return String(channelIndex + 1);
}

const String JuceDemoPluginAudioProcessor::getOutputChannelName(const int channelIndex) const
{
    return String(channelIndex + 1);
}

bool JuceDemoPluginAudioProcessor::isInputChannelStereoPair(int /*index*/) const
{
    return true;
}

bool JuceDemoPluginAudioProcessor::isOutputChannelStereoPair(int /*index*/) const
{
    return true;
}

bool JuceDemoPluginAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool JuceDemoPluginAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool JuceDemoPluginAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double JuceDemoPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceDemoPluginAudioProcessor();
}
