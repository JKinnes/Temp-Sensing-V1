//Define floats for each temperature sensor
double temp[5];

//Set pins for each temperature sensor
double tempPin[5] = {0, 2, 4, 6, 8};

//Set pins for alarming conditions
int relay1 = 39; 
int relay2 = 41;
int alarm = 12;

//Define input and output word variable
double outWord[9];
String inWord;

//Define strings for checking input word
String zero = "0";
String one = "1";

//Define warning variables

int alarmWarn = 0;
int alarmTrigger = 0;

void setup() {
  //Set up serial communication with Raspberry Pi
  Serial.begin(9600);
  pinMode(41, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {

  /*Check for serial data from Pi
    Input word to the Arduino is defined as follows:
    Character 1: State of power relays (1 or 0)
    Character 2: State of alarm (1 or 0)*/
  if (Serial.available() > 0){
    inWord = Serial.readStringUntil('\n');
    //Serial.print("You sent me: ");
    //Serial.println(inWord);

  //Set relay activation voltages based on input word
    if (inWord.startsWith(zero)) {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      outWord[1] = 0;
    } else if (inWord.startsWith(one)) {
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      outWord[1] = 1;
    }

  //Set alarm activation voltage based on input word
    if (inWord.endsWith(one)) {
      tone(alarm, 1000);
      outWord[2] = 1;
    } else if (inWord.endsWith(zero)) {
      noTone(alarm);
      outWord[2] = 0;
      alarmTrigger = 0;
    } 
  }

  //Read temp sensor voltages and set temp array floats
  //Round temp values to the nearest degree
  for (int i = 0; i < 5; i++) {
    temp[i] = round(analogRead(tempPin[i]))*500/1024;
  }

  //Reset warning variables;
  alarmWarn = 0;
  alarmTrigger = 0;

  //Check if any temp sensors are 150 or over. Set alarm warning if true
  for (int i = 0; i < 5; i++) {
    if (temp[i] >= 150){
      //Set alarmWarn to sensor over 150 to track for second check
      alarmWarn = i + 1;
    }
  }

  //If second sensor is over 150, trigger alarm
  if(alarmWarn != 0){
    for (int i = 0; i < 5; i++) {
     if (temp[i] >= 150 && i != (alarmWarn - 1)){
       alarmTrigger = 1;
        //Remove relay activation voltage
        digitalWrite(relay1, HIGH);
        digitalWrite(relay2, HIGH);
        //Apply buzzer voltage        
        tone(alarm, 1000);
     }
    }
  }

  //Begin writing data to output word
  //Set first element in outWord array to word start character
  outWord[0] = 1234;

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

  if(alarmTrigger == 1){    
    delay(1000);
  }else {
    delay(250);
  }
}
