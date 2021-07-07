const int button = 4;
const int vibr = 5;
const int gled = 6;
const int rled = 7;
const int bt_state = 2;

const int xInput = A0;
const int sampleSize = 10;
int xRaw;

int state;
int score = 0;
unsigned long DELAY;
unsigned long deadline;
String temp;

void success(){ 
  state = 2; 
  score++;
  Serial.println("left pass green");
  temp = "middle "+String(score)+" green";  
  Serial.println(temp);
}

void blinkPin(int pin, int duration) {
  digitalWrite(pin, HIGH);
  delay(duration);
  digitalWrite(pin, LOW);
  delay(duration);
}

int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++){
    reading += analogRead(axisPin);
  }
  return reading/sampleSize;
}


void setup()
{
  pinMode(button, INPUT);
  pinMode(vibr, OUTPUT);
  pinMode(gled, OUTPUT);
  pinMode(rled, OUTPUT);
  Serial.begin(38400);
  Serial.flush();
  randomSeed(analogRead(A3));
  state = 1;
}

void loop()
{
  //main program//
  switch (state){
    case 1: // bootup and post failure state
      //press the button to begin or connect to bluetooth
      while (!digitalRead(button)) {
        blinkPin(gled, 200);
        blinkPin(rled, 200);
        delay(10);
      }
      //start game light sequence
      DELAY = 10000;
      Serial.println("left Three red");
      blinkPin(gled,750);
      Serial.println("left Two red");
      blinkPin(gled, 750);
      Serial.println("left One red");
      blinkPin(gled, 750);
      Serial.println("left Go! green");
      state = 2;
      break;
    case 2: // post success and post start state
      blinkPin(gled,300);  //indicates success
      state = random(3,6);
      DELAY = DELAY * 0.9;
      temp = "right "+String(double(DELAY)/double(1000))+" red";
      Serial.println(temp);
      Serial.println("left ... gray");
      break;
    case 3: // honk it state
      //sensory output
      blinkPin(vibr, 1000);
      
      state = 6;
      deadline = millis() + DELAY;
      while (millis() < deadline) { //checks if the user selcts the correct input
        if (digitalRead(button)){ // turn left
          success();
          break;
      }
      delay(10);
     }
     break;
    case 4: // turn left state
      //sensory output
      blinkPin(vibr, 250);
      
      state = 6;
      deadline = millis() + DELAY;
      while (millis() < deadline) { //checks if the user selcts the correct input
        xRaw = ReadAxis(xInput);
        if (xRaw < 330){ // turn left
          success();
          break;
      }
      if(millis() > deadline){
          break;
      }
      delay(10);
     }
     break;
    case 5: //turn right state;
      //sensory output
      blinkPin( vibr, 250);
      blinkPin( vibr, 250);
      
      state = 6;
      deadline = millis() + DELAY;
      while (millis() < deadline) { //checks if the user selcts the correct input
        xRaw = ReadAxis(xInput);
        if (xRaw > 400){ // turn left
          success();
          break;
      }
      if(millis() > deadline){
          break;
      }
      delay(10);
     }
     break;
    case 6: //failure state
      Serial.println("left Failed red");
      Serial.println("middle "+String(score)+" red");
      blinkPin(rled, 5000);
      Serial.println("right new green");
      state = 1;
      break;
  }

}
