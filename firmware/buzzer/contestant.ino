#if !IS_HOST
  void setupBuzzer() {
    buttonReady();
    joinHost();
    sendConnectTest();
    setupComplete = true;
    buttonReady();
  }
  
  void loopBuzzer() {
    if (buttonPressed) {
      buttonPressed = false;
      sendBuzz();
      buttonReady();
    }

    if (WiFi.status() != WL_CONNECTED) {
      setupBuzzer();
    }
  }
  
  void sendBuzz() {
    HTTPClient http;
    http.begin("http://192.168.4.1/buzz");
    int httpResponseCode = http.GET();
  
    if (httpResponseCode == 200) {
      getBuzzed();
    }

    if (httpResponseCode == 300) {
      // too soon!
      delay(1000);
    }

    if (httpResponseCode == 418) {
      playDoubleBoop();
      delay(1000);
    }
  }
  
  void getBuzzed() {    
    ledSet(LED_ON);
    playBuzz();
    delay(BUZZ_DURATION);    
    ledSet(LED_OFF);
  }

  void joinHost() {
    WiFi.begin(ssid, password);
    ledSet(LED_ON);
    
    while (WiFi.status() != WL_CONNECTED) {
      ledSet(LED_HALF);
      delay(50);
      ledSet(LED_OFF);
      delay(50);
    }

    ledSet(LED_OFF);
  }

  void sendConnectTest() {
    HTTPClient http;
    http.begin("http://192.168.4.1/ping");
    int httpResponseCode = http.GET();
  
    if (httpResponseCode == 200) {
      playBoop();
    }
  }
#endif
