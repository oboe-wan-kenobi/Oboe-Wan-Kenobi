#include "SynthesizerTwo.h"

#pragma warning( suppress : 4101 4129 )
#include "IPlug_include_in_plug_src.h"

#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 5;

enum EParams
{
    kNumParams
};

enum ELayout
{
    kWidth = GUI_WIDTH,
    kHeight = GUI_HEIGHT
};


void SynthesizerTwo::ProcessMidiMsg(IMidiMsg* pMsg) {
    mMIDIReceiver.onMessageReceived(pMsg);
}

SynthesizerTwo::SynthesizerTwo(IPlugInstanceInfo instanceInfo)
    : IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo) {
    TRACE;

    IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
    pGraphics->AttachPanelBackground(&COLOR_RED);
    AttachGraphics(pGraphics);
    CreatePresets();
}

SynthesizerTwo::~SynthesizerTwo() {}

void SynthesizerTwo::ProcessDoubleReplacing(
    double** inputs,
    double** outputs,
    int nFrames)
{
    // Mutex is already locked for us.

    double* leftOutput = outputs[0];
    double* rightOutput = outputs[1];

    for (int i = 0; i < nFrames; ++i) {
        mMIDIReceiver.advance();
        int velocity = mMIDIReceiver.getLastVelocity();
        if (velocity > 0) {
            mOscillator.setFrequency(mMIDIReceiver.getLastFrequency());
            mOscillator.setMuted(false);
        }
        else {
            mOscillator.setMuted(true);
        }
        leftOutput[i] = rightOutput[i] = mOscillator.nextSample() * velocity / 127.0;
    }

    mMIDIReceiver.Flush(nFrames);
}

void SynthesizerTwo::Reset()
{
    TRACE;
    IMutexLock lock(this);
    mOscillator.setSampleRate(GetSampleRate());
}

void SynthesizerTwo::OnParamChange(int paramIdx)
{
    IMutexLock lock(this);
}
