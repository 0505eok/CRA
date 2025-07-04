#include "headers.h"

class IBrake : public IProduct {
public:
	void printLog() override {
		std::cout << mName << " 제동장치를 선택하셨습니다.\n";
	}
};

class MandoBrake : public IBrake {
public:
	MandoBrake() {
		mName = "MANDO";
		mType = MANDO;
	}
};

class ContinentalBrake : public IBrake {
public:
	ContinentalBrake() {
		mName = "CONTINENTAL";
		mType = CONTINENTAL;
	}
};

class BoschBrake : public IBrake {
public:
	BoschBrake() {
		mName = "BOSCH";
		mType = BOSCH_B;
	}
};

class BrakeFactory {
public:
	IBrake* createBrake(int type) {
		if (type == 1)
			return new MandoBrake();
		if (type == 2)
			return new ContinentalBrake();
		if (type == 3)
			return new BoschBrake();
	}
};