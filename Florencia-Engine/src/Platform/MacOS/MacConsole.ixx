export module MacConsole;
import Console;

export namespace Florencia {

	class MacConsole : public Console {
	public:
		MacConsole() {}
		~MacConsole() {}
		bool CreateNewConsole() override { return false; }
		bool ReleaseConsole() override { return false; }
	private:

	};

}