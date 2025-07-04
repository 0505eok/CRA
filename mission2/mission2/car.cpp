#include "headers.h"
#include "engine.cpp"
#include "brake.cpp"
#include "steering.cpp"

class ICar : public IProduct {
public:
	void setEngine(IEngine* engine) {
		mEngine = engine;
	}
	void setBrake(IBrake* brake) {
		mBrake = brake;
	}
	void setSteering(ISteering* steering) {
		mSteering = steering;
	}
	void printLog() override {
		std::cout << "차량 타입으로 " << mName << "을 선택하셨습니다.\n";
	}
	int isValid(int printFlag) {
		if (mType == SEDAN) {
			if (mBrake->getType() == CONTINENTAL) {
				if (printFlag) {
					printf("자동차 부품 조합 테스트 결과 : FAIL\n");
					printf("Sedan에는 Continental제동장치 사용 불가\n");
				}
				return false;
			}
		}
		
		if (mType == SUV) {
			if (mEngine->getType() == TOYOTA) {
				if (printFlag) {
					printf("자동차 부품 조합 테스트 결과 : FAIL\n");
					printf("SUV에는 TOYOTA엔진 사용 불가\n");
				}
				return false;
			}
		}
		
		if (mType == TRUCK) {
			if (mEngine->getType() == WIA) {
				if (printFlag) {
					printf("자동차 부품 조합 테스트 결과 : FAIL\n");
					printf("Truck에는 WIA엔진 사용 불가\n");
				}
				return false;
			}
			if (mBrake->getType() == MANDO) {
				if (printFlag) {
					printf("자동차 부품 조합 테스트 결과 : FAIL\n");
					printf("Truck에는 Mando제동장치 사용 불가\n");
				}
				return false;
			}
		}

		if (mBrake->getType() == BOSCH_B && mSteering->getType() != BOSCH_S) {
			if (printFlag) {
				printf("자동차 부품 조합 테스트 결과 : FAIL\n");
				printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
			}
			return false;
		}

		if(printFlag)
			printf("자동차 부품 조합 테스트 결과 : PASS\n");
		return true;
	}

	IEngine* mEngine;
	IBrake* mBrake;
	ISteering* mSteering;
};

class Sedan : public ICar {
public:
	Sedan() {
		mName = "Sedan";
		mType = SEDAN;
	}
};

class Suv : public ICar {
public:
	Suv() {
		mName = "SUV";
		mType = SUV;
	}
};

class Truck : public ICar {
public:
	Truck() {
		mName = "Truck";
		mType = TRUCK;
	}
};

class CarFactory {
public:
	ICar* createCar(int type) {
		if (type == 1)
			return new Sedan();
		if (type == 2)
			return new Suv();
		if (type == 3)
			return new Truck();
	}
};