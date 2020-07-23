#include "DistortionThing.h"

#pragma warning( suppress : 4101 4129 )
#include "IPlug_include_in_plug_src.h"

#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 5;

enum EParams
{
  kThreshold = 0,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kThresholdX = 79,
  kThresholdY = 62,
  kKnobFrames = 128
};



DistortionThing::DistortionThing(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mThreshold(1.)
{
  TRACE;

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kThreshold)->InitDouble("Threshold", 0., 0., 99.99, 0.01, "%");
  GetParam(kThreshold)->SetShape(2.);

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  //pGraphics->AttachPanelBackground(&COLOR_BLUE);
  pGraphics->AttachBackground(BACKGROUND_ID, BACKGROUND_FN);

  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);

  pGraphics->AttachControl(new IKnobMultiControl(this, kThresholdX, kThresholdY, kThreshold, &knob));

  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  CreatePresets();
}

DistortionThing::~DistortionThing() {}

void DistortionThing::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.

    int const channelCount = 2;

    for (int i = 0; i < channelCount; i++) {
        double* input = inputs[i];
        double* output = outputs[i];

        for (int s = 0; s < nFrames; ++s, ++input, ++output) {
            if (*input >= 0) {
                // Make sure positive values can't go above the threshold:
                *output = fmin(*input, mThreshold);
            }
            else {
                // Make sure negative values can't go below the threshold:
                *output = fmax(*input, -mThreshold);
            }
            *output /= mThreshold;
        }
    }
}

void DistortionThing::Reset()
{
  TRACE;
  IMutexLock lock(this);
}

void DistortionThing::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
    case kThreshold:
        mThreshold = 1 - (GetParam(kThreshold)->Value() / 100.);
      break;

    default:
      break;
  }

}
