/*

  Peter Vanhevel
  peter.vanhevel@pandora.be
  https://github.com/PVanhevel/explorer
  2020 -

  LEFT refers to the left track drive
  RIGHT refers tot the right track drive

  wire layout between Frsky X8R and Arduino Uno:
               X8R    Uno
  red           +     5 V
  brown         -     Gnd
  blue+yellow  CH2     2                                                                                                            
  purple+white CH3     4

*/

#include <SPort.h>

#define SKETCH_VERSION      "V2.1"                                                                                               // Added telemetry

#define BAUDRATE          115200

#define LEFT_MOTOR             0
#define RIGHT_MOTOR            1

#define SPORT_PIN             10                                                                                                  // Software Serial

#define PPM_CENTER          1500
#define PPM_MIN PPM_CENTER - 500
#define PPM_MAX PPM_CENTER + 500

#define LEFT_FORWARD           0
#define LEFT_REVERSE           1
#define LEFT_CHANNEL_PIN       2
#define LEFT_DIRECTION_PIN    13                                                                                                   // Defined by Arduino motor shield layout
#define LEFT_PWM_PIN          11                                                                                                   // Defined by Arduino motor shield layout
#define LEFT_BRAKE_PIN         9                                                                                                   // Defined by Arduino motor shield layout 
//#define LEFT_CURSENS_PIN      A0                                                                                                 // Defined by Arduino motor shield layout

#define RIGHT_FORWARD          1
#define RIGHT_REVERSE          0
#define RIGHT_CHANNEL_PIN      4
#define RIGHT_DIRECTION_PIN   12                                                                                                   // Defined by Arduino motor shield layout
#define RIGHT_PWM_PIN          3                                                                                                   // Defined by Arduino motor shield layout
#define RIGHT_BRAKE_PIN        8                                                                                                   // Defined by Arduino motor shield layout 
//#define RIGHT_CURSENS_PIN     A1                                                                                                 // Defined by Arduino motor shield layout

volatile int ch1_autoPulsewidth, ch2_leftPulsewidth, ch3_rightPulsewidth, leftSpeed, rightSpeed;

SPortHub hub(0x12, SPORT_PIN);
CustomSPortSensor sensorA0(getSensorDataA0);
CustomSPortSensor sensorA1(getSensorDataA1);
CustomSPortSensor sensorA2(getSensorDataA2);
CustomSPortSensor sensorA3(getSensorDataA3);
CustomSPortSensor sensorA4(getSensorDataA4);
CustomSPortSensor sensorA5(getSensorDataA5);


void setup() {
  Serial.begin(BAUDRATE);
  setupTelemetry();
  setupReceiver();
  setupArdumoto();
  delay(5);                                                                                                                        // Delay to allow the Frsky receiver to start up after powering up the explorer
}


void loop() {
  rcMode();
  hub.handle();                                                                                                                    // Handle new data
}


void rcMode() {
  ch2_leftPulsewidth = pulseIn(LEFT_CHANNEL_PIN, HIGH, 25000);                                                                     // The pulseIn function measures the width of the Frsky PPM signal
  leftSpeed = map(ch2_leftPulsewidth, PPM_MIN, PPM_MAX, -500, 500);
  leftSpeed = constrain(leftSpeed, -255, 255);                                                                                     // Reverse polarity, depending on motor connections
  if (leftSpeed > 0) {
    driveArdumoto(LEFT_MOTOR, LEFT_FORWARD, leftSpeed);
  };
  if (leftSpeed < 0) {
    driveArdumoto(LEFT_MOTOR, LEFT_REVERSE, -leftSpeed);
  };

  ch3_rightPulsewidth = pulseIn(RIGHT_CHANNEL_PIN, HIGH, 25000);
  rightSpeed = map(ch3_rightPulsewidth, PPM_MIN, PPM_MAX, -500, 500);
  rightSpeed = constrain(rightSpeed, -255, 255);
  if (rightSpeed > 0) {
    driveArdumoto(RIGHT_MOTOR, RIGHT_FORWARD, rightSpeed);
  };
  if (rightSpeed < 0) {
    driveArdumoto(RIGHT_MOTOR, RIGHT_REVERSE, -rightSpeed);
  };
}


