bool waterPump = false;
bool drySoil = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Smart Garden Ready");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "TURN_ON_PUMP") {
      waterPump = true;
      Serial.println("Water Pump turned ON");
    } else if (cmd == "TURN_OFF_PUMP") {
      waterPump = false;
      Serial.println("Water Pump turned OFF");
    } else if (cmd == "STATUS") {
      Serial.print("Water Pump: ");
      Serial.println(waterPump ? "ON" : "OFF");
      Serial.print("Soil Moisture: ");
      Serial.println(drySoil ? "DRY" : "WET");
    } else if (cmd == "SIMULATE_DRY") {
      drySoil = true;
      Serial.println("Soil is dry");
    } else if (cmd == "SIMULATE_WET") {
      drySoil = false;
      Serial.println("Soil is wet");
    } else if (cmd == "AUTO") {
      if (drySoil) {
        if (!waterPump) {
          waterPump = true;
          Serial.println("AUTO: Soil dry → Pump turned ON");
        } else {
          Serial.println("AUTO: Soil dry → Pump already ON");
        }
      } else {
        if (waterPump) {
          waterPump = false;
          Serial.println("AUTO: Soil wet → Pump turned OFF");
        } else {
          Serial.println("AUTO: Soil wet → Pump already OFF");
        }
      }
    } else {
      Serial.println("Unknown command");
    }
  }
}
