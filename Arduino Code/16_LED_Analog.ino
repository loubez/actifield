int outPin = 13; // the pin number of the indicator LED
int outPinState = LOW; // the current state of the indicator LED
int count = 0; //this variable will store the number of beam breaks
int limit=50;                 //Threshold for detecting IR radiation 

// the following variables are long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long outTime = 0; // the last time the output pin was toggled

 //rows and cols will define the size of the array 
const int rows = 2;
const int cols = 8;

int SensorMatrix[rows][cols] = {
  // This matrix will hold the pin assignments for the Sensors
  {A0, A1, A2, A3, A4, A5, A6, A7}, 
  {A8, A9, A10, A11, A12, A13, A14, A15}
};

int SensorStateMatrix[rows][cols] = {
 // This matrix will store the current reading from each sensor
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

int lastSensorStateMatrix[rows][cols] = {
 // This matrix will store the previous reading from each sensor
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

 
void setup() {
Serial.begin(9600); //initialize serial monitor for writing
pinMode(outPin, OUTPUT); //set outPin as an output pin
} //close setup()

 
void loop() {
 
  //this nested for loop will scan each IR sensor in sequence
  for(int i = 0; i < rows; i++){
 
    for(int j = 0; j < cols; j++){
  SensorStateMatrix[i][j] = analogRead(SensorMatrix[i][j]); //read the current value of the corresponding sensor
  // if the beam was just broken (i.e. the sensor value went from > limit to <= limit) or restored (i.e. the sensor value went from <=limit to > limit),
  if ((SensorStateMatrix[i][j] <= limit && lastSensorStateMatrix[i][j] > limit) || (SensorStateMatrix[i][j] > limit && lastSensorStateMatrix[i][j] <= limit)){
    outTime = millis(); //remember the last time the beam was broken or restored
    count += 1;
    Serial.print("Pin broken= "); 
    Serial.println(SensorMatrix[i][j]); 
    Serial.print("Beam break time = "); 
    Serial.println(outTime); 
    Serial.print("Total beam breaks = "); 
    Serial.println(count); 
    digitalWrite(outPin, HIGH);
    delay(20);  
    digitalWrite(outPin, LOW);   
  }
  lastSensorStateMatrix[i][j] = SensorStateMatrix[i][j];
 
    }//close for j
 
  }//close for i
 
} //close loop()

