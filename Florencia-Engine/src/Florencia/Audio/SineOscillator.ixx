export module SineOscillator;
import <stdint.h>;
import <fstream>;
import FloMath;

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

	export class SineOscillator {
	public:
		//Duration in seconds
		SineOscillator(float frequency, float amplitude, uint32_t duration, uint32_t channels = 2, uint32_t bitdepth = 16, uint32_t samplingRate = 44100)
			: m_Frequency(frequency), m_Amplitude(amplitude), m_Duration(duration), m_BitDepth(bitdepth), m_SamplingRate(samplingRate), m_Channels(channels) {
			m_Offset = 2 * FloMath::Pi();
		}

		[[nodiscard]] double process() const {
			const double sample = m_Amplitude * FloMath::sin(m_Angle);
			m_Angle = m_Angle + m_Offset * m_Frequency / m_SamplingRate;
			return sample;
		}

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

	export class SineOscillatorAudioFileCreator {
	public:
		SineOscillatorAudioFileCreator(SineOscillator& oscillator, std::string_view filepath) : m_Oscillator(oscillator) {
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
	private:
		//Size is in bytes
		template <typename T> void writeToFile(T value, int size) { m_AudioFile.write(reinterpret_cast<const char*>(&value), size); }

		const SineOscillator& m_Oscillator;
		std::ofstream m_AudioFile;
	};

}