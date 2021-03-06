﻿#include <math.h>

enum OscillatorMode {
	OSCILLATOR_MODE_SINE,
	OSCILLATOR_MODE_SAW,
	OSCILLATOR_MODE_SQUARE,
	OSCILLATOR_MODE_TRIANGLE
};

class Oscillator {
private:
	OscillatorMode mOscillatorMode;
	const double mPI;
	double mFrequency;
	double mPhase;
	double mSampleRate;
	double mPhaseIncrement;
	const double twoPI = 2 * mPI;
	bool isMuted;
	
public:
	
	Oscillator() :
		mOscillatorMode(OSCILLATOR_MODE_SINE),
		mPI(2 * acos(0.0)),
		twoPI(2 * mPI), // This line is new
		isMuted(true),  // And this line
		mFrequency(440.0),
		mPhase(0.0),
		mSampleRate(44100.0) {
		updateIncrement();
	};
	inline void setMuted(bool muted) { isMuted = muted; }
	double Oscillator::nextSample() {
		double value = 0.0;
		if (isMuted) return value;

		switch (mOscillatorMode) {
		case OSCILLATOR_MODE_SINE:
			value = sin(mPhase);
			break;
		case OSCILLATOR_MODE_SAW:
			value = 1.0 - (2.0 * mPhase / twoPI);
			break;
		case OSCILLATOR_MODE_SQUARE:
			if (mPhase <= mPI) {
				value = 1.0;
			}
			else {
				value = -1.0;
			}
			break;
		case OSCILLATOR_MODE_TRIANGLE:
			value = -1.0 + (2.0 * mPhase / twoPI);
			value = 2.0 * (fabs(value) - 0.5);
			break;
		}
		mPhase += mPhaseIncrement;
		while (mPhase >= twoPI) {
			mPhase -= twoPI;
		}
		return value;
	}
	void Oscillator::setMode(OscillatorMode mode) {
		mOscillatorMode = mode;
	}

	void Oscillator::setFrequency(double frequency) {
		mFrequency = frequency;
		updateIncrement();
	}

	void Oscillator::setSampleRate(double sampleRate) {
		mSampleRate = sampleRate;
		updateIncrement();
	}

	void Oscillator::updateIncrement() {
		mPhaseIncrement = mFrequency * 2 * mPI / mSampleRate;
	}
	void Oscillator::generate(double* buffer, int nFrames) {
		
		switch (mOscillatorMode) {
		case OSCILLATOR_MODE_SINE:
			for (int i = 0; i < nFrames; i++) {
				buffer[i] = sin(mPhase);
				mPhase += mPhaseIncrement;
				while (mPhase >= twoPI) {
					mPhase -= twoPI;
				}
			}
			break;
		case OSCILLATOR_MODE_SAW:
			for (int i = 0; i < nFrames; i++) {
				buffer[i] = 1.0 - (2.0 * mPhase / twoPI);
				mPhase += mPhaseIncrement;
				while (mPhase >= twoPI) {
					mPhase -= twoPI;
				}
			}
			break;
		case OSCILLATOR_MODE_SQUARE:
			for (int i = 0; i < nFrames; i++) {
				if (mPhase <= mPI) {
					buffer[i] = 1.0;
				}
				else {
					buffer[i] = -1.0;
				}
				mPhase += mPhaseIncrement;
				while (mPhase >= twoPI) {
					mPhase -= twoPI;
				}
			}
			break;
		case OSCILLATOR_MODE_TRIANGLE:
			for (int i = 0; i < nFrames; i++) {
				double value = -1.0 + (2.0 * mPhase / twoPI);
				buffer[i] = 2.0 * (fabs(value) - 0.5);
				mPhase += mPhaseIncrement;
				while (mPhase >= twoPI) {
					mPhase -= twoPI;
				}
			}
			break;
		}
	}
};
