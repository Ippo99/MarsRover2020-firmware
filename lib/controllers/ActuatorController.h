#pragma once

#include "mbed.h"
#include "Motor.h"
#include "Encoder.h"
#include "PID.h"
#include "PinNames.h"

static DigitalIn NULL_DIGITAL_IN = DigitalIn(NC);

class ActuatorController {

public:

	typedef enum t_actuatorControlMode {
		motorPower,
		velocity,
		position
	} t_actuatorControlMode;

	typedef struct {
		t_actuatorControlMode defaultControlMode = motorPower;

		float minMotorPower_Percentage = -1.0, maxMotorPower_Percentage = +1.0;
		float minVelocity_DegreesPerSec = -10.0, maxVelocity_DegreesPerSec = +10.0;
		float minAngle_Degrees = -90, maxAngle_Degrees = +90;

		PID::t_pidConfig velocityPID, positionPID;
	} t_actuatorConfig;


	ActuatorController(t_actuatorConfig actuatorConfig, 
					   Motor &motor, Encoder &encoder, 
					   DigitalIn &limSwitchMin = NULL_DIGITAL_IN, 
					   DigitalIn &limSwitchMax = NULL_DIGITAL_IN);

	mbed_error_status_t setControlMode(t_actuatorControlMode controlMode);
	
	mbed_error_status_t setMotorPower_Percentage(float percentage);
	mbed_error_status_t setVelocity_DegreesPerSec(float degreesPerSec);
	mbed_error_status_t setAngle_Degrees(float degrees);

	t_actuatorControlMode getControlMode();

	float getMotorPower_Percentage();
	float getVelocity_DegreesPerSec();
	float getAngle_Degrees();

	void update();

private:

	t_actuatorControlMode m_controlMode;
	t_actuatorConfig m_actuatorConfig;

	Motor &r_motor;
	Encoder &r_encoder;
	DigitalIn &r_limSwitchMin;
	DigitalIn &r_limSwitchMax;

	bool m_limSwitchMin_Connected;
	bool m_limSwitchMax_Connected;

	PID m_velocityPIDController;
	PID m_positionPIDController;

	Timer updateTimer;

	void initializePIDControllers();

	bool isLimSwitchMinTriggered();
	bool isLimSwitchMaxTriggered();
	bool isPastMinAngle();
	bool isPastMaxAngle();
};