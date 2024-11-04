// define the maximum allowed brightness
#define LED_MAX     124

int ledState = LED_OFF;
int led1brightness = 0;
int led2brightness = 0;
int led3brightness = 0;
int led4brightness = 0;
unsigned long nextLedUpdate = 0;
bool pulseDirection = true;

void ledSet(int state) {
  ledState = state;
  ledUpdate();
}

void ledUpdate() {
  switch (ledState) {
    case LED_OFF:
      ledOff();
      break;
    case LED_ON:
      ledOn();
      break;
    case LED_SPIN:
      ledSpin();
      break;
    case LED_PULSE:
      ledPulse();
      break;
    case LED_HALF:
      ledHalfOn();
      break;
  }

  analogWrite(LED_PIN_1, led1brightness);
  analogWrite(LED_PIN_2, led2brightness);
  analogWrite(LED_PIN_3, led3brightness);
  analogWrite(LED_PIN_4, led4brightness);
}

void ledOff() {
  led1brightness = 0;
  led2brightness = 0;
  led3brightness = 0;
  led4brightness = 0;
  nextLedUpdate = 0;
}

void ledOn() {
  led1brightness = LED_MAX;
  led2brightness = LED_MAX;
  led3brightness = LED_MAX;
  led4brightness = LED_MAX;
  nextLedUpdate = 0;
}

void ledHalfOn() {
  int newbrightness = round(LED_MAX / 2);
  led1brightness = newbrightness;
  led2brightness = newbrightness;
  led3brightness = newbrightness;
  led4brightness = newbrightness;
  nextLedUpdate = 0;
}

void ledSpin() {
  if (millis() < nextLedUpdate) {
    return;
  }
  
  if (nextLedUpdate == 0) {
    led1brightness = LED_MAX;
    led2brightness = 0;
    led3brightness = 0;
    led4brightness = 0;
  } else {
    led1brightness = (led4brightness == LED_MAX) ? LED_MAX : 0;
    led2brightness = (led1brightness == LED_MAX) ? LED_MAX : 0;
    led3brightness = (led2brightness == LED_MAX) ? LED_MAX : 0;
    led4brightness = (led3brightness == LED_MAX) ? LED_MAX : 0;
  }

  nextLedUpdate = millis() + 300;
}

void ledPulse() {
  if (millis() < nextLedUpdate) {
    return;
  }

  if (led1brightness == 0) {
    pulseDirection = true;
  }

  if (led1brightness == LED_MAX) {
    pulseDirection = false;
  }

  int nextBrightness = 0;
  
  if (pulseDirection) {
    nextBrightness = led1brightness + 1;
  } else {
    nextBrightness = led1brightness - 1;
  }

  if (nextBrightness > LED_MAX) {
    nextBrightness = LED_MAX;
  }

  if (nextBrightness < 0) {
    nextBrightness = 0;
  }

  led1brightness = nextBrightness;
  led2brightness = nextBrightness;
  led3brightness = nextBrightness;
  led4brightness = nextBrightness;

  nextLedUpdate = millis() + 75;
}
