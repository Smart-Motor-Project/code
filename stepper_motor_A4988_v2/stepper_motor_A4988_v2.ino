// include libraries

#include <TimerOne.h>
#include <Wire.h>

// define secondary arduino address
#define I2C_ADDR 3

// defines pins numbers
// stepper motor pinout
#define stepPin 9
#define dirPin 6
#define STBY 2
#define MODE_1 7
#define MODE_2 8
#define FORWARD HIGH  // motor direction
#define REVERSE LOW   // motor direction

const uint32_t MICROSECOND = 1000000;
const uint16_t MILLISECOND = 1000;
const uint8_t THREAD_PITCH = 4;  // in millimeters, thread pitch of the actuator's screw
const uint16_t MICROSTEP = 64; // motor micro step size
const uint16_t GEAR_RATIO = 100; // worm gear ratio
const float NUM_ROTATIONS = 0.1; // number of rotations

// communication commands table
const char forward_cmd = 'F';
const char backward_cmd = 'B';
const char running_cmd = 'r';
const char stop_cmd = 's';
const char raduis_cmd = 'R';

//char rx_user_in;
String din_string = "";
float user_radius = 10.845;
float user_Q = 0.016666;
char run_char = stop_cmd; // refer to communication commands table

// stepper motor parameters
const uint16_t STEP_ROT = 200 * MICROSTEP;  // steps per rotation
const uint16_t DutyCycle = 0.5 * 1024;

// initialize variables
uint32_t old_period, period;
uint64_t StartTime;
bool start_flag = false;  //**change to true to start program
bool rx_flg = false;
bool adj_Q_flg = false;

// motor ISR variables
volatile uint32_t motor_rot = 0, microsteps = 0;




void setup() {
  Serial.begin(9600);
  init_Microsteps(MICROSTEP);
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, REVERSE);
  delay(10);
  Wire.begin(I2C_ADDR);  //begin i2c communciation as device 3
  Wire.onReceive(receiveI2C);
  Wire.onRequest(requestI2CData);
  //NOTE MOVE ALL THIS LATER
  //  Serial.print("rps max: ");
  //  Serial.print(rps_max, 12);
  //  Serial.print("   ,freq ");
  //  Serial.print(frequency);
  //  Serial.print(" Hz");
  //  Serial.print("   ,period ");
  //  Serial.print(period);
  //  Serial.println(" us");
}
void loop() {
  //  delay(1000);                    //USED FOR TESTING
  //  Serial.println(din_string);     //USED FOR TESTING
  if (rx_flg) motor_setup();
  if (adj_Q_flg && old_period != period) {
    if (period - old_period > 0)  Timer1.setPeriod(old_period++);    // smooth change of Q
    else Timer1.setPeriod(old_period--);    // smooth change of Q
  }
  else adj_Q_flg = false;
  if (start_flag) {
    uint64_t t1 = millis() - StartTime;
    static uint64_t t2 = 0;
    if (t1 - t2 >= 500) {
      t2 = t1;
      float freq = 1.0 * MILLISECOND / t1 * (motor_rot * STEP_ROT + microsteps);
      float Q = freq * PI * user_radius * user_radius * THREAD_PITCH / GEAR_RATIO / STEP_ROT;
      if (Q > 0) Serial.println(Q, 5);
    }
  }
}

void motor_setup() {
  switch (din_string[0]) {
    case forward_cmd:   //start driving motor forward
      digitalWrite(dirPin, FORWARD);
      Serial.println("FORWARD");
      break;
    case backward_cmd:   //start driving motor backward
      digitalWrite(dirPin, REVERSE);
      Serial.println("REVERSE");
      break;
  }
  uint8_t delim = din_string.indexOf(raduis_cmd);
  String user_r_string = din_string.substring(delim + 1);
  String user_Q_string = din_string.substring(1, delim);
  user_radius = user_r_string.toFloat();
  user_Q = user_Q_string.toFloat();
  din_string = "";  //reset
  double frequency = user_Q / (PI * user_radius * user_radius * THREAD_PITCH) * GEAR_RATIO * STEP_ROT;
  old_period = period;
  period = 1.0 / frequency * MICROSECOND;
  Serial.println((String) "frequency is: " + frequency);    //USED FOR TESTING
  motor_rot = 0; microsteps = 0;    // reset steps for new Q calculation
  if (start_flag) adj_Q_flg = true;
  else {
    Timer1.initialize(period);
    Timer1.pwm(stepPin, DutyCycle);
    Timer1.attachInterrupt(steps);  // call ISR every period to count the motor steps
  }
  StartTime = millis();  //measeure start time
  start_flag = true;
  run_char = running_cmd;
  rx_flg = false;
}

