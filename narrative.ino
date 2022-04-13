#include <Servo.h>

#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247
#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494
#define C5  523
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988
#define C6  1047
#define CS6 1109
#define D6  1175
#define DS6 1245
#define REST 0

const int buzzer = 15;
int tempo;
int notes;
int wholenote;
int divider = 0, noteDuration = 0;

int musicSpring[] = { 
  E5, 4,
  GS5, 4, GS5, 4, GS5, 4, FS5, 8, E5, 8, B5, -2, B5, 8, A5, 8,
  GS5, 4, GS5, 4, GS5, 4, FS5, 8, E5, 8, B5, -2, B5, 8, A5, 8,
  GS5, 4, A5, 8, B5, 8, A5, 4, GS5, 4, FS5, -2
};

int musicSpringEnd[] = {
  E5, 4,
  B5, 4, A5, 8, GS5, 8, A5, 4,B5, 4, CS6, 4, B5, 2, E5, 4,
  B5, 4, A5, 8, GS5, 8, A5, 4,B5, 4, CS6, 4, B5, 2, E5, 4,
  CS6, 4, B5, 2, A5, 4, GS5, 4, FS5, 8, E5, 8, FS5, 16, GS5, 16, FS5, 4,
  E5, 1  
};

int musicSummer[] = {
  G4, 5, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, 
  F4, 5, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4,
  DS4, 5, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4,
  D4, 5, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, -2,
  REST, 1, REST, 1, REST, 1, REST, 1,
  D5, 5, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, 
  C5, 5, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4,
  AS4, 5, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4,
  A4, 5, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, 4, G3, -2,
};

int musicSummerEnd[] = {
  G4, 4, G4, 4, G4, 4, G4, 4, G4, 4, G4, 4, G4, 4, G4, 4, G4, 4, G4, 4, G4, 4, G4, 4,
  FS4, 4, FS4, 4, FS4, 4, FS4, 4, FS4, 4, FS4, 4, FS4, 4, FS4, 4, FS4, 4, FS4, 4, FS4, 4, FS4, 4, 
  G4, 4, G4, 4, G4, 4, G4, 4, AS4, 4, AS4, 4, AS4, 4, AS4, 4, D5, 4, D5, 4, D5, 4, D5, 4,
  G5, 4, G5, 4, G5, 4, G5, 4, AS5, 4, AS5, 4, AS5, 4, AS5, 4, G5, 4, G5, 4, G5, 4, G5, 4,
  D5, 4, D5, 4, D5, 4, D5, 4, AS4, 4, AS4, 4, AS4, 4, AS4, 4, G4, 4, G4, 4, G4, 4, G4, 4,
  REST, 8,
  G3, 0
};

int musicAutumn[] = {
  A5, 4, A5, 4, A5, 4, AS5, 4, A5, 2, A5, 4, AS5, 4, 
  A5, 4, A5, 4, A5, 4, AS5, 4, A5, 2, A5, 4, AS5, 4,
  A5, 4, G5, 8, A5, 8, AS5, 4, G5, 4, A5, 2, REST, 2,
  A4, 4, A4, 4, A4, 4, AS4, 4, A4, 2, A4, 4, AS4, 4, 
  A4, 4, A4, 4, A4, 4, AS4, 4, A4, 2, A4, 4, AS4, 4,
  A4, 4, G4, 8, A4, 8, AS4, 4, G4, 4, F4, 2, REST, 2,
};

int musicAutumnEnd[] = {
  F4, -4, C5, -8, F4, 2, F4, 2, 
  F4, -4, C5, -8, F4, 2, F4, 2, 
  F4, -4, C5, -8, AS4, 2, A4, 2, 
  G4, 4, G3, 4, G4, 4, G3, 4, G4, 4, G3, 4,
  F4, -4, C5, -8, F4, 2, F4, 2,
  F4, -4, C5, -8, F4, 2, F4, 2,
  F4, -4, A4, -8, AS4, 2, G4, 2,
  F4, 1 
};