void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == LEFT_MOTOR)
  {
    digitalWrite(LEFT_DIRECTION_PIN, dir);
    analogWrite(LEFT_PWM_PIN, spd);
  }
  else if (motor == RIGHT_MOTOR)
  {
    digitalWrite(RIGHT_DIRECTION_PIN, dir);
    analogWrite(RIGHT_PWM_PIN, spd);
  }
}


void setupTelemetry()
{
  hub.registerSensor(sensorA0);                                                                                                     // Add sensor to the hub
  hub.registerSensor(sensorA1);                                                                                                     // Add sensor to the hub
  hub.registerSensor(sensorA2);                                                                                                     // Add sensor to the hub
  hub.registerSensor(sensorA3);                                                                                                     // Add sensor to the hub
  hub.registerSensor(sensorA4);                                                                                                     // Add sensor to the hub
  hub.registerSensor(sensorA5);                                                                                                     // Add sensor to the hub
  hub.begin();                                                                                                                      // Start listening
}


void setupArdumoto()
{
  pinMode(LEFT_PWM_PIN, OUTPUT);
  pinMode(RIGHT_PWM_PIN, OUTPUT);
  pinMode(LEFT_DIRECTION_PIN, OUTPUT);
  pinMode(RIGHT_DIRECTION_PIN, OUTPUT);

  analogWrite(LEFT_PWM_PIN, 0);
  analogWrite(RIGHT_PWM_PIN, 0);
  digitalWrite(LEFT_DIRECTION_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_PIN, LOW);
}


void setupReceiver()
{
  pinMode(LEFT_CHANNEL_PIN, INPUT);
  pinMode(RIGHT_CHANNEL_PIN, INPUT);
}


sportData getSensorDataA0(CustomSPortSensor* sensorA0) {
  sportData data;
  data.applicationId = 0x6000;                                                                                                     // Set the sensor id for the current data poll. Set to 0 to discard the data, skip to the next sensor.  You can easily name the sensor and scale its value in OpenTX.
  data.value = (uint32_t)(analogRead(A0));
  return data;
}


sportData getSensorDataA1(CustomSPortSensor* sensorA1) {
  sportData data;
  data.applicationId = 0x6100;                                                                                                     // Set the sensor id for the current data poll. Set to 0 to discard the data, skip to the next sensor.  You can easily name the sensor and scale its value in OpenTX.
  data.value = (uint32_t)(analogRead(A1));
  return data;
}

sportData getSensorDataA2(CustomSPortSensor* sensorA2) {
  sportData data;
  data.applicationId = 0x6200;                                                                                                     // Set the sensor id for the current data poll. Set to 0 to discard the data, skip to the next sensor.  You can easily name the sensor and scale its value in OpenTX.
  data.value = (uint32_t)(analogRead(A2));
  return data;
}

sportData getSensorDataA3(CustomSPortSensor* sensorA3) {
  sportData data;
  data.applicationId = 0x6300;                                                                                                     // Set the sensor id for the current data poll. Set to 0 to discard the data, skip to the next sensor.  You can easily name the sensor and scale its value in OpenTX.
  data.value = (uint32_t)(analogRead(A3));
  return data;
}

sportData getSensorDataA4(CustomSPortSensor* sensorA4) {
  sportData data;
  data.applicationId = 0x6400;                                                                                                     // Set the sensor id for the current data poll. Set to 0 to discard the data, skip to the next sensor.  You can easily name the sensor and scale its value in OpenTX.
  data.value = (uint32_t)(analogRead(A4));
  return data;
}

sportData getSensorDataA5(CustomSPortSensor* sensorA5) {
  sportData data;
  data.applicationId = 0x6500;                                                                                                     // Set the sensor id for the current data poll. Set to 0 to discard the data, skip to the next sensor.  You can easily name the sensor and scale its value in OpenTX.
  data.value = (uint32_t)(analogRead(A5));
  return data;
}