//ISR (goes in every turn)
void steps()
{
  microsteps++;
  if (microsteps == STEP_ROT) {
    microsteps = 0;
    motor_rot++;  //num rotations at the motor
  }
  if (motor_rot ==  NUM_ROTATIONS * GEAR_RATIO) {
    motor_rot = 0;
    Timer1.disablePwm(stepPin);
    Timer1.detachInterrupt();
    Serial.println("finished...");    //USED FOR TESTING
    run_char = stop_cmd;  //finished driving motor
    start_flag = false;
    //    long volatile timer = millis() - StartTime;
    //    float volatile rps = 1.0 * MILLISECOND / timer * NUM_ROTATIONS; //velocity used to compare with volumetric flow error below
    //    Serial.println((String) "rps: " + rps);
    //    Serial.print("\nrps: ");
    //    Serial.print(rps, 11);
    //    Serial.print("\n");
    //    float volatile error = (rps - rps_max) / rps * 100;
    //    Serial.println((String) "error: " + error + '%');
    //    Serial.println((String) timer + " ms");
  }
}


// Handler when receiving from I2C
void receiveI2C(int numBytes)
{
  din_string = "";
  //  Serial.println("Receiving...");   //USED FOR TESTING
  while (Wire.available())
  {
    char ch = Wire.read();
    if (ch == stop_cmd)
    {
      Timer1.disablePwm(stepPin);
      Timer1.detachInterrupt();
      Serial.println("stopping early...");    //USED FOR TESTING
      run_char = stop_cmd;
      start_flag = false;
    }
    else {
      din_string += ch;     // append string received from I2C master
      rx_flg = true;
    }
  }
  Serial.println("Received " + din_string);   //USED FOR TESTING
}


// Handler to send data to primary arduino
void requestI2CData()
{
  Wire.write(run_char);
}

void init_Microsteps(uint16_t stepResolution) {
  //Table 1 Microstep configuration
  uint16_t pin_config;
  switch (stepResolution) {
    case 1: pin_config = 0; break;    // Full-step
    case 2: pin_config = 5; break;    // 1/2th step
    case 4: pin_config = 10; break;   // 1/4th step
    case 8: pin_config = 7; break;    // 1/8th step
    case 16: pin_config = 15; break;  // 1/16th step
    case 32: pin_config = 2; break;   // 1/32nd step
    case 64: pin_config = 11; break;  // 1/64th step
    case 128: pin_config = 1; break;  // 1/128th step
    case 256: pin_config = 3; break;  // 1/256th step
    default: Serial.println("Invalid stepResolution"); pin_config = 0;
  }
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(MODE_1, OUTPUT);
  pinMode(MODE_2, OUTPUT);
  pinMode(STBY, OUTPUT);
  //The recommended power-up sequence is following:
  //1. Power-up the device applying the VS supply voltage but keeping both STBY and EN/FAULT inputs low.
  digitalWrite(STBY, LOW);
  //2. Set the MODEx inputs according to the target step resolution (see Table 1).
  digitalWrite(MODE_1, pin_config & 1);
  digitalWrite(MODE_2, (pin_config >> 1) & 1);
  digitalWrite(stepPin, (pin_config >> 2) & 1);
  digitalWrite(dirPin, (pin_config >> 3) & 1);
  //3. Wait for at least 1 µs (minimum tMODEsu time).
  delayMicroseconds(1);
  //4. Set the STBY high. The MODEx configuration is now latched inside the device.
  digitalWrite(STBY, HIGH);
  //5. Wait for at least 100 µs (minimum tMODEho time).
  delayMicroseconds(100);
  //6. Enable the power stage releasing the EN/FAULT input and start the operation.
}




// testing code
//#include <CALIPER.h>
//**TESTING VARAIABLES REMOVE LATER
//float user_Q = 10;
//float user_radius = RADIUS;



//**const float Q_max = 93.586;    // maximum volumetric flow rate in microLitre per second
//const float Q_min = 0.016666666666;   // minimum volumetric flow rate in microLitre per second (1uL/min)

//------------------------------------------------------------------------------------------------------
//** change into function to make Q variable
// calculations
//**TESTING VARIABLES
//const float rps_min = user_Q / (PI * RADIUS * RADIUS * THREAD_PITCH);
//const float rps_min = Q_min / (PI * RADIUS * RADIUS * THREAD_PITCH);
//const float rps_max = velocity / THREAD_PITCH / 60; //Q_max / (PI * RADIUS * RADIUS * THREAD_PITCH);
//const double frequency = rps_min * GEAR_RATIO * STEP_ROT;
//uint32_t period = 1 / frequency * MICROSECOND;

/*
  double calcFrequency(float Q_val, float radius_val)
  {
  float RPS_val = Q_val / (PI * radius_val * radius_val * THREAD_PITCH);
  double freq_val = Q_val / (PI * radius_val * radius_val * THREAD_PITCH) * GEAR_RATIO * STEP_ROT;
  Serial.println(RPS_val, 8);
  return freq_val;
  }
*/
