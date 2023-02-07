//Define floats for each temperature sensor
double temp[5];

//Set pins for each temperature sensor
int tempPin[5] = {0, 2, 4, 6, 8};

//Set pins for alarming conditions
double relay1 = 39; 
double relay2 = 41;
double alarm = 12;

//Define input and output word variable
double outWord[9];
String inWord;

//Define strings for checking input word
String zero = "0";
String one = "1";

void setup() {
  //Set up serial communication with Raspberry Pi
  Serial.begin(9600);
}

void loop() {

  /*Check for serial data from Pi
    Input word to the Arduino is defined as follows:
    Character 1: State of power relays (1 or 0)
    Character 2: State of alarm (1 or 0)*/
  if (Serial.available() > 0){
    inWord = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(inWord);

  //Set relay activation voltages based on input word
    if (inWord.startsWith(one)) {  //SERIAL OUTPUT ISSUE RESOLVED, SERIAL READ ISSUE REMAINS. BOARD SEES INPUT AND WRITES TO data STRING. READING data STRING IS CURRENT ISSUE
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
    } else if (inWord.startsWith(zero)) {
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
    }

  //Set alarm activation voltage based on input word
    if (inWord.endsWith(one)) {
      digitalWrite(alarm, HIGH);
    } else if (inWord.endsWith(zero)) {
      digitalWrite(alarm, LOW);
    } 
  }

  //Read temp sensor voltages and set temp array floats
  //Round temp values to the nearest degree
  for (int i = 0; i < 5; i++) {
    temp[i] = (round((analogRead(tempPin[i]) / 1024) * 1000)/10);
  }

  //Define and reset warning variables;
  int alarmWarn = 0;
  int alarmTrigger = 0;

  //Check if any temp sensors are 150 or over. Set alarm warning if true
  for (int i = 0; i < 5; i++) {
    if (temp[i] >= 150){
      //Set alarmWarn to sensor over 150 to track for second check
      alarmWarn = i;
    }
  }

  //If second sensor is over 150, trigger alarm
  if(alarmWarn != 0){
    for (int i = 0; i < 5; i++) {
     if (temp[i] >= 150 && i != alarmWarn){
       alarmTrigger = 1;
        //Remove relay activation voltage
        digitalWrite(relay1, LOW);
        digitalWrite(relay2, LOW);
        //Apply buzzer voltage        
        digitalWrite(alarm, HIGH);
     }
    }
  }

  //Begin writing data to output word
  //Set first element in outWord array to word start character
  outWord[0] = 1234;

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

  outWord[8] = 4321;

  /*Send serial data from Arduino to Pi in several serial messages from outWord array
    Output word to the Arduino is defined as follows:
    Character 1: Word start character (1234)
    Character 2: State of power relays (1 or 0)
    Character 3: State of alarm (1 or 0)
    Character 4: temp1 degrees
    Character 5: temp2 degrees
    Character 6: temp3 degrees
    Character 7: temp4 degrees
    Character 8: temp5 degrees
    Character 9: Word end character (4321)
    Output word is printed and loop is repeated every 250ms*/
  for (int i = 0; i < 9; i++){
  Serial.println(outWord[i]);
  }

  delay(250);
}