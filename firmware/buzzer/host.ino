#if IS_HOST
  unsigned long unBuzz = 0;
  bool readyToBuzz = false;
  bool tooLong = false;
  hw_timer_t *tooLongTimer = NULL;

  void IRAM_ATTR onTooLongTimer(){
    tooLong = true;
  }

  void setupBuzzer() {
    tooLongTimer = timerBegin(0, 80, true);
    timerAttachInterrupt(tooLongTimer, &onTooLongTimer, true);
    timerAlarmWrite(tooLongTimer, 8000000, false);
    
    // https://github.com/espressif/arduino-esp32/blob/337058ac94e7e3df11d273a93e88d1ea605e6f5f/libraries/WiFi/src/WiFiAP.cpp#L50
    WiFi.softAP(ssid, password, 13, 0, 10);
  
    server.on("/buzz", checkBuzz);
    server.on("/ping", checkPing);
    server.begin();

    buttonReady();
    delay(3000);
    setupComplete = true;
    playBoop();
  }
  
  void loopBuzzer() {
    server.handleClient();

    if (buttonPressed) {
      buttonPressed = false;
      //playTimeout();
      //delay(1000);
      readyToBuzz = true;
      buzzed = false;
      ledSet(LED_OFF);
      startCountdownTimer();
      buttonReady();
    }

    if (tooLong) {
      tooLong = false;
      buzzed = false;
      readyToBuzz = false;
      ledSet(LED_ON);
      playTimeout();
    }
  }
  
  void checkBuzz() {
    if (buzzed == false && readyToBuzz == true) {
      stopCountdownTimer();
      server.send(200, "text/plain", "ok");
      buzzed = true;
      readyToBuzz = false;
      ledSet(LED_ON);
    } else {
      server.send(418, "text/plain", "not ok");
    }

    // server.send(300, "text/plain", "too soon");
  }

  void checkPing() {
    server.send(200, "text/plain", "pong");
  }

  

  void startCountdownTimer() {
    stopCountdownTimer();
    timerWrite(tooLongTimer, 0);
    timerAlarmEnable(tooLongTimer);
  }

  void stopCountdownTimer() {
    timerAlarmDisable(tooLongTimer);
  }
#endif
