void displaySpinner(int i) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(Liberation_Mono_Bold_16);
  display.drawString(64, 16, "Connecting");
  display.setFont(Liberation_Mono_10);
  display.drawString(64, 40, STA_SSID);
  display.setFont(Liberation_Mono_10);
  const char* strings[] = {
    "       ",
    "*      ",
    "**     ",
    "***    ",
    " ***   ",
    "  ***  ",
    "   *** ",
    "    ***",
    "     **",
    "      *",
    "       ",
    "       ",
  };
  display.drawString(64, 55, strings[i % 12]);
  display.display();
  Serial.print('.');
}

void displayConnected(IPAddress addr) {
  Serial.println("Connected");
  Serial.print("IP address:");
  Serial.println(addr);

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(Liberation_Mono_Bold_16);
  display.drawString(64, 16, "Connected");
  String ip = addr.toString();
  display.setFont(Liberation_Mono_10);
  display.drawString(64, 40, ip);
  display.display();
}

void displayWaitingForSensor() {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(Liberation_Mono_Bold_16);
  display.drawString(64, 16, "Waiting");
  display.drawString(64, 40, "for sensor");
  display.display();
  lastStatus = "Waiting for sensor";
}

void displayTime() {
  time_t now = time(nullptr);
  display.clear();

  if (now > 365*24*3600) {
    char buf[64];
    strftime(buf, sizeof(buf), "%a %b %d %H:%M", localtime(&now));
    Serial.println(buf);
    display.setFont(Liberation_Mono_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 5, buf);
  }
}

void displayValues(bool ok, int pm25, int pm10) {
  char buf[64];
  if (ok) {
    snprintf(buf, sizeof(buf), "PM2.5 %3d\r\nPM10  %3d\r\n", pm25, pm10);
  }
  else {
    snprintf(buf, sizeof(buf), "No sensor");
  }
  Serial.println(buf);
  lastStatus = buf;
  display.setFont(Liberation_Mono_Bold_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 20, buf);
  display.display();
}

void displayOTAStart() {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(Liberation_Mono_Bold_16);
  display.drawString(64, 16, "OTA starting");
  display.display();
}

void displayOTAProgress(unsigned progress, unsigned size) {
  char buf[17];
  static int prev_percent = -1;
  int percent = progress * 100 / size;
  if (percent != prev_percent) {
    prev_percent = percent;
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(Liberation_Mono_Bold_16);
    display.drawString(64, 16, "Updating");
    display.setFont(Liberation_Mono_10);
    for (int i = 0; i < 16; ++i) {
      if (i * 100 / 16 <= percent) {
        buf[i] = '*';
      }
      else {
        buf[i] = ' ';
      }
    }
    buf[16] = 0;
    display.drawString(64, 40, buf);
    display.display();
  }
  
}

void displayOTAEnd() {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(Liberation_Mono_Bold_16);
  display.drawString(64, 16, "Restarting");
  display.display();
}

void displayOTAError() {
display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(Liberation_Mono_Bold_16);
  display.drawString(64, 16, "OTA error :(");
  display.display();  
}



