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
		std::cout << "���� Ÿ������ " << mName << "�� �����ϼ̽��ϴ�.\n";
	}
	int isValid(int printFlag) {
		if (mType == SEDAN) {
			if (mBrake->getType() == CONTINENTAL) {
				if (printFlag) {
					printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
					printf("Sedan���� Continental������ġ ��� �Ұ�\n");
				}
				return false;
			}
		}
		
		if (mType == SUV) {
			if (mEngine->getType() == TOYOTA) {
				if (printFlag) {
					printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
					printf("SUV���� TOYOTA���� ��� �Ұ�\n");
				}
				return false;
			}
		}
		
		if (mType == TRUCK) {
			if (mEngine->getType() == WIA) {
				if (printFlag) {
					printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
					printf("Truck���� WIA���� ��� �Ұ�\n");
				}
				return false;
			}
			if (mBrake->getType() == MANDO) {
				if (printFlag) {
					printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
					printf("Truck���� Mando������ġ ��� �Ұ�\n");
				}
				return false;
			}
		}

		if (mBrake->getType() == BOSCH_B && mSteering->getType() != BOSCH_S) {
			if (printFlag) {
				printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
				printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
			}
			return false;
		}

		if(printFlag)
			printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
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