#include <Servo.h>

const int GATE_SERVO_MOTOR_PIN = 9;
const int IR_SENSOR_PIN = 7;

Servo gateServoMotor;

void setup() {

  Serial.begin(9600);
  // attach server motor to pin
  gateServoMotor.attach(GATE_SERVO_MOTOR_PIN);

  //IR pin is connected as input
  pinMode(IR_SENSOR_PIN, INPUT);

  closeGate();
}

void loop() {
  //detect the car is near gate by using IR sensor
  int isCarThere = digitalRead(IR_SENSOR_PIN);

  // if the car is detected
  if(isCarThere == 0){
      Serial.println("Car detected");
      // then open the gate
      // and keep it open for 5 seconds
      openGate();
  }
  // if the car is not detect
  else{
    // then close the gate
    closeGate();
  }

}

// opens gate by turning servo motor to 180 degree
void openGate(){
  Serial.println("Gate Opened");
  gateServoMotor.write(90);
  delay(3000);
}

// opens gate by turning servo motor to 90 degree
void closeGate(){
  Serial.println("Gate Closed");
  gateServoMotor.write(180);
  delay(1000);
}
