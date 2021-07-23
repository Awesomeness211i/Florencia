export module AudioFile;
import <string>;

namespace Florencia {

	export class AudioFile {
	public:
		AudioFile() = default;
		virtual ~AudioFile() = default;

		virtual void Open(std::string_view filepath) = 0;

	};

}