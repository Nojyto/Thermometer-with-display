#include <DHT.h>
#include "SSD1306.h"

#define interval 30000 //ms

/*
  --Pinout--
  Addr => 0x3C (oled specific)
  D1   => SCK  (serial Clock)
  D2   => SDA  (serial Data)
*/
SSD1306   dp(0x3C, D1, D2);
DHT       dht(D3, DHT11);

const int cW  = dp.getWidth()  / 2;
const int cH  = dp.getHeight() / 2;

void setup() {
	dht.begin();

	dp.init();
	dp.flipScreenVertically();
	dp.setFont(ArialMT_Plain_16);
	dp.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
}

void loop() {
	int t = dht.readTemperature(),
		h = dht.readHumidity();

	if(isnan(h) || isnan(t)){
		updateDisplay("Failed to read\nfrom sensor!");
	}else{
		updateDisplay("Temp: " + String(t) + " °C\n" +
					  "Humi: " + String(h) + "  %");
	}
	delay(interval);
}

void updateDisplay(const String msg){
    dp.clear();
    dp.drawString(cW, cH, msg);
    dp.display();
}