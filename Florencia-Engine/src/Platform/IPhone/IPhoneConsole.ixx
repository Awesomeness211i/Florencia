export module IPhoneConsole;
import Console;

export namespace Florencia {

	class IPhoneConsole : public Console {
	public:
		IPhoneConsole() {}
		~IPhoneConsole() {}
		bool CreateNewConsole() override { return false; }
		bool ReleaseConsole() override { return false; }
	private:

	};

}