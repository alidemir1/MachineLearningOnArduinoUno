//Reward Matrice
float Q[7][7] = {{0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0}
};
//Mapping Matrice -1's are walls, 0's are connections and 100 is target
float R[7][7] = {{ -1, 0, -1, -1, -1, -1, -1},
  {0, -1, 0, 0, -1, -1, -1},
  { -1, 0, -1, -1, 0, -1, 100},
  { -1, 0, -1, -1, 0, -1, -1},
  { -1, -1, 0, 0, -1, 0, -1},
  { -1, -1, -1, -1, 0, -1, -1},
  { -1, -1, 0, -1, -1, -1, -1},
};

int M[7][3] = {{1}, {0, 2, 3}, {1, 4, 6}, {1, 4}, {2, 3, 5}, {4}, {2}};

int pins[] = {2, 3, 4, 5, 6, 7, 8};
//random selected action on the current state (or next state)
int action;
//current position
int state;
int i, j, l, m;
int k = 0;
int r;
float gamma = 0.8;
float Qmax;
float a;
float b;
void setup() {
  for (i = 0; i < 7; i++) {
    pinMode(pins[i], OUTPUT);
    Serial.begin(9600);
  }
}

void loop() {
  while (k < 10) {

    //initial state (if you want the change the starting room, change this value to the starting room.)
    state = 0;
    j = state + 2;
    Serial.println(state);
    digitalWrite(j, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);              // wait for a second
    digitalWrite(j, LOW);    // turn the LED off by making the voltage LOW
    delay(100);

    while (state != 6) {
      if (state == 0) {
        action = 1;
      }
      else if (state == 1) {
        r = rand() % 3;
        action = M[1][r];
      }
      else if (state == 2) {
        r = rand() % 3;
        action = M[2][r];
      }
      else if (state == 3) {
        r = rand() % 2;
        action = M[3][r];
      }
      else if (state == 4) {
        r = rand() % 3;
        action = M[4][r];
      }
      else if (state == 5) {
        action = 4 ;
      }
      else if (state == 6) {
        action = 2 ;
      }
      a = -10;
      for (i = 0; i < 7; i++) {
        if (a < Q[action][i]) {
          a = Q[action][i];
        }
      }
      Qmax = a * gamma;
      Q[state][action] = R[state][action] + Qmax;
      state = action;

      Serial.println(state);
      j = state + 2;
      digitalWrite(j, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(200);              // wait for a second
      digitalWrite(j, LOW);    // turn the LED off by making the voltage LOW
      delay(100);


    }
    k++;
  }

  while (1) {
    //initial state (if you want the change the starting room, change this value to the starting room.)
    state = 0;
    j = state + 2;
    Serial.println(state);
    digitalWrite(j, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(300);              // wait for a second
    digitalWrite(j, LOW);    // turn the LED off by making the voltage LOW
    delay(100);   // wait for a second

    //Finds the action with highest score and performs that action
    b = -10;
    while (state != 6) {
      for (i = 0; i < 7; i++) {
        if (b <= Q[state][i]) {
          b = Q[state][i];
          l = i;
        }
      }
      state = l;
      Serial.println(state);
      j = state + 2;
      digitalWrite(j, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(300);              // wait for a second
      digitalWrite(j, LOW);    // turn the LED off by making the voltage LOW
      delay(100);
    }

  }


}
