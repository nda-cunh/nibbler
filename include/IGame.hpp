
enum Event {
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ENTER, // enter-key
	CLOSE // Alt+F4 or cross window

};

class IPlugin {
	public:
		virtual void open() = 0;
		virtual void close() = 0;
		virtual void rect(int x, int y) = 0;
		virtual void iteration () = 0;
		virtual Event poll_event() = 0;

};