int musicWinter[] = {
  B4, 4, G5, 4, FS5, 4, E5, 4, DS5, 4, E5, 4, 
  B4, 4, G5, 4, FS5, 4, E5, 4, DS5, 4, E5, 4, 
  B4, 4, G5, 4, FS5, 4, E5, 4, DS5, 4, E5, 4,
  B4, 4, C5, 4, B4, 4, A4, 4, B4, 4, C5, 4,
  E4, 4, C5, 4, B4, 4, A4, 4, B4, 4, C5, 4, 
  E4, 4, C5, 4, B4, 4, A4, 4, B4, 4, C5, 4, 
  E4, 1
};

int musicWinterEnd[] = {
  B4, 4, B3, 4, B4, 4, B3, 4, B4, 4, B3, 4, B4, 4, B3, 4, B4, 4, B3, 4, B4, 4, B3, 4, 
  A4, 4, A3, 4, A4, 4, A3, 4, A4, 4, A3, 4, A4, 4, A3, 4, A4, 4, A3, 4, A4, 4, A3, 4, 
  G4, 4, E4, 4, G3, 4, E4, 4, G4, 4, E4, 4, G3, 4, E4, 4, G4, 4, E4, 4, G3, 4, E4, 4, 
  FS4, 4, E4, 4, FS3, 4, E4, 4, FS4, 4, E4, 4, FS3, 4, E4, 4, FS4, 4, E4, 4, FS3, 4, E4, 4,
  FS4, 4, DS4, 4, FS3, 4, DS4, 4, FS4, 4, DS4, 4, FS3, 4, DS4, 4, FS4, 4, DS4, 4, FS3, 4, DS4, 4,
  REST, 6, C4, 16, G5, 16, E4, 0  
};

void playMusic(int *score, int n, int t) {
  notes = n;
  tempo = t;
  wholenote = (60000 * 4) / tempo;
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = score[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    } else {
      noteDuration = (wholenote) * 4.5;
    }
    tone(buzzer, score[thisNote], noteDuration);
    delay(noteDuration);
    noTone(buzzer);
  }    
}

Servo servo;
int servoPIN = 45;

const int lightGroup1 = 11;
const int lightGroup2 = 12;
const int lightGroup3 = 13;

const int lightGroup1Controller = 7;
const int lightGroup2Controller = 8;
const int lightGroup3Controller = 9;

bool lightGroup1On = false;
bool lightGroup2On = false;
bool lightGroup3On = false;

const int sunGroup1 = 34;
const int sunGroup2 = 35;

const int skyBlue = 26;
const int skyWhite = 29;

const int masterController = 5;
const int servoController = 4;
int servoSpeed = 90;
int brightness;

const int lightSensor = A0;

bool successful = true;
int state = 0;
const int SPRING = 1;
const int SUMMER = 2;
const int AUTUMN = 3;
const int WINTER = 4;

unsigned long currentMillis;

const int blinkInterval = 200;
long lastBlinkTime = 0;
int currentLightGroup = 0;

const int blinkIntervalSlow = 800;

const int pressInterval = 500;
long lastPressTime = 0;

const int speedChangeInterval = 1200;
long lastSpeedChangeTime = 0;

const int skyBlinkInterval = 1200;
long lastSkyBlinkTime = 0;
bool blueSkyOn = true;

const int sunBlinkInterval = 1000;
long lastSunBlinkInterval = 0;

