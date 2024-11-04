void setupSpeaker() {
  ledcAttachPin(SPEAKER_PIN, SPEAKER_CHANNEL);
}

void ampOn() {
  #if AMP_PIN >= 0
    if (!muted) {
      digitalWrite(AMP_PIN, HIGH);
    }
  #endif
}

void ampOff() {
  #if AMP_PIN >= 0
    digitalWrite(AMP_PIN, LOW);
  #endif
}

void playTones(int notes[], int durations[], int total) {
  ampOn();
  
  for (int thisNote = 0; thisNote < total; thisNote++) {
    ledcWriteTone(SPEAKER_CHANNEL, notes[thisNote]);
    delay(durations[thisNote]);
  }
  
  ledcWrite(SPEAKER_CHANNEL, 0);
  ampOff();
}

void playBoop() {
  int notes[] = {
    130
  };

  int durations[] = {
    80
  };

  playTones(notes, durations, 1);
}

void playDoubleBoop() {
  int notes[] = {
    130, 0, 130
  };

  int durations[] = {
    80, 40, 80
  };

  playTones(notes, durations, 3);
}

void playTimeout() {
  int notes[] = {
    200, 0, 200, 0, 200
  };

  int durations[] = {
    80, 100, 80, 100, 160
  };

  playTones(notes, durations, 5);
}

void playConnected() {
  int notes[] = {
    130, 135, 140, 150, 160, 170, 180, 190, 200, 210, 220, 260, 300, 350, 400, 460, 560, 720
  };

  int durations[] = {
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 13
  };

  playTones(notes, durations, 18);
}

void playBuzz() {
  int notes[] = {
    320, 0, 540, 0, 970
  };

  int durations[] = {
    250, 50, 100, 30, 75
  };

  playTones(notes, durations, 5);
}
