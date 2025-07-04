#include "headers.h"

class ISteering : public IProduct {
public:
	void printLog() override {
		std::cout << mName << " 조향장치를 선택하셨습니다.\n";
	}
};

class BoschSteering : public ISteering {
public:
	BoschSteering() {
		mName = "BOSCH";
		mType = BOSCH_S;
	}
};

class MobisSteering : public ISteering {
public:
	MobisSteering() {
		mName = "MOBIS";
		mType = MOBIS;
	}
};

class SteeringFactory {
public:
	ISteering* createSteering(int type) {
		if (type == 1)
			return new BoschSteering();
		if (type == 2)
			return new MobisSteering();
	}
};