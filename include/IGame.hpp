class IGame {
	public:
		virtual void open() = 0;
		virtual void close() = 0;
		virtual void rect(int x, int y) = 0;
		virtual void iteration () = 0;
};