void toSpring() {
  digitalWrite(skyBlue, HIGH);
  digitalWrite(skyWhite, HIGH);
  digitalWrite(sunGroup1, HIGH);
  digitalWrite(sunGroup2, LOW);
  int brightness = analogRead(lightSensor);
  if (digitalRead(lightGroup1Controller) == HIGH) {
    digitalWrite(lightGroup1, LOW);
  } else {
    digitalWrite(lightGroup1, HIGH);
  }
  if (digitalRead(lightGroup2Controller) == HIGH) {
    digitalWrite(lightGroup2, LOW);
  } else {
    digitalWrite(lightGroup2, HIGH);
  }
  if (digitalRead(lightGroup3Controller) == HIGH) {
    digitalWrite(lightGroup3, LOW);
  } else {
    digitalWrite(lightGroup3, HIGH);
  }
  currentMillis = millis();
  if (digitalRead(servoController) == LOW && currentMillis - lastPressTime > pressInterval) {
    lastPressTime = currentMillis;
    if (servoSpeed < 120) {
      servoSpeed = 120;
      servo.write(servoSpeed);
    } else if (servoSpeed > 100) {
      servoSpeed = 100;
      servo.write(servoSpeed);
    }
  }

  if (brightness < 400 &&
      servoSpeed > 119 
      && digitalRead(lightGroup1Controller) == LOW 
      && digitalRead(lightGroup2Controller) == LOW 
      && digitalRead(lightGroup3Controller) == LOW) {
    digitalWrite(lightGroup1, HIGH);
    digitalWrite(lightGroup2, HIGH);
    digitalWrite(lightGroup3, HIGH);
    successful = true;
    playMusic(musicSpringEnd, sizeof(musicSpringEnd)/sizeof(musicSpringEnd[0])/2, 230);
  }
}

void toSpringSuccess() {
  currentMillis = millis();
  if (currentMillis - lastBlinkTime > blinkInterval) {
    currentLightGroup = (currentLightGroup + 1) % 3;
    if (currentLightGroup == 1) {
      digitalWrite(lightGroup1, HIGH);
      digitalWrite(lightGroup2, LOW);
      digitalWrite(lightGroup3, LOW);
      lastBlinkTime = currentMillis;
    } else if (currentLightGroup == 2) {
      digitalWrite(lightGroup1, LOW);
      digitalWrite(lightGroup2, HIGH);
      digitalWrite(lightGroup3, LOW);
      lastBlinkTime = currentMillis;
    } else if (currentLightGroup == 0) {
      digitalWrite(lightGroup1, LOW);
      digitalWrite(lightGroup2, LOW);
      digitalWrite(lightGroup3, HIGH);
      lastBlinkTime = currentMillis;
    }    
  }
}

void toSummer() {
  digitalWrite(skyBlue, HIGH);
  digitalWrite(skyWhite, HIGH);
  digitalWrite(sunGroup1, HIGH);
  digitalWrite(sunGroup2, HIGH);
  currentMillis = millis();
  if (currentMillis - lastSpeedChangeTime > speedChangeInterval) {
    lastSpeedChangeTime = currentMillis;
    if (servoSpeed < 101) {
      servoSpeed = 175;
      servo.write(servoSpeed);
    } else if (servoSpeed > 101) {
      servoSpeed = 100;
      servo.write(servoSpeed);
    }
  }
  brightness = analogRead(lightSensor);
  if (brightness > 800) {
    successful = true;
    playMusic(musicSummerEnd, sizeof(musicSummerEnd)/sizeof(musicSummerEnd[0])/2, 600);
  }
}

void toSummerSuccess() {
  digitalWrite(lightGroup1, HIGH);
  digitalWrite(lightGroup2, HIGH);
  digitalWrite(lightGroup3, HIGH);
  servoSpeed = 170;
  servo.write(servoSpeed);
  currentMillis = millis();
  if (currentMillis - lastSkyBlinkTime > skyBlinkInterval) {
    lastSkyBlinkTime = currentMillis;
    if (blueSkyOn) {
      digitalWrite(skyBlue, LOW);
      digitalWrite(skyWhite, HIGH);
      blueSkyOn = false;
    } else {
      digitalWrite(skyBlue, HIGH);
      digitalWrite(skyWhite, LOW);
      blueSkyOn = true;
    }
  }
}

