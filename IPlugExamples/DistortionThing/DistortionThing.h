#ifndef __DISTORTIONTHING__
#define __DISTORTIONTHING__

#pragma warning( suppress : 4101 4129 )
#include "IPlug_include_in_plug_hdr.h"

class DistortionThing : public IPlug
{
public:
  DistortionThing(IPlugInstanceInfo instanceInfo);
  ~DistortionThing();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mThreshold;
  void CreatePresets() {
      MakePreset("clean", 100.0);
      MakePreset("slightly distorted", 80.0);
      MakePreset("woooo", 40.0);
      MakePreset("waaaa", 20.0);
      MakePreset("buzzz!!!", 0.01);
  }
};

#endif
