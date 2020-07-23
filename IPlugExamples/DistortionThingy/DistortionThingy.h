#ifndef __DISTORTIONTHINGY__
#define __DISTORTIONTHINGY__

#include "IPlug_include_in_plug_hdr.h"

class DistortionThingy : public IPlug
{
public:
  DistortionThingy(IPlugInstanceInfo instanceInfo);
  ~DistortionThingy();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mGain;
};

#endif
