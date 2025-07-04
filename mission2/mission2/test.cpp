#include "gmock/gmock.h"
#include "question.cpp"

//steering
TEST(Steering, BoschSteering) {
	SteeringFactory sf;
	ISteering* steering = sf.createSteering(BOSCH_S);
	EXPECT_EQ(BOSCH_S, steering->getType());
}
TEST(Steering, MobisSteering) {
	SteeringFactory sf;
	ISteering* steering = sf.createSteering(MOBIS);
	EXPECT_EQ(MOBIS, steering->getType());
}

//engine
TEST(Engine, GmEngine) {
	EngineFactory ef;
	IEngine* engine = ef.createEngine(GM);
	EXPECT_EQ(GM, engine->getType());
}
TEST(Engine, ToyotaEngine) {
	EngineFactory ef;
	IEngine* engine = ef.createEngine(TOYOTA);
	EXPECT_EQ(TOYOTA, engine->getType());
}
TEST(Engine, WiaEngine) {
	EngineFactory ef;
	IEngine* engine = ef.createEngine(WIA);
	EXPECT_EQ(WIA, engine->getType());
}
TEST(Engine, BreakEngine) {
	EngineFactory ef;
	IEngine* engine = ef.createEngine(4);
	EXPECT_EQ(4, engine->getType());
}

//brake
TEST(Brake, GmEngine) {
	BrakeFactory bf;
	IBrake* brake = bf.createBrake(MANDO);
	EXPECT_EQ(MANDO, brake->getType());
}
TEST(Brake, ToyotaEngine) {
	BrakeFactory bf;
	IBrake* brake = bf.createBrake(CONTINENTAL);
	EXPECT_EQ(CONTINENTAL, brake->getType());
}
TEST(Brake, WiaEngine) {
	BrakeFactory bf;
	IBrake* brake = bf.createBrake(BOSCH_B);
	EXPECT_EQ(BOSCH_B, brake->getType());
}

//car
TEST(Car, Sedan) {
	CarFactory cf;
	ICar* car = cf.createCar(SEDAN);
	EXPECT_EQ(MANDO, car->getType());
}
TEST(Car, Suv) {
	CarFactory cf;
	ICar* car = cf.createCar(SUV);
	EXPECT_EQ(CONTINENTAL, car->getType());
}
TEST(Car, Truck) {
	CarFactory cf;
	ICar* car = cf.createCar(TRUCK);
	EXPECT_EQ(BOSCH_B, car->getType());
}
TEST(Car, isValidSedanFalse) {
	ICar* car = new Sedan();
	car->setBrake(new ContinentalBrake());
	int ret = car->isValid(1);
	EXPECT_EQ(ret, false);
}
TEST(Car, isValidSUVFalse) {
	ICar* car = new Suv();
	car->setEngine(new ToyotaEngine());
	int ret = car->isValid(1);
	EXPECT_EQ(ret, false);
}
TEST(Car, isValidTruckFalseEngine) {
	ICar* car = new Truck();
	car->setEngine(new WiaEngine());
	int ret = car->isValid(1);
	EXPECT_EQ(ret, false);
}
TEST(Car, isValidTruckFalseBrake) {
	ICar* car = new Truck();
	car->setEngine(new ToyotaEngine());
	car->setBrake(new MandoBrake());
	int ret = car->isValid(1);
	EXPECT_EQ(ret, false);
}
TEST(Car, isValidFalseBosch) {
	ICar* car = new Sedan();
	car->setBrake(new BoschBrake());
	car->setSteering(new MobisSteering());
	int ret = car->isValid(1);
	EXPECT_EQ(ret, false);
}
TEST(Car, isValidTrue) {
	ICar* car = new Sedan();
	car->setBrake(new BoschBrake());
	car->setSteering(new BoschSteering());
	int ret = car->isValid(1);
	EXPECT_EQ(ret, true);
}

//Question
TEST(Question, getAndParseCommand) {
	Question q;
	q.getAndParseCommand();
	int ret = strlen(q.buf);
	EXPECT_EQ(ret, 1);
}

TEST(Question, isExitCommandTrue) {
	Question q;
	q.buf[0] = 'e';
	q.buf[1] = 'x';
	q.buf[2] = 'i';
	q.buf[3] = 't';
	bool ret = q.isExitCommand();
	EXPECT_TRUE(ret);
}

TEST(Question, isExitCommandFalse) {
	Question q;
	bool ret = q.isExitCommand();
	EXPECT_FALSE(ret);
}

