
// Host or client build
#define IS_HOST           false
#define BOARD_VERSION     2

// Hardware Pinout
#if BOARD_VERSION == 1
  #define LED_PIN_1         1
  #define LED_PIN_2         -1
  #define LED_PIN_3         -1
  #define LED_PIN_4         -1
  #define BUTTON_PIN        9
  #define SPEAKER_PIN       17
  #define SPEAKER_CHANNEL   0
  #define AMP_PIN           -1
#endif

#if BOARD_VERSION == 2
  #define LED_PIN_1         1
  #define LED_PIN_2         2
  #define LED_PIN_3         3
  #define LED_PIN_4         4
  #define BUTTON_PIN        9
  #define SPEAKER_PIN       17
  #define SPEAKER_CHANNEL   0
  #define AMP_PIN           42
#endif

// possible LED states
#define LED_OFF     0
#define LED_ON      1
#define LED_SPIN    2
#define LED_PULSE   3
#define LED_HALF    4

#define BUZZ_DURATION  3000

#include <WiFi.h>

#if !IS_HOST
  #include <HTTPClient.h>
#endif

#if IS_HOST
  #include <WebServer.h>
  WebServer server(80);
#endif

const char* ssid = "jeopardy";
const char* password = "idontknow";

bool buzzed = false;
bool buttonPressed = false;
bool muted = false;
bool setupComplete = false;

void setup() {
  // LED setup
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);

  // Button setup
  pinMode(BUTTON_PIN, INPUT);
  
  // Audio setup
  pinMode(SPEAKER_PIN, OUTPUT);
  #if AMP_PIN >= 0
    pinMode(AMP_PIN, OUTPUT);
    digitalWrite(AMP_PIN, LOW);
  #endif

  setupSpeaker();
  setupBuzzer();
}

void loop() {
  loopBuzzer();
  powerOffWarning();
}

void IRAM_ATTR pressButton() {
  if (!setupComplete) {
    playDoubleBoop();
    muted = true;
  } else {
    buttonPressed = true;
  }
  detachInterrupt(BUTTON_PIN);
}

void buttonReady() {
  attachInterrupt(BUTTON_PIN, pressButton, FALLING);
}

// if the buzzer is powered for more than 2 hours, 
// we need to alert to remove the battery
void powerOffWarning() {
  if (millis() < 7200000) { // 2 hours
    return;
  }

  buttonReady();
  int counter = 0;

  while(counter < 50) {
    if (buttonPressed) {
      resetPowerOffWarning();
    }
    
    ledSet(LED_HALF);
    delay(500);
    ledSet(LED_OFF);
    delay(500);
  }

  playBoop();
}

void resetPowerOffWarning() {
  ESP.restart();
}
