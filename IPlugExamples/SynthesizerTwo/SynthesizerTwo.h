#ifndef __SYNTHESIZERTWO__
#define __SYNTHESIZERTWO__

#include "Oscillator.h"

#pragma warning( suppress : 4101 4129 )
#include "IPlug_include_in_plug_hdr.h"

class SynthesizerTwo : public IPlug
{
public:
  SynthesizerTwo(IPlugInstanceInfo instanceInfo);
  ~SynthesizerTwo();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mFrequency;
  void CreatePresets() {

      MakePreset("clean", 440.0);
  
  }
  Oscillator mOscillator;
};

#endif
