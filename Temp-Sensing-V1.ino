//Define floats for each temperature sensor
float temp[4];

//Set pins for each temperature sensor
int tempPin[4] = {1, 2, 3, 4, 5};

//Define character arrays for each temperature hex value
char tempHex[4][1];

//Set pins for alarming conditions
int relay1; 
int relay2;
int alarm;

//Define input and output word variable
char outWord[11]; 
char inWord[1];


void setup() {
  //Set up serial communication with Raspberry Pi
  Serial.begin(9600);
}

float setTemp(temp, pin) {
  //read voltage on pin, correct for scaling, and set temp equal
  temp = ((analog.read(pin) / 1024) * 100);
  return temp;
}

char setTempHex(tempHex, output){


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

  //Set relay activation voltages based on input word
  if (inWord[0] = 1) {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  } else if (inWord[0] = 0) {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
  }
  
  //Set alarm activation voltage based on input word
  if (inWord[1] = 1) {
    digitalWrite(alarm, HIGH);
  } else if (inWord[1] = 0) {
    digitalWrite(alarm, LOW);
  }

  //Read temp sensor voltages and set temp array floats
  for (int i = 0, i < 5, i++) {
    temp[i] = round(((analog.read(tempPin[i]) / 1024) * 1000)/10);
  }

  //

  //Read temp sensor values and convert to hex
  for (int i = 0, i < 5, i++) {
    char hexTemp[1] = String(temp[i], HEX); //????
  }

  /*
    Send serial data from Arduino to Pi
    Output word to the Arduino is defined as follows:
    Character 1: State of power relays (1 or 0)
    Character 2: State of alarm (1 or 0)
    Characters 3 and 4: temp1 degrees (Hexadecimal)
    Characters 5 and 6: temp2 degrees (Hexadecimal)
    Characters 7 and 8: temp3 degrees (Hexadecimal)
    Characters 9 and 10: temp4 degrees (Hexadecimal)
    Characters 11 and 12: temp5 degrees (Hexadecimal)
    Output word is printed and loop is repeated every 250ms
  */
  Serial.println(outWord[i]);
  delay(250);
}
