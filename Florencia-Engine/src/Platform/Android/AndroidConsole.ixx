export module AndroidConsole;
import Console;

export namespace Florencia {

	class AndroidConsole : public Console {
	public:
		AndroidConsole() {}
		~AndroidConsole() {}
		bool CreateNewConsole() override { return false; }
		bool ReleaseConsole() override { return false; }
	private:

	};

}