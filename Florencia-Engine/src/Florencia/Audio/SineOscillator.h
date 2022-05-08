#pragma once
#include <fstream>
#include <stdint.h>
#include "../Math/FloMath.h"

namespace Florencia {

	enum class WaveFileCompressionFormats {
		UNKNOWN = 0,
		PCM = 1, //Integer PCM
		FPCM = 3, //Floating point PCM
		ADPCM = 2, //
		A_LAW = 6, //
		MEW_LAW = 7, //
		IMAADPCM = 17, //
		ITU723ADPCM = 20, //
		GSM = 49, //
		ITU721ADPCM = 64, //
		MPEG = 80, //
		WFE = 65534 //WaveFormatExtensible
	};

	class SineOscillator {
	public:
		//Duration in seconds
		SineOscillator(float frequency, float amplitude, uint32_t duration, uint32_t channels = 2, uint32_t bitdepth = 16, uint32_t samplingRate = 44100);

		[[nodiscard]] double process() const;

		void SetSamplingRate(uint32_t samplingRate) { m_SamplingRate = samplingRate; }
		void SetBitDepth(uint32_t bitDepth) { m_BitDepth = bitDepth; }
		void SetChannels(uint32_t channels) { m_Channels = channels; }

		void SetFrequency(double frequency) { m_Frequency = frequency; }
		void SetAmplitude(double amplitude) { m_Amplitude = amplitude; }

		[[nodiscard]] uint32_t GetSampleRate() const { return m_SamplingRate; }
		[[nodiscard]] uint32_t GetDuration() const { return m_Duration; }
		[[nodiscard]] uint32_t GetChannels() const { return m_Channels; }
		[[nodiscard]] uint32_t GetBitDepth() const { return m_BitDepth; }
		[[nodiscard]] double GetAmplitude() const { return m_Amplitude; }
		[[nodiscard]] double GetFrequency() const { return m_Frequency; }
	private:
		double m_Frequency, m_Amplitude, m_Offset = 0.0f;
		mutable double m_Angle = 0.0f;
		uint32_t m_SamplingRate, m_BitDepth, m_Channels, m_Duration;
	};

	class SineOscillatorAudioFileCreator {
	public:
		SineOscillatorAudioFileCreator(SineOscillator& oscillator, std::string_view filepath);
	private:
		//Size is in bytes
		template <typename T> void writeToFile(T value, int size) { m_AudioFile.write(reinterpret_cast<const char*>(&value), size); }

		const SineOscillator& m_Oscillator;
		std::ofstream m_AudioFile;
	};

}
