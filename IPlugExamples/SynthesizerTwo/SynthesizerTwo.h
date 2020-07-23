#ifndef __SYNTHESIZERTWO__
#define __SYNTHESIZERTWO__

#include "Oscillator.h"
#include "MIDIReceiver.h"

#pragma warning( suppress : 4101 4129 )
#include "IPlug_include_in_plug_hdr.h"



class SynthesizerTwo : public IPlug
{

public:

  SynthesizerTwo(IPlugInstanceInfo instanceInfo);
  ~SynthesizerTwo();
  //const int kNumPrograms = 5;
  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

  // to receive MIDI messages:
  void ProcessMidiMsg(IMidiMsg* pMsg);

private:
  double mFrequency;
  void SynthesizerTwo::CreatePresets() {
      
      MakeDefaultPreset(nullptr, kNumPrograms);
  }
  Oscillator mOscillator;

  MIDIReceiver mMIDIReceiver;
};

#endif
