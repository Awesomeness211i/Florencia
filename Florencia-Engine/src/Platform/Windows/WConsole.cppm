export module WConsole;
import <iostream>;
import <stdint.h>;

export namespace Florencia {

	class WConsole {
	public:
		WConsole(int16_t minLength = 1024);
		bool CreateNewConsole();
		bool ReleaseConsole();
	private:
		bool AttachParentConsole();
		bool RedirectConsoleIO();
		void AdjustConsoleBuffer();
		int16_t m_MinLength;
	};
}