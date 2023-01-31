//Define floats for each temperature sensor
float temp1; 
float temp2; 
float temp3; 
float temp4; 
float temp5; 

//Set pins for each temperature sensor
int temp1pin;
int temp2pin;
int temp3pin;
int temp4pin;
int temp5pin;

//Define Arrays for temps and temp pins
float temps[];
int tempPins[];

//Set pins for alarming conditions
int relay1; 
int relay2;
int alarm;

//Define input and output word variable
char outWord; 
char inWord;


void setup() {
  //Set up serial communication with Raspberry Pi
  Serial.begin(9600);
}

float setTemp(temp, pin) {
  //read voltage on pin, correct for scaling, and set temp equal
  temp = ((analog.read(pin) / 1024) * 100);
  return temp;
}

void loop() {

  /*
    Check for serial data from Pi
    Input word to the Arduino is defined as follows:
    Character 1: State of power relays (1 or 0)
    Character 2: State of alarm (1 or 0)
  */
  if(Serial.available() > 0) {
    inWord[] = Serial.readStringUntil('\n');
  }

  //Set alarming criteria based on input word

  //

  //Read temp sensor voltages and set temp variabes
  for (int i = 0, i < 5, i++) {
    setTemp(temps[i], tempPins[i]);
  }

  /*
    Send serial data from Arduino to Pi
    Output word to the Arduino is defined as follows:
    Character 1: State of power relays (1 or 0)
    Character 2: State of alarm (1 or 0)
    Characters 3 and 4: temp1 degrees (Hexadecimal)
    Character 5: Decimal for temp1
    Characters 6 and 7: temp2 degrees (Hexadecimal)
    Character 8: Decimal for temp2
    Characters 9 and 10: temp3 degrees (Hexadecimal)
    Character 11: Decimal for temp3
    Characters 12 and 13: temp4 degrees (Hexadecimal)
    Character 14: Decimal for temp4
    Characters 15 and 16: temp5 degrees (Hexadecimal)
    Character 17: Decimal for temp5
    Output word is printed and loop is repeated every 250ms
  */
  Serial.println(outWord[i]);
  delay(250);
}
