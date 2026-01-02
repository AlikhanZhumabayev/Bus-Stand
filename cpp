

Servo myServo;

// Pins
const int TEMP_PIN = A0;
const int PIR_PIN = 2;
const int SERVO_PIN = 9;

// Settings
const float HOT_TEMP_C = 27.0;
const unsigned long OFF_DELAY = 20000; // 20 seconds

// Servo positions
const int SERVO_OFF = 0;
const int SERVO_ON = 80;

// State variables
bool servoActive = false;
bool countdownRunning = false;
unsigned long countdownStart = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  myServo.attach(SERVO_PIN);
  myServo.write(SERVO_OFF);

  Serial.begin(9600);
  Serial.println("System ready");
}

void loop() {
  // ---- Read temperature ----
  int raw = analogRead(TEMP_PIN);
  float voltage = raw * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100.0;

  int motion = digitalRead(PIR_PIN);

  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.print(" C | Motion: ");
  Serial.print(motion);
  Serial.print(" | ServoActive: ");
  Serial.print(servoActive);
  Serial.print(" | Countdown: ");
  Serial.println(countdownRunning);

  // ---- Temperature gate ----
  if (tempC < HOT_TEMP_C) {
    if (servoActive) {
      Serial.println("Temp dropped - servo OFF immediately");
    }
    myServo.write(SERVO_OFF);
    servoActive = false;
    countdownRunning = false;
    return; // Ignore motion
  }

  // ---- Motion detected ----
  if (motion == HIGH) {
    if (!servoActive) {
      Serial.println("Motion detected - servo ON");
      myServo.write(SERVO_ON);
      servoActive = true;
    }

    // Pause countdown while motion is active
    countdownRunning = false;
  }

  // ---- Motion stopped ----
  if (motion == LOW && servoActive) {
    if (!countdownRunning) {
      countdownRunning = true;
      countdownStart = millis();
      Serial.println("Motion stopped - countdown started");
    }
  }

  // ---- Countdown handling ----
  if (countdownRunning) {
    unsigned long elapsed = millis() - countdownStart;

    Serial.print("Countdown remaining: ");
    Serial.println((OFF_DELAY - elapsed) / 1000);

    if (elapsed >= OFF_DELAY) {
      Serial.println("Countdown finished - servo OFF");
      myServo.write(SERVO_OFF);
      servoActive = false;
      countdownRunning = false;
    }
  }

  delay(200); // Clean serial output
}
