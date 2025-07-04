#include "headers.h"
#include "car.cpp"

class Question {
public:
    void getAndParseCommand()
    {
#ifdef _DEBUG
        buf[0] = 1;
        buf[1] = '\r';
        buf[2] = '\n';
#else
        fgets(buf, sizeof(buf), stdin);
#endif
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);
    }

    bool isExitCommand()
    {
        if (strcmp(buf, "exit"))
            return false;
        printf("���̹���\n");
        return true;
    }

    bool getAnwerAndCheckIsValid()
    {
        char* checkNumber;
        answer = strtol(buf, &checkNumber, 10);

        if (*checkNumber == '\0')
            return true;

        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(800);
        return false;
    }

    bool isValidStepAndAnswer() {
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

    void updateStepAfterRun()
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

    int getStep() 
    {
        return step;
    }

    char buf[100];
    int step = CarType_Q;
    int answer;
    class ICar* car;

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

    void updateStepAfterDelay(int& step) {
        delay(800);
        step++;
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

};