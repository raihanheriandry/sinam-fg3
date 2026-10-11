#include <Servo.h>

// =====================================
// OBJECT
// =====================================

Servo valveServo;


// =====================================
// PIN
// =====================================

const int soilPin = A0;
const int waterPin = A1;
const int rainAnalogPin = A2;

const int rainDigitalPin = 2;   // External interrupt
const int servoPin = 9;
const int pumpPin = 5;          // Relay


// =====================================
// THRESHOLD
// =====================================

const int soilThreshold = 500;
const int waterThreshold = 500;


// =====================================
// SERVO PULSE WIDTH
// =====================================

// Sesuaikan lagi jika posisi servo fisik berbeda
const int valveClosePulse = 1000;   // Valve tertutup
const int valveOpenPulse  = 1500;   // Valve terbuka


// =====================================
// INTERRUPT VARIABLES
// =====================================

volatile bool rainChanged = false;

bool raining = false;


// =====================================
// INTERRUPT SERVICE ROUTINE
// =====================================

void rainISR() {

  // ISR dibuat sesingkat mungkin
  // Hanya memberi tanda bahwa kondisi rain sensor berubah
  rainChanged = true;
}


// =====================================
// SETUP
// =====================================

void setup() {

  Serial.begin(9600);


  // -----------------------------
  // SERVO
  // -----------------------------

  valveServo.attach(servoPin);

  // Posisi awal valve tertutup
  valveServo.writeMicroseconds(valveClosePulse);


  // -----------------------------
  // RELAY / PUMP
  // -----------------------------

  pinMode(pumpPin, OUTPUT);

  // Relay ACTIVE LOW
  // HIGH = Relay OFF
  // LOW  = Relay ON

  digitalWrite(pumpPin, HIGH);


  // -----------------------------
  // RAINDROP DIGITAL
  // -----------------------------

  pinMode(rainDigitalPin, INPUT);


  // Baca kondisi hujan saat startup
  // LOW  = hujan
  // HIGH = tidak hujan

  raining =
    (digitalRead(rainDigitalPin) == LOW);


  // -----------------------------
  // EXTERNAL INTERRUPT
  // -----------------------------

  attachInterrupt(
    digitalPinToInterrupt(rainDigitalPin),
    rainISR,
    CHANGE
  );


  // -----------------------------
  // STARTUP MESSAGE
  // -----------------------------

  Serial.println("================================");
  Serial.println("SMART IRRIGATION SYSTEM");
  Serial.println("================================");

  Serial.println("Soil  : >= 500 = KERING");
  Serial.println("Water : >= 500 = AIR TERSEDIA");
  Serial.println("Rain  : LOW = HUJAN");

  Serial.println("Relay : LOW = POMPA ON");
  Serial.println("Relay : HIGH = POMPA OFF");

  Serial.println("================================");
}


// =====================================
// MAIN LOOP
// =====================================

void loop() {


  // =================================
  // CEK INTERRUPT RAINDROP
  // =================================

  if (rainChanged) {

    rainChanged = false;

    // Baca ulang kondisi digital sensor
    raining =
      (digitalRead(rainDigitalPin) == LOW);

    Serial.println(
      "Perubahan kondisi hujan terdeteksi!"
    );
  }


  // =================================
  // BACA SENSOR ANALOG
  // =================================

  int soilValue =
    analogRead(soilPin);

  int waterValue =
    analogRead(waterPin);

  int rainValue =
    analogRead(rainAnalogPin);


  // =================================
  // TENTUKAN KONDISI
  // =================================

  // Soil:
  // >= 500 = tanah kering
  // <  500 = tanah basah

  bool soilDry =
    soilValue >= soilThreshold;


  // Water:
  // >= 500 = air tersedia
  // <  500 = air tidak tersedia

  bool waterAvailable =
    waterValue >= waterThreshold;


  // =================================
  // SERIAL MONITOR
  // =================================

  Serial.print("Soil: ");
  Serial.print(soilValue);

  Serial.print(" | Water: ");
  Serial.print(waterValue);

  Serial.print(" | Rain Analog: ");
  Serial.print(rainValue);

  Serial.print(" | Soil Dry: ");
  Serial.print(
    soilDry ? "YES" : "NO"
  );

  Serial.print(" | Water Available: ");
  Serial.print(
    waterAvailable ? "YES" : "NO"
  );

  Serial.print(" | Raining: ");
  Serial.println(
    raining ? "YES" : "NO"
  );


  // =================================
  // IRRIGATION LOGIC
  // =================================


  // ---------------------------------
  // KONDISI 1:
  // HUJAN
  // ---------------------------------

  if (raining) {

    // Pump OFF
    digitalWrite(pumpPin, HIGH);

    // Valve CLOSE
    valveServo.writeMicroseconds(
      valveClosePulse
    );

    Serial.println(
      "HUJAN -> VALVE CLOSE, POMPA OFF"
    );
  }


  // ---------------------------------
  // KONDISI 2:
  // AIR TIDAK TERSEDIA
  // ---------------------------------

  else if (!waterAvailable) {

    // Pump OFF
    digitalWrite(pumpPin, HIGH);

    // Valve CLOSE
    valveServo.writeMicroseconds(
      valveClosePulse
    );

    Serial.println(
      "AIR TIDAK TERSEDIA -> VALVE CLOSE, POMPA OFF"
    );
  }


  // ---------------------------------
  // KONDISI 3:
  // TANAH KERING
  // TIDAK HUJAN
  // AIR TERSEDIA
  // ---------------------------------

  else if (soilDry) {

    // Valve OPEN
    valveServo.writeMicroseconds(
      valveOpenPulse
    );

    // Pump ON
    digitalWrite(pumpPin, LOW);

    Serial.println(
      "TANAH KERING -> VALVE OPEN, POMPA ON"
    );
  }


  // ---------------------------------
  // KONDISI 4:
  // TANAH BASAH
  // ---------------------------------

  else {

    // Pump OFF
    digitalWrite(pumpPin, HIGH);

    // Valve CLOSE
    valveServo.writeMicroseconds(
      valveClosePulse
    );

    Serial.println(
      "TANAH BASAH -> VALVE CLOSE, POMPA OFF"
    );
  }


  Serial.println("--------------------------------");

  delay(500);
}