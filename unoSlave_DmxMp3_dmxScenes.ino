#include <DmxSimple.h>

#define MIN_DELAY  10

/* ETERN TRIG PINS&STATES*/
int trigRecievePin = A0;
int trigRecieveState;

/* DMX */

int animation_cycle;
int scene_switcher;
unsigned long previousMillis = 0;


typedef struct status_reflektora {
  int red;
  int green;
  int blue;
} status_reflektora;

typedef struct status_animacije {
  status_reflektora ref1;
  status_reflektora ref2;
} status_animacije;

/* PROTOTIPI */
//scena1 -- svaka animacija je jedan kus te scene
void animation1(status_animacije *state);
void animation2(status_animacije *state);
void animation3(status_animacije *state);
void animation4(status_animacije *state);
void animation5(status_animacije *state);
//scena2
void animation6(status_animacije *state); 
void animation7(status_animacije *state);
void animation8(status_animacije *state);
void animation9(status_animacije *state);
void animation10(status_animacije *state);


/* DEFINICIJE */
//scena1
status_animacije animation1_state;
status_animacije animation2_state;
status_animacije animation3_state;
status_animacije animation4_state;
status_animacije animation5_state;
//scena2
status_animacije animation6_state;
status_animacije animation7_state;
status_animacije animation8_state;
status_animacije animation9_state;
status_animacije animation10_state;

void setup() {
  //Serial.begin(9600);
  DmxSimple.maxChannel(6);
  pinMode(trigRecievePin, INPUT);

  animation_cycle = 0;
  scene_switcher = 1;

  /*DMX -- ALOKACIJA MEMORIJE*/
  //scena1
  memset(&animation1_state, 0, sizeof(status_animacije));
  memset(&animation2_state, 0, sizeof(status_animacije));
  memset(&animation3_state, 0, sizeof(status_animacije));
  memset(&animation4_state, 0, sizeof(status_animacije));
  memset(&animation5_state, 0, sizeof(status_animacije));
  //scena2
  memset(&animation6_state, 0, sizeof(status_animacije));
  memset(&animation7_state, 0, sizeof(status_animacije));
  memset(&animation8_state, 0, sizeof(status_animacije));
  memset(&animation9_state, 0, sizeof(status_animacije));
  memset(&animation10_state, 0, sizeof(status_animacije));
}

void loop() {

  trigRecieveState = digitalRead(trigRecievePin);

  if ( trigRecieveState == HIGH) {
    /* SCENES BOUNDLE */
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= MIN_DELAY) {
      previousMillis = currentMillis;
      switch (scene_switcher) {
        case 1:
          scena_1();
          break;
        case 2:
          scena_2();
          break;
      }
    } // millis
  } // sen state

  if ( trigRecieveState == LOW) {
    animation_cycle = 0;
    mrak();
  }

} // loop

void scena_1() {
  switch (animation_cycle) {
    case 0:
      //mrak();
      ++animation_cycle;
      break;
    case 1:
      animation1(&animation1_state);
      break;
    case 2:
      animation2(&animation2_state);
      break;
    case 3:
      animation3(&animation3_state);
      break;
    case 4:
      animation4(&animation4_state);
      break;
    case 5:
      animation5(&animation5_state);
      break;
  }
}

void scena_2() {
  switch (animation_cycle) {
    case 0:
      //mrak();
      ++animation_cycle;
      break;
    case 1:
      animation6(&animation6_state);
      break;
    case 2:
      animation7(&animation7_state);
      break;
    case 3:
      animation8(&animation8_state);
      break;
    case 4:
      animation9(&animation9_state);
      break;
    case 5:
      animation10(&animation10_state);
      break;
  }
}


//SCENA1_parts
void animation1(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue); // za refl1 spremat ce tu stanje za red, green i blue.. 
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue); // za refl2 spremat ce tu stanje za red, green i blue.. 

  state->ref1.red = 254;
  state->ref1.green = 254;
  state->ref1.blue = 254; 
  state->ref2.red = 254;
  state->ref2.green = 254;
  state->ref2.blue = 254; 
  
  state->ref1.red +=1;
  state->ref1.green +=1;
  state->ref1.blue +=1; 
  state->ref2.red +=1;
  state->ref2.green +=1;
  state->ref2.blue +=1; 
  
  

  if (state->ref1.red >= 255 && state->ref1.green >= 255 && state->ref1.blue >= 255 && state->ref2.red >= 255 && state->ref2.green >= 255 && state->ref2.blue >= 255) { // tu postavljamo do kuda koja boja ide maximalno (255, 185, bla bla bla whatever)
   
    animation2_state = *state; 
    ++animation_cycle;
  }
}

void animation2(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue);
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue);

  state->ref1.blue -= 1;
  state->ref1.red -= 1;

  state->ref2.green -= 1;
  state->ref2.red -= 1;

  if (
    (state->ref1.blue <= 0 && state->ref1.red <= 0) &&
    (state->ref2.green <= 0 && state->ref2.red <= 0)
  ) {
    animation3_state = *state;
    ++animation_cycle;
  }
}

