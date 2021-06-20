export module LinuxConsole;
import Console;

export namespace Florencia {

	class LinuxConsole : public Console {
	public:
		LinuxConsole() {}
		~LinuxConsole() {}
		bool CreateNewConsole() override { return false; }
		bool ReleaseConsole() override { return false; }
	private:

	};

}