#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "car.cpp"

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];
class ICar* car;

void selectCarType(int answer);
void getAnwerAndCheckIsValid(int& answer, char  buf[100], int& retFlag);
void getAndParseCommand(char  buf[100]);
void isExitCommand(char  buf[100], int& retFlag);
void updateStepAfterRun(int& step, int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

void printScreen(int step) {
    if (step == CarType_Q)
    {
        printf(CLEAR_SCREEN);

        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("� ���� Ÿ���� �����ұ��?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (step == Engine_Q)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. ���峭 ����\n");
    }
    else if (step == brakeSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (step == SteeringSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (step == Run_Test)
    {
        printf(CLEAR_SCREEN);
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("0. ó�� ȭ������ ���ư���\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    printf("===============================\n");

    printf("INPUT > ");
}

bool isValidStepAndAnswer(int step, int answer) {
    if (step == CarType_Q && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return false;
    }

    if (step == Engine_Q && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        delay(800);
        return false;
    }

    if (step == brakeSystem_Q && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return false;
    }

    if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
        delay(800);
        return false;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delay(800);
        return false;
    }

    return true;
}

void updateStepAfterDelay(int& step) {
    delay(800);
    step++;
}

void updateStepAfterRun(int& step, int answer)
{
    if (answer == 0 && step == Run_Test)
    {
        step = CarType_Q;
        return;
    }

    if (answer == 0 && step >= 1)
    {
        step -= 1;
        return;
    }

    if (step == CarType_Q)
    {
        selectCarType(answer);
        updateStepAfterDelay(step);
    }
    else if (step == Engine_Q)
    {
        selectEngine(answer);
        updateStepAfterDelay(step);
    }
    else if (step == brakeSystem_Q)
    {
        selectbrakeSystem(answer);
        updateStepAfterDelay(step);
    }
    else if (step == SteeringSystem_Q)
    {
        selectSteeringSystem(answer);
        updateStepAfterDelay(step);
    }
    else if (step == Run_Test && answer == 1)
    {
        runProducedCar();
        delay(2000);
    }
    else if (step == Run_Test && answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }
}

void getAndParseCommand(char buf[100])
{
    fgets(buf, sizeof(buf), stdin);

    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

bool isExitCommand(char buf[100])
{
    if (strcmp(buf, "exit"))
        return false;
    printf("���̹���\n");
    return true;
}

bool getAnwerAndCheckIsValid(int& answer, char buf[100])
{
    char* checkNumber;
    answer = strtol(buf, &checkNumber, 10);

    if (*checkNumber == '\0')
        return true;

    printf("ERROR :: ���ڸ� �Է� ����\n");
    delay(800);
    return false;
}

int main()
{
    char buf[100];
    int step = CarType_Q;
    int answer;

    while (1)
    {
        printScreen(step);

        getAndParseCommand(buf);

        if (isExitCommand(buf))
            break;

        if (!getAnwerAndCheckIsValid(answer, buf))
            continue;

        if (!isValidStepAndAnswer(step, answer))
            continue;

        updateStepAfterRun(step, answer);
    }
}

void selectCarType(int answer)
{
    CarFactory carFactory;
    car = carFactory.createCar(answer);
    car->printLog();
}

void selectEngine(int answer)
{
    EngineFactory engineFactory;
    car->setEngine(engineFactory.createEngine(answer));
    car->mEngine->printLog();
}

void selectbrakeSystem(int answer)
{
    BrakeFactory brakeFactory;
    car->setBrake(brakeFactory.createBrake(answer));
    car->mBrake->printLog();
}

void selectSteeringSystem(int answer)
{
    SteeringFactory steeringFactory;
    car->setSteering(steeringFactory.createSteering(answer));
    car->mSteering->printLog();
}

int isValidCheck()
{
    return car->isValid(0);
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (car->mEngine->getType() == 4)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            printf("Car Type : %s\n", car->getName().c_str());
            printf("Engine : %s\n", car->mEngine->getName().c_str());
            printf("Brake System : %s\n", car->mBrake->getName().c_str());
            printf("SteeringSystem : %s\n", car->mSteering->getName().c_str());
            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    car->isValid(1);
}

#endif