void animation3(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue);
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue);

  state->ref1.green -= 1;
  state->ref1.blue += 1;
  
  state->ref2.green += 1;
  state->ref2.blue -= 1;
  
  if (state->ref1.blue >= 255 || state->ref2.green >=255) {
    animation4_state = *state;
    ++animation_cycle;
  }
}
// --- 4) ( dodat ponasanje ciklusa, tj komnada scene)
void animation4(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue);
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue);

  state->ref2.green -= 1;
  state->ref2.blue += 1;

  if (state->ref2.blue >= 255 || state->ref2.green <= 0) {
    
    animation5_state = *state;
    ++animation_cycle;
  }
}
void animation5(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue);
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue);

  state->ref1.red += 1;
  state->ref1.green += 1;
  state->ref2.red += 1;
  state->ref2.green += 1;

  if (state->ref1.red >= 255 || state->ref2.red >= 255) {
    ++scene_switcher;
    ++animation_cycle;
    delay(4000);
  }
  
}

//SCENA2_parts

void animation6(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue); // za refl1 spremat ce tu stanje za red, green i blue.. 
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue); // za refl2 spremat ce tu stanje za red, green i blue.. 

  state->ref1.red = 254;
  state->ref1.green = 254;
  state->ref1.blue = 254; 
  state->ref2.red = 254;
  state->ref2.green = 254;
  state->ref2.blue = 254; 
  
  state->ref1.red +=1;
  state->ref1.green +=1;
  state->ref1.blue +=1; 
  state->ref2.red +=1;
  state->ref2.green +=1;
  state->ref2.blue +=1; 
  
  

  if (state->ref1.red >= 255 && state->ref1.green >= 255 && state->ref1.blue >= 255 && state->ref2.red >= 255 && state->ref2.green >= 255 && state->ref2.blue >= 255) { // tu postavljamo do kuda koja boja ide maximalno (255, 185, bla bla bla whatever) 
    animation7_state = *state; 
    ++animation_cycle;
  }
}

void animation7(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue);
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue);

  state->ref1.blue -= 1;
  state->ref1.green -= 1;

  state->ref2.blue -= 1;

  if ( state->ref1.blue <= 0 && state->ref1.green <= 0 && state->ref2.blue <= 0 ) {
    animation8_state = *state;
    ++animation_cycle;
  }
}

void animation8(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue);
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue);

  state->ref1.green += 1;
    
  state->ref2.green -= 1;
  
  if (state->ref1.green >= 255 || state->ref2.green <= 0) {
    animation9_state = *state;
    ++animation_cycle;
  }
}

// --- 4) ( dodat ponasanje ciklusa, tj komnada scene)
void animation9(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue);
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue);

  state->ref1.green -= 2;
 
  if (state->ref1.green <= 0 ) {   
    animation10_state = *state;
    ++animation_cycle;
  }
  
}

void animation10(status_animacije *state) {

  reflektor_1(state->ref1.red, state->ref1.green, state->ref1.blue);
  reflektor_2(state->ref2.red, state->ref2.green, state->ref2.blue);

  state->ref1.green += 1;
  state->ref1.blue += 1;
  state->ref2.green += 1;
  state->ref2.blue += 1;

  if (state->ref1.green >= 255 || state->ref2.green >= 255 || state->ref1.blue >= 255 || state->ref2.blue >= 255) {
    scene_switcher = 1;
    ++animation_cycle;
    delay(4000);
    }
}


void reflektor_1(int r, int g, int b) {
  if (r > 255) r = 255;
  if (g > 255) g = 255;
  if (b > 255) b = 255;

  if (r < 0) r = 0;
  if (g < 0) g = 0;
  if (b < 0) b = 0;

  DmxSimple.write(1, r); 
  DmxSimple.write(2, g);
  DmxSimple.write(3, b);
}

void reflektor_2(int r, int g, int b) {
  if (r > 255) r = 255;
  if (g > 255) g = 255;
  if (b > 255) b = 255;

  if (r < 0) r = 0;
  if (g < 0) g = 0;
  if (b < 0) b = 0;

  DmxSimple.write(4, r); 
  DmxSimple.write(5, g);
  DmxSimple.write(6, b);
}


void mrak() {
  
  reflektor_1(0, 0, 0); //000
  reflektor_2(0, 0, 0);

  memset(&animation1_state, 0, sizeof(status_animacije));
  memset(&animation2_state, 0, sizeof(status_animacije));
  memset(&animation3_state, 0, sizeof(status_animacije));
  memset(&animation4_state, 0, sizeof(status_animacije));
  memset(&animation5_state, 0, sizeof(status_animacije));//3) resetiranje vrij*/
  
  memset(&animation6_state, 0, sizeof(status_animacije));
  memset(&animation7_state, 0, sizeof(status_animacije));
  memset(&animation8_state, 0, sizeof(status_animacije));
  memset(&animation9_state, 0, sizeof(status_animacije));
  memset(&animation10_state, 0, sizeof(status_animacije));
  
  DmxSimple.write(1, 0);
  DmxSimple.write(2, 0);
  DmxSimple.write(3, 0);

  DmxSimple.write(4, 0);
  DmxSimple.write(5, 0);
  DmxSimple.write(6, 0);
}