void toAutumn() {
  digitalWrite(skyBlue, LOW);
  digitalWrite(skyWhite, HIGH);
  digitalWrite(sunGroup1, LOW);
  digitalWrite(sunGroup2, HIGH);
  currentMillis = millis();
  if (digitalRead(servoController) == LOW && currentMillis - lastPressTime > pressInterval) {
    lastPressTime = currentMillis;
    if (servoSpeed < 120) {
      servoSpeed = 120;
      servo.write(servoSpeed);
    } else if (servoSpeed > 100) {
      servoSpeed = 100;
      servo.write(servoSpeed);
    }
  }
  if (digitalRead(lightGroup1Controller) == LOW) {
    lightGroup1On = false;
    digitalWrite(lightGroup1, LOW);
  }
  if (digitalRead(lightGroup2Controller) == LOW) {
    lightGroup2On = false;
    digitalWrite(lightGroup2, LOW);
  }
  if (digitalRead(lightGroup3Controller) == LOW) {
    lightGroup3On = false;
    digitalWrite(lightGroup3, LOW);
  }
  int brightness = analogRead(lightSensor);
  if (brightness < 400 && servoSpeed < 101 && !lightGroup1On && !lightGroup2On && !lightGroup3On) {
    successful = true;
    playMusic(musicAutumnEnd, sizeof(musicAutumnEnd)/sizeof(musicAutumnEnd[0])/2, 260);
  }
}

void toAutumnSuccess() {
  currentMillis = millis();
  if (currentMillis - lastBlinkTime > blinkIntervalSlow) {
    currentLightGroup = (currentLightGroup + 1) % 3;
    if (currentLightGroup == 1) {
      digitalWrite(lightGroup1, HIGH);
      digitalWrite(lightGroup2, LOW);
      digitalWrite(lightGroup3, LOW);
      lastBlinkTime = currentMillis;
    } else if (currentLightGroup == 2) {
      digitalWrite(lightGroup1, LOW);
      digitalWrite(lightGroup2, HIGH);
      digitalWrite(lightGroup3, LOW);
      lastBlinkTime = currentMillis;
    } else if (currentLightGroup == 0) {
      digitalWrite(lightGroup1, LOW);
      digitalWrite(lightGroup2, LOW);
      digitalWrite(lightGroup3, HIGH);
      lastBlinkTime = currentMillis;
    }    
  }
}

void toWinter() {
  servoSpeed = 90;
  servo.write(servoSpeed);
  digitalWrite(skyBlue, HIGH);
  digitalWrite(skyWhite, LOW);
  digitalWrite(sunGroup1, LOW);
  digitalWrite(sunGroup2, LOW);
  int brightness = analogRead(lightSensor);
  if (digitalRead(lightGroup1Controller) == HIGH) {
    digitalWrite(lightGroup1, LOW);
  } else {
    digitalWrite(lightGroup1, HIGH);
  }
  if (digitalRead(lightGroup2Controller) == HIGH) {
    digitalWrite(lightGroup2, LOW);
  } else {
    digitalWrite(lightGroup2, HIGH);
  }
  if (digitalRead(lightGroup3Controller) == HIGH) {
    digitalWrite(lightGroup3, LOW);
  } else {
    digitalWrite(lightGroup3, HIGH);
  }
  if (brightness > 840 
      && digitalRead(lightGroup1Controller) == LOW 
      && digitalRead(lightGroup2Controller) == LOW 
      && digitalRead(lightGroup3Controller) == LOW){
    successful = true;
    playMusic(musicWinterEnd, sizeof(musicWinterEnd)/sizeof(musicWinterEnd[0])/2, 600);
  }
  
}

