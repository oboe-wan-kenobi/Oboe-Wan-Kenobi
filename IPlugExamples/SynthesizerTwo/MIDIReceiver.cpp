#include "MIDIReceiver.h"
//pretzel

void MIDIReceiver::onMessageReceived(IMidiMsg* midiMessage) {
    IMidiMsg::EStatusMsg status = midiMessage->StatusMsg();
    // We're only interested in Note On/Off messages (not CC, pitch, etc.)
    if (status == IMidiMsg::kNoteOn || status == IMidiMsg::kNoteOff) {
        mMidiQueue.Add(midiMessage);
    }
}
