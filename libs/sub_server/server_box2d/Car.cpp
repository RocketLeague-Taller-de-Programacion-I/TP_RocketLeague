#include <memory>
#include "Car.h"
#include "box2d/box2d.h"
#define BALL 0x0002
#define CAR -3

#define FLIPYHEIGHT 2
#define ONEJUMP 0.5
#define ONEJUMPFORCE 7000
#define TWOJUMPFORCE 6000
#define XFORCE 50
#define TURBOXFORCE 75

Car::Car(b2World* world, uint8_t& id) : id(id), turboOn(false), movingLeft(false), movingRight(false), facingRight(true) {
    b2Vec2 vertices[8];

    vertices[0].Set(-1.5f, -.25f);
    vertices[1].Set(1.5f, -.25f);
    vertices[2].Set(-1.5f, 1.f);
    vertices[3].Set(1.5f, 1.f);

    myUserData = std::make_unique<MyFixtureUserDataType>();
    fixDef.userData.pointer = reinterpret_cast<uintptr_t>(myUserData.get());
    myUserData->mObjectType = 3;
    chassis.Set(vertices, 4);
    bd.type = b2_dynamicBody;
    bd.position.Set(20.0f, 1.0f);
    fixDef.density = 1.f;
    fixDef.restitution = 0.2f;
    fixDef.shape = &chassis;
    fixDef.filter.groupIndex = CAR;
    m_car = world->CreateBody(&bd);
    myUserData->mOwningFixture =  m_car->CreateFixture(&fixDef);
    myUserData->mOwningFixture->SetFilterData(fixDef.filter);
    myUserData->facingRight = &this->facingRight;
    myUserData->id = this->id;

    // Down sensor
    b2Vec2 vertDown[4];
    vertDown[0].Set(-1.25f, -.5f);
    vertDown[1].Set(1.25f,-.5f);
    vertDown[2].Set(-1.25f, .05f);
    vertDown[3].Set(1.25f, .05f);
    b2PolygonShape down;
    down.Set(vertDown, 4);
    b2FixtureDef fixDefDown;
    fixDefDown.density = 1.f;
    fixDefDown.restitution = 0.1f;
    fixDefDown.shape = &down;
    fixDefDown.filter.groupIndex = CAR;
    fixDefDown.isSensor = true;
    userDataDown = std::make_unique<MyFixtureUserDataType>();
    fixDefDown.userData.pointer = reinterpret_cast<uintptr_t>(userDataDown.get());
    userDataDown->mObjectType = SENSORDOWN;  //  Down
    userDataDown->mOwningFixture =  m_car->CreateFixture(&fixDefDown);
    userDataDown->mOwningFixture->SetFilterData(fixDefDown.filter);
    userDataDown->id = this->id;

    // Left sensor
    b2Vec2 vertLeft[4];
    vertLeft[0].Set(-1.75f, 0.f);
    vertLeft[1].Set(-1.25f,0.f);
    vertLeft[2].Set(-1.75f, .75f);
    vertLeft[3].Set(-1.25f, .75f);
    b2PolygonShape left;
    left.Set(vertLeft, 4);
    b2FixtureDef fixDefLeft;
    fixDefLeft.density = 1.f;
    fixDefLeft.restitution = 0.1f;
    fixDefLeft.shape = &left;
    fixDefLeft.filter.groupIndex = CAR;
    fixDefLeft.isSensor = true;
    userDataLeft = std::make_unique<MyFixtureUserDataType>();
    fixDefLeft.userData.pointer = reinterpret_cast<uintptr_t>(userDataLeft.get());
    userDataLeft->mObjectType = SENSORLEFT;  //  Left
    userDataLeft->mOwningFixture =  m_car->CreateFixture(&fixDefLeft);
    userDataLeft->mOwningFixture->SetFilterData(fixDefLeft.filter);
    userDataLeft->facingRight = &this->facingRight;
    userDataLeft->id = this->id;

    // Right sensor
    b2Vec2 vertRight[4];
    vertRight[0].Set(1.25f, 0.f);
    vertRight[1].Set(1.75f,0.f);
    vertRight[2].Set(1.25f, .75f);
    vertRight[3].Set(1.75f, .75f);
    b2PolygonShape right;
    right.Set(vertRight, 4);
    b2FixtureDef fixDefRight;
    fixDefRight.density = 1.f;
    fixDefRight.restitution = 0.1f;
    fixDefRight.shape = &right;
    fixDefRight.filter.groupIndex = CAR;
    fixDefRight.isSensor = true;
    userDataRight = std::make_unique<MyFixtureUserDataType>();
    fixDefRight.userData.pointer = reinterpret_cast<uintptr_t>(userDataRight.get());
    userDataRight->mObjectType = SENSORRIGHT;  //  Right
    userDataRight->mOwningFixture =  m_car->CreateFixture(&fixDefRight);
    userDataRight->mOwningFixture->SetFilterData(fixDefRight.filter);
    userDataRight->facingRight = &this->facingRight;
    userDataRight->id = this->id;
    // Upper sensor
    b2Vec2 vertUp[4];
    vertUp[0].Set(-1.25f, .75f);
    vertUp[1].Set(1.25f,.75f);
    vertUp[2].Set(-1.25f, 1.15f);
    vertUp[3].Set(1.25f, 1.15f);
    b2PolygonShape up;
    up.Set(vertUp, 4);
    b2FixtureDef fixDefUp;
    fixDefUp.density = 1.f;
    fixDefUp.restitution = 0.1f;
    fixDefUp.shape = &up;
    fixDefUp.filter.groupIndex = CAR;
    fixDefUp.isSensor = true;
    userDataUp = std::make_unique<MyFixtureUserDataType>();
    fixDefUp.userData.pointer = reinterpret_cast<uintptr_t>(userDataUp.get());
    userDataUp->mObjectType = SENSORUP;  //  Up
    userDataUp->mOwningFixture =  m_car->CreateFixture(&fixDefUp);
    userDataUp->mOwningFixture->SetFilterData(fixDefUp.filter);
    userDataUp->id = this->id;
}
void Car::goRight() {
    if (this->m_car->GetPosition().y > FLIPYHEIGHT) {
        m_car->ApplyTorque(-50.0, true);
        return;
    }
    if (turboOn) {
        m_car->ApplyForce(b2Vec2(TURBOXFORCE, 0), m_car->GetWorldCenter(), true);
        turboOn = false;
        return;
    }
    //  ApplyForceToCenter
    m_car->ApplyForce(b2Vec2(XFORCE, 0), m_car->GetWorldCenter(), true);
}
//
void Car::goLeft() {
    if (this->m_car->GetPosition().y > FLIPYHEIGHT) {
        m_car->ApplyTorque(50.0, true);
        return;
    }
    if (turboOn) {
        m_car->ApplyForce(b2Vec2(-TURBOXFORCE,0), m_car->GetWorldCenter(), true);
        turboOn = false;
        return;
    }
    m_car->ApplyForce(b2Vec2(-XFORCE, 0), m_car->GetWorldCenter(), true);
}