void toWinterSuccess() {
  currentMillis = millis();
  if (currentMillis - lastBlinkTime > blinkInterval) {
    currentLightGroup = (currentLightGroup + 1) % 3;
    if (currentLightGroup == 1) {
      digitalWrite(lightGroup1, HIGH);
      digitalWrite(lightGroup2, LOW);
      digitalWrite(lightGroup3, LOW);
      lastBlinkTime = currentMillis;
    } else if (currentLightGroup == 2) {
      digitalWrite(lightGroup1, LOW);
      digitalWrite(lightGroup2, HIGH);
      digitalWrite(lightGroup3, LOW);
      lastBlinkTime = currentMillis;
    } else if (currentLightGroup == 0) {
      digitalWrite(lightGroup1, LOW);
      digitalWrite(lightGroup2, LOW);
      digitalWrite(lightGroup3, HIGH);
      lastBlinkTime = currentMillis;
    }    
  }
  if (currentMillis - lastSkyBlinkTime > skyBlinkInterval) {
    lastSkyBlinkTime = currentMillis;
    if (blueSkyOn) {
      digitalWrite(skyBlue, LOW);
      digitalWrite(skyWhite, HIGH);
      blueSkyOn = false;
    } else {
      digitalWrite(skyBlue, HIGH);
      digitalWrite(skyWhite, LOW);
      blueSkyOn = true;
    }
  }
}

void setup() {
  Serial.begin(9600);
  servo.attach(servoPIN);
  servo.write(100);
  pinMode(sunGroup1, OUTPUT);
  pinMode(sunGroup2, OUTPUT);
  pinMode(skyBlue, OUTPUT);
  pinMode(skyWhite, OUTPUT);
  pinMode(lightGroup1, OUTPUT);
  pinMode(lightGroup2, OUTPUT);
  pinMode(lightGroup3, OUTPUT);
  pinMode(lightGroup1Controller, INPUT_PULLUP);
  pinMode(lightGroup2Controller, INPUT_PULLUP);
  pinMode(lightGroup3Controller, INPUT_PULLUP);
  pinMode(masterController, INPUT_PULLUP);

}

void loop() {
  
  if (digitalRead(masterController) == LOW && successful) {
    state++;
    if (state == SPRING) {
      digitalWrite(skyBlue, HIGH);
      digitalWrite(skyWhite, HIGH);
      digitalWrite(sunGroup1, HIGH);
      digitalWrite(sunGroup2, LOW);
      playMusic(musicSpring, sizeof(musicSpring)/sizeof(musicSpring[0])/2, 230);
    } else if (state == SUMMER) {
      digitalWrite(lightGroup1, HIGH);
      digitalWrite(lightGroup2, HIGH);
      digitalWrite(lightGroup3, HIGH);
      playMusic(musicSummer, sizeof(musicSummer)/sizeof(musicSummer[0])/2, 600);
    } else if (state == AUTUMN) {
      lightGroup1On = true;
      lightGroup2On = true;
      lightGroup3On = true;
      playMusic(musicAutumn, sizeof(musicAutumn)/sizeof(musicAutumn[0])/2, 260);
    } else if (state == WINTER) {
      digitalWrite(lightGroup1, LOW);
      digitalWrite(lightGroup2, LOW);
      digitalWrite(lightGroup3, LOW);
      playMusic(musicWinter, sizeof(musicWinter)/sizeof(musicWinter[0])/2, 300);
    }
    successful = false;   
  }
  if (state == SPRING && !successful) {
    toSpring();
  } else if (state == SPRING && successful) {
    toSpringSuccess();
  } else if (state == SUMMER && !successful) {
    toSummer();
  } else if (state == SUMMER && successful) {
    toSummerSuccess();
  } else if (state == AUTUMN && !successful) {
    toAutumn();
  } else if (state == AUTUMN && successful) {
    toAutumnSuccess();
  } else if (state == WINTER && !successful) {
    toWinter();
  } else if (state == WINTER && successful) {
    toWinterSuccess();
  }
}
