module;
#include <fstream>
#include <iostream>
#include <stdint.h>
export module SineOscillator;
import Declarations;

namespace Florencia {

	export class SineOscillator {
	public:
		//Duration in seconds
		SineOscillator(float frequency, float amplitude, uint32_t duration, uint32_t bitdepth = 16, uint32_t samplingRate = 44100, uint32_t channels = 1)
			:m_Frequency(frequency), m_Amplitude(amplitude), m_Duration(duration), m_BitDepth(bitdepth), m_SamplingRate(samplingRate), m_Channels(channels) {
			m_Offset = 2 * FloMath::pi;
		}
		double process() {
			auto sample = m_Amplitude * sin(m_Angle);
			m_Angle += m_Offset * m_Frequency / m_SamplingRate;
			return sample;
		}

		void SetFrequency(double frequency) { m_Frequency = frequency; }

		uint32_t GetSampleRate() { return m_SamplingRate; }
		uint32_t GetDuration() { return m_Duration; }
		uint32_t GetChannels() { return m_Channels; }
		uint32_t GetBitDepth() { return m_BitDepth; }
	private:
		double m_Frequency, m_Amplitude, m_Angle = 0.0f, m_Offset = 0.0f;
		uint32_t m_SamplingRate, m_BitDepth, m_Channels, m_Duration;
	};

	export class SineOscillatorAudioFileCreator {
	public:
		SineOscillatorAudioFileCreator(SineOscillator& oscillator, const std::string& filepath) :m_Oscillator(oscillator) {
			auto maxAmplitude = std::pow(2, oscillator.GetBitDepth() - 1) - 1;
			m_AudioFile.open(filepath, std::ios::binary);
			//Header Chunk
			m_AudioFile << "RIFF";
			m_AudioFile << "----";
			m_AudioFile << "WAVE";
			//Format Chunk
			m_AudioFile << "fmt ";
			writeToFile(16, 4); //Size
			writeToFile(1, 2); //Compression Code
			writeToFile(oscillator.GetChannels(), 2); //Channels
			writeToFile(oscillator.GetSampleRate(), 4); //Sample Rate
			writeToFile(oscillator.GetSampleRate() * oscillator.GetBitDepth() / 8, 4); //Byte Rate
			writeToFile(oscillator.GetBitDepth() / 8, 2); //Block align
			writeToFile(oscillator.GetBitDepth(), 2); //Bit Depth
			//Data Chunk
			m_AudioFile << "data";
			m_AudioFile << "----";
			int startpos = (int)m_AudioFile.tellp();
			for (uint32_t i = 0; i < oscillator.GetSampleRate() * oscillator.GetDuration() / 2; i++) {
				auto sample = oscillator.process();
				int intSample = static_cast<int>(sample * maxAmplitude);
				writeToFile(intSample, 2);
			}
			oscillator.SetFrequency(524.0);
			for (uint32_t i = 0; i < oscillator.GetSampleRate() * oscillator.GetDuration() / 2; i++) {
				auto sample = oscillator.process();
				int intSample = static_cast<int>(sample * maxAmplitude);
				writeToFile(intSample, 2);
			}
			int endpos = (int)m_AudioFile.tellp();

			m_AudioFile.seekp(static_cast<std::streampos>(startpos) - static_cast<std::streampos>(4));
			writeToFile(endpos - startpos, 4); //Size

			m_AudioFile.seekp(4, std::ios::beg);
			writeToFile(endpos - 8, 4);

			m_AudioFile.close();
		}
	private:
		void writeToFile(int value, int size) { m_AudioFile.write(reinterpret_cast<const char*>(&value), size); }

		SineOscillator& m_Oscillator;
		std::ofstream m_AudioFile;
	};

}