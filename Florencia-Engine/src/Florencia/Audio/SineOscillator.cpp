#include "SineOscillator.h"

namespace Florencia {

	SineOscillator::SineOscillator(float frequency, float amplitude, uint32_t duration, uint32_t channels, uint32_t bitdepth, uint32_t samplingRate)
			: m_Frequency(frequency), m_Amplitude(amplitude), m_SamplingRate(samplingRate), m_BitDepth(bitdepth), m_Channels(channels), m_Duration(duration) {
			m_Offset = 2 * FloMath::Pi();
		}

	double SineOscillator::process() const  {
		const double sample = m_Amplitude * FloMath::sin(m_Angle);
		m_Angle = m_Angle + m_Offset * m_Frequency / m_SamplingRate;
		return sample;
	}

	SineOscillatorAudioFileCreator::SineOscillatorAudioFileCreator(Florencia::SineOscillator& oscillator, std::string_view filepath) : m_Oscillator(oscillator) {
		m_AudioFile.open(&filepath[0], std::ios::binary);
		if (m_AudioFile.is_open()) {
			//Header Chunk
			m_AudioFile << "RIFF"; //chunk id
			m_AudioFile << "----"; //chunk size
			m_AudioFile << "WAVE"; //format

			//Format Chunk
			m_AudioFile << "fmt "; //subchunk1 id
			writeToFile(16, 4); //subchunk1 size
			writeToFile(WaveFileCompressionFormats::PCM, 2); //audio format compression code
			writeToFile(oscillator.GetChannels(), 2); //number of channels
			writeToFile(oscillator.GetSampleRate(), 4); //sample rate
			writeToFile(oscillator.GetSampleRate() * oscillator.GetChannels() * oscillator.GetBitDepth() / 8, 4); //byte-rate = samplerate * channels * bitspersample / bitsinbyte
			writeToFile(oscillator.GetChannels() * oscillator.GetBitDepth() / 8, 2); //block align = channels * bitspersample / bitsinbyte
			writeToFile(oscillator.GetBitDepth(), 2); //bit depth = bitspersample

			//Data Sub-Chunk
			m_AudioFile << "data"; //subchunk2 id
			m_AudioFile << "----"; //subchunk2 size

			auto maxAmplitude = std::pow(2, oscillator.GetBitDepth() - 1) - 1;

			int startpos = (int)m_AudioFile.tellp();
			for(uint32_t i = 0; i < oscillator.GetSampleRate() * oscillator.GetDuration(); i++) {
				auto sample = oscillator.process();
				int intSample = static_cast<int>(sample * maxAmplitude);
				for(int j = 0; j < oscillator.GetChannels(); i++) {
					writeToFile(intSample, 2);
				}
			}
			int endpos = (int)m_AudioFile.tellp();
			m_AudioFile.seekp(startpos - 4);
			writeToFile(endpos - startpos, 4); //subchunk2 size

			m_AudioFile.seekp(4, std::ios::beg);
			writeToFile(endpos - 8, 4);
		}
		m_AudioFile.close();
	}

}
