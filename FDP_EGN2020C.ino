const int buttonPin = 3;     // Define pushbutton pin
const int LEDPin =  5;      // ...and LED pin
const int solarPin = A0;    // Define voltage reading pin for solar panel
const int batteryPin = A1;  // ...and battery 

int buttonState = 0;         // Keep track of button state 
int LEDState = 0;            // and the LED's 
double solarVoltage = 0;      //..and solar panel voltage
double batteryVoltage = 0;    //..and battery voltage

const double solarThreshold= 2.82;  //Voltage cutoff for sunlight
const double batteryThreshold= 3.2; //Voltage minimum for battery 
 
void setup() {

  Serial.begin(9600);
  
  pinMode(LEDPin, OUTPUT);    //Set up the GPIO pins
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(LEDPin, LOW);   //Turn off light initially
}


double getVoltage(int pin) {  //checks the voltage of an analog pin
  int i;
  double voltage = 0;

  for (i = 0; i < 3; i++){            // for 3 times,
    voltage = voltage + analogRead(pin);    // read sensor on analog pin
  }
  
  voltage = voltage / 3;    // average these values to give smooth result
  voltage = (voltage * 5) / 1024;  // Give a voltage value rather than a 0-1023 value
  voltage = voltage * 2; // Correct for voltage divider
  return voltage;
}

void loop() {

  solarVoltage = getVoltage(solarPin);    //Check voltages and state of button
  batteryVoltage = getVoltage(batteryPin);
  buttonState = digitalRead(buttonPin);
  
  if (batteryVoltage < batteryThreshold || solarVoltage > solarThreshold){ // if there's no battery OR it's sunny outside...
    LEDState = 0;  //Don't allow the light to turn on
  }
  else {LEDState = 1;}  //Light can be toggled

  digitalWrite(LEDPin, LEDState * buttonState); //Write the value of the button to the LED 

  Serial.print("Battery = ");
  Serial.print(batteryVoltage);
  Serial.print("\t Panel = ");
  Serial.println(solarVoltage);
}
