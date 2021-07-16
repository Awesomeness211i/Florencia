export module Console;

export namespace Florencia {

	class Console {
	public:
		Console() = default;
		virtual ~Console() = default;

		virtual bool CreateNewConsole() = 0;
		virtual bool ReleaseConsole() = 0;
	};

}