TEST(Question, getAnswerCheckIsValidTrue) {
	Question q;
	q.buf[0] = '0';
	bool ret = q.getAnwerAndCheckIsValid();
	EXPECT_TRUE(ret);
}

TEST(Question, getAnswerCheckIsValidFalse) {
	Question q;
	q.buf[0] = 'k';
	bool ret = q.getAnwerAndCheckIsValid();
	EXPECT_FALSE(ret);
}

TEST(Question, isValidStepAndAnswerFalseByCar) {
	Question q;
	q.step = CarType_Q;
	q.answer = 4;
	bool ret = q.isValidStepAndAnswer();
	EXPECT_FALSE(ret);
}

TEST(Question, isValidStepAndAnswerFalseByEngine) {
	Question q;
	q.step = Engine_Q;
	q.answer = 5;
	bool ret = q.isValidStepAndAnswer();
	EXPECT_FALSE(ret);
}

TEST(Question, isValidStepAndAnswerFalseByBrake) {
	Question q;
	q.step = brakeSystem_Q;
	q.answer = 4;
	bool ret = q.isValidStepAndAnswer();
	EXPECT_FALSE(ret);
}

TEST(Question, isValidStepAndAnswerFalseBySteering) {
	Question q;
	q.step = SteeringSystem_Q;
	q.answer = 4;
	bool ret = q.isValidStepAndAnswer();
	EXPECT_FALSE(ret);
}

TEST(Question, isValidStepAndAnswerFalseByRunTest) {
	Question q;
	q.step = Run_Test;
	q.answer = 4;
	bool ret = q.isValidStepAndAnswer();
	EXPECT_FALSE(ret);
}

TEST(Question, isValidStepAndAnswerTrue) {
	Question q;
	q.step = Run_Test;
	q.answer = 1;
	bool ret = q.isValidStepAndAnswer();
	EXPECT_TRUE(ret);
}

TEST(Question, updateStepAfterRunCarStart) {
	Question q;
	q.step = Run_Test;
	q.answer = 0;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, CarType_Q);
}

TEST(Question, updateStepAfterRunCarBack) {
	Question q;
	q.step = Engine_Q;
	q.answer = 0;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, CarType_Q);
}

TEST(Question, updateStepAfterRunCar) {
	Question q;
	q.step = CarType_Q;
	q.answer = 1;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, Engine_Q);
}

TEST(Question, updateStepAfterRunEngine) {
	Question q;
	q.car = new Sedan();
	q.step = Engine_Q;
	q.answer = 1;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, brakeSystem_Q);
}

TEST(Question, updateStepAfterRunEngineBreak) {
	Question q;
	q.car = new Sedan();
	q.step = Engine_Q;
	q.answer = 4;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, brakeSystem_Q);
}

TEST(Question, updateStepAfterRunBrake) {
	Question q;
	q.car = new Sedan();
	q.step = brakeSystem_Q;
	q.answer = 1;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, SteeringSystem_Q);
}

TEST(Question, updateStepAfterRunSteering) {
	Question q;
	q.car = new Sedan();
	q.step = SteeringSystem_Q;
	q.answer = 1;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, Run_Test);
}

TEST(Question, getStep) {
	Question q;
	q.step = CarType_Q;
	int ret = q.getStep();
	EXPECT_EQ(ret, CarType_Q);
}

TEST(Question, updateStepAfterRunRunFail) {
	Question q;
	q.car = new Sedan();
	q.car->setBrake(new ContinentalBrake());
	q.step = Run_Test;
	q.answer = 1;
	q.updateStepAfterRun();
}

TEST(Question, updateStepAfterRunRunFailByEngine) {
	Question q;
	q.car = new Sedan();
	q.car->setBrake(new BoschBrake());
	q.car->setEngine(new BreakEngine());
	q.car->setSteering(new BoschSteering());
	q.step = Run_Test;
	q.answer = 1;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, Run_Test);
}

TEST(Question, updateStepAfterRunRunSuccess) {
	Question q;
	q.car = new Sedan();
	q.car->setBrake(new BoschBrake());
	q.car->setEngine(new ToyotaEngine());
	q.car->setSteering(new BoschSteering());
	q.step = Run_Test;
	q.answer = 1;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, Run_Test);
}

TEST(Question, updateStepAfterRunTest) {
	Question q;
	q.car = new Sedan();
	q.car->setBrake(new BoschBrake());
	q.car->setEngine(new ToyotaEngine());
	q.car->setSteering(new BoschSteering());
	q.step = Run_Test;
	q.answer = 2;
	q.updateStepAfterRun();
	EXPECT_EQ(q.step, Run_Test);
}