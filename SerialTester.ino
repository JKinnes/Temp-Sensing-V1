int randStart = 900;
double randTemp[5];
double randRelay;
double randAlarm;
double outword[9];


void setup() {
  Serial.begin(9600);
}

void loop() {
  
  if (615 < randStart < 1485) {
  randStart = random(randStart - 15, ransStart + 15);
  } else if (615 > randStart) {
    randStart = random(randStart, randStart +15);
  } else if (randStart > 1485){
    ranStart = random(randStart -15, randStart); 
  }
    
  if ((randStart % 2) == 0){
    randRelay = 1;
    randAlarm = 0;
  } else {
    randRelay = 0;
    randAlarm = 1;
  }
  
  for (int i = 0; i < 5; i++){
    randTemp[i] = random(randStart - 25, randStart + 25);
  }
  
  outWord[0] = 1234;
  outword[1] = randRelay;
  outWord[2] = randAlarm;
  
  for (int i = 0; i < 5; i++){
    outWord[i+3] = (randtemp[i]/10);
  }
  
  outWord[8] = 4321;
  
  for (int i = 0; i < 9; i++){
    Serial.println(outWord[i]);
  }
  
  delay(250);
}
