#include "headers.h"

class IEngine : public IProduct {
public:
	void printLog() override {
		std::cout << mName << " 엔진을 선택하셨습니다.\n";
	}
};

class GmEngine : public IEngine {
public:
	GmEngine() {
		mName = "GM";
		mType = GM;
	}
};

class ToyotaEngine : public IEngine {
public:
	ToyotaEngine() {
		mName = "TOYOTA";
		mType = TOYOTA;
	}
};

class WiaEngine : public IEngine {
public:
	WiaEngine() {
		mName = "WIA";
		mType = WIA;
	}
};

class BreakEngine : public IEngine {
public:
	BreakEngine() {
		mType = 4;
	}

	void printLog() override {
		return;
	}
};

class EngineFactory {
public:
	IEngine* createEngine(int type) {
		if (type == 1)
			return new GmEngine();
		if (type == 2)
			return new ToyotaEngine();
		if (type == 3)
			return new WiaEngine();
		if (type == 4)
			return new BreakEngine();
	}
};