void Car::turbo() {
    this->turboOn = true;
}
void Car::jump() {
    check_y_pos();
}

Car::~Car() { }

//  OK
void Car::check_y_pos() {
    if (Y() > MAXY) { return; }
    if (Y() > ONEJUMP) {
        m_car->ApplyForce(b2Vec2(0, TWOJUMPFORCE), m_car->GetWorldCenter(), true);
        return;
    }
    m_car->ApplyForce(b2Vec2(0, ONEJUMPFORCE), m_car->GetWorldCenter(), true);
}
float Car::Y() {
    return this->m_car->GetPosition().y;
}
float Car::X() {
    return this->m_car->GetPosition().x;
}

float Car::angle() {
    return this->m_car->GetAngle();
}

float Car::angleDeg() {
    return (angle()*RADTODEG);
}

uint8_t Car::getId() {
    return this->id;
}
void Car::startMovingRight() {
    this->movingRight = true;
    this->facingRight = true;
    this->movingLeft = false;
}
void Car::startMovingLeft() {
    this->movingRight = false;
    this->facingRight = false;
    this->movingLeft = true;
}
void Car::stopMovingRight() {
    this->movingRight = false;
}
void Car::stopMovingLeft() {
    this->movingLeft = false;
}
void Car::update() {
    if (movingRight and X() < 38.0) {
        goRight();
    }
    if (movingLeft and X() > 1) {
        goLeft();
    }
    if(X() > 39.0) {
        this->m_car->SetTransform(b2Vec2(38.0, Y()), true);
        m_car->ApplyLinearImpulseToCenter(b2Vec2(-10,0), true);
    }
    if(X() < 0.5) {
        this->m_car->SetTransform(b2Vec2(0.5, Y()), true);
        m_car->ApplyLinearImpulseToCenter(b2Vec2(10,0), true);
    }
}
bool Car::facingWhere() {
    return this->facingRight;
}
uint8_t Car::carId() {
    return this->id;
}