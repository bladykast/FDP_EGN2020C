

const int buttonPin = 3;     // Define pushbutton pin
const int ledPin =  5;      // ...and LED pin
const int solarPin = A0;    // Define voltage reading pin for solar panel
const int batteryPin = A1;  // ...and battery 

int buttonState = 0;         // Keep track of button state 
int LEDState = 0;            // and the LED's 
double solarVoltage = 0;      //..and solar panel voltage
double batteryVoltage = 0;    //..and battery voltage

double solarThreshold= 2.82;  //Voltage cutoff for sunlight
double batteryThreshold= 3.2; //Voltage minimum for battery 
 
void setup() {
  pinMode(LEDPin, OUTPUT);    //Set up the GPIO pins
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(LEDPin, LOW);   //Turn off light initially
}

void loop() {

  solarVoltage = getVoltage(solarPin);    //Check voltages and state of button
  batteryVoltage = getVoltage(batteryPin);
  buttonState = buttonToggleRead(buttonPin);
  
  if (batteryVoltage < batteryThreshold || solarVoltage > solarThreshold){ // if there's no battery OR it's sunny outside...
    LEDState = 0;  //Don't allow the light to turn on
  }
  else {LEDState = 1;}  //Light can be toggled

  digitalWrite(LEDPin, LEDState * buttonState} //Write the value of the button to the LED 

}

double getVoltage(int pin) {  //checks the voltage of an analog pin
  int i;
  double voltage = 0;

  for (i = 0; i < 3; i++){            // for 3 times,
    voltage = voltage + analogRead(pin);    // read sensor on analog pin
  }
  
  voltage = voltage / 3;    // average these values to give smooth result
  voltage = (voltage * 5) / 1024;  // Give a voltage value rather than a 0-1023 value
  return voltage;
}

int buttonToggleRead(int pin){  // turns pushbutton into toggle switch
 int status = false;
 if (digitalRead(pin) == true) {
    status = !status;
    return status;
  } 
  while(digitalRead(pin) == true);
      delay(50); // keeps a small delay 
}
