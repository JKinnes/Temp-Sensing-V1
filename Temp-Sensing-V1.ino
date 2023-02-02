//Define floats for each temperature sensor
float temp[5];

//Set pins for each temperature sensor
int tempPin[5] = {1, 2, 3, 4, 5};

//Set pins for alarming conditions
int relay1; 
int relay2;
int alarm;

//Define input and output word variable
char inWord[32];
char outWord[9];


void setup() {
  //Set up serial communication with Raspberry Pi
  Serial.begin(9600);
}

void loop() {


  /*Check for serial data from Pi
    Input word to the Arduino is defined as follows:
    Character 1: State of power relays (1 or 0)
    Character 2: State of alarm (1 or 0)*/

  int availableBytes = Serial.available();

  for(int i=0; i<availableBytes; i++) {
    inWord[i] = Serial.read();
  }
  

  //Set relay activation voltages based on input word
  if (inWord[0] == 1) {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    Serial.print("Got");
  } else if (inWord[0] == 0) {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
  }
  
  //Set alarm activation voltage based on input word
  if (inWord[1] == 1) {
    digitalWrite(alarm, HIGH);
  } else if (inWord[1] == 0) {
    digitalWrite(alarm, LOW);
  }

  //Read temp sensor voltages and set temp array floats
  //Round temp values to the nearest degree
  for (int i = 0; i < 5; i++) {
    temp[i] = (round((analogRead(tempPin[i]) / 1024) * 1000)/10);
  }

  //Begin writing data to output word
  //Set first element in outWord array to word start character
  outWord[0] = 1;

  if (digitalRead(relay1) == HIGH){
  outWord[1] = 1;
  } else if (digitalRead(relay1) == LOW){
    outWord[1] = 0;
  }

  if (digitalRead(alarm) == HIGH){
  outWord[2] = 1;
  } else if (digitalRead(alarm) == LOW){
    outWord[2] = 0;
  }

  for (int i = 0; i < 5; i++) {
    outWord[i+3] = temp[i];
  } 

  /*
    Send serial data from Arduino to Pi in several serial messages from outWord array
    Output word to the Arduino is defined as follows:
    Character 1: Word start character
    Character 2: State of power relays (1 or 0)
    Character 3: State of alarm (1 or 0)
    Character 4: temp1 degrees
    Character 5: temp2 degrees
    Character 6: temp3 degrees
    Character 7: temp4 degrees
    Character 8: temp5 degrees
    Character 9: Word end character (Separate serial statement)
    Output word is printed and loop is repeated every 250ms
  * /
  for (int i = 0; i < 8; i++){
  Serial.print(outWord[i]);
  }

  //Serial.println("End");
  //Serial.println(outWord[0]); */

  outWord[1] = 1;
  Serial.println(outWord[1]);

  delay(250);
}
