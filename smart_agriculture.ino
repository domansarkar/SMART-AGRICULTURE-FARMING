/* ###############################################################################################################################################################################################################################
 * ########################     SMART Agriculture Farming Using IoT for Efficient Crop Growth     ################################################################################################################################
 * ###############################################################################################################################################################################################################################
 * SMART Agriculture Farming is a open source project done to ease the use of efficient resources. The project focuses on the different aspects of the soil coditions such 
 * as soil moisture and soil NPK values and controls the values by either the irrigation system or the nutrient supply system. The project uses the ESP8266 to connect to 
 * the Blynk servers to fetch or post values. The app can be replicated using the QR code.
 * 
 * THE PROJECT IS OPEN-SOURCE MEANING YOU CAN CHANGE ANY ASPECT OF THE PROJECT AND POST IT WITHOUT MY CONCENT!
 * so happy coding :)
 * 
 * Components:-
 * SNo.       COMPONENT                 QTY
 * 1.         LTR390 UV sensor          01
 * 1.         WS2812B LEDs              01
 * 1.         Battery shield            01
 * 1.         SR602                     01
 * 1.         Solenoid valve            04
 * 1.         Chainable RGB             >=01
 * 1.         LTR390                    01
 * 1.         BME280                    01
 * 1.         Capacitive soil sensor    01
 * 1.         MQ4                       01
 * 1.         MQ135                     01
 * 1.         Li-po 1000mah battery     01
 * 1.         Battery shield            01
 * 
 * Features:-
 * 1. Motion sensor to detect motion (to detect pests or other animals)
 * 2. Can see all the vitals and control it using the app.
 * 3. Gas sensor like CO2 and NH4 can be detected as some plants do release those.
 * 4. UV index and sunlight level detection.
 * 5. Artificial night growth lights.
 * 6. Timer to irrigation system and the artificail night light.
 * 7. Tmeperature, Humidity and pressure detection.
 * 8. Battery operated and battery level display.
 * 9. Soil humidity detection.
 * 10. NPK values detection and NPK controller.
 * 
 * 
 * CONNECTIONS:-
 * 
 * ## SR-602:-
 * SR-602   ==>    ESP8266
 * VCC -------------> +5v
 * GND -------------> GND
 * OUT -------------> GPIO15
 * 
 * ## WS2812B:-
 * Ws2812b   ==>    ESP8266
 * VCC -------------> +5v
 * GND -------------> GND
 * IN  -------------> GPIO16
 * 
 * ## PUMP:-
 * PUMP      ==>    ESP8266
 * GND -------------> GND
 * IN  -------------> GPIO13
 * 
 * ## Chainable RGB:-
 * RGB       ==>    ESP8266
 * VCC -------------> +5v
 * GND -------------> GND
 * CLK -------------> GPIO12
 * IN  -------------> GPIO14
 * 
 * ## LTR-390:-
 * LTR-390   ==>    ESP8266
 * VCC -------------> +5v
 * GND -------------> GND
 * SCL -------------> GPIO5
 * SDA -------------> GPIO4
 * 
 * ## BME-280:-
 * BME-280   ==>    ESP8266
 * VCC -------------> +5v
 * GND -------------> GND
 * SCL -------------> GPIO5
 * SDA -------------> GPIO4
 * 
 * ## PCF-8591:-
 * PCF-8591  ==>    ESP8266
 * VCC -------------> +5v
 * GND -------------> GND
 * SCL -------------> GPIO5
 * SDA -------------> GPIO4
 * 
 * ## Capacitive soil sensor:-
 * soil mod  ==>    *PCF-8591*
 * VCC -------------> +5v
 * GND -------------> GND
 * OUT -------------> AIN0
 * 
 * ## MQ-4:-
 * MQ-4      ==>    *PCF-8591*
 * VCC -------------> +5v
 * GND -------------> GND
 * OUT -------------> AIN2
 * 
 * ## MQ-135:-
 * MQ-135    ==>    *PCF-8591*
 * VCC -------------> +5v
 * GND -------------> GND
 * OUT -------------> AIN1
 * 
 * ## Battery level:-
 * Battery   ==>    *PCF-8591*
 * VCC -------------> AIN3
 * GND -------------> GND
 * 
 * 
 * NOTE:-
 * The sensors are simply plug and play so if it cant find any sensor it will disable and you can also manually disable them through the code.
 * Just make the value false for the sensor name variable.
 * for e.g MQ4 = false;
 * 
 * 
 * This code can be found on my github
 * github.com/domansarkar/
 * 
 * 
 *                                                        HAPPY CODING EVERYBODY!
 *                                                    ~~~~~~~~~~~~~~by DOMAN SARKAR
 *                                            github.com/domansarkar/SMART-AGRICULTURE-FARMING
 */



///////////////INCLUDE LIBRARIES///////////////
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_PCF8591.h>
#include <LTR390.h>
#include <ChainableLED.h>
#include <FastLED.h>



///////////////DEFINED MACROS///////////////
#define BLYNK_PRINT Serial

#define SEALEVELPRESSURE_HPA (1013.25)

#define ADC_REFERENCE_VOLTAGE 5

#define I2C_ADDRESS 0x53

#define NUM_LEDS 1

#define PCF8591 (0x90 >> 1)

#define LED_PIN     16
#define NUM_LEDS    4
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB



///////////////GLOBAL VARIABLES///////////////
char auth[] = "Cxbm2LYnW8iPsFIqagI9aIZc8N_yNhAa";   /*authentication code sent to your email*/
char ssid[] = "Airtel";                             /*Wifi SSID*/
char pass[] = "mamata@123456";                      /*Wifi password*/

bool BME280 = true;                                 /*enable BME280 (false to disable)*/

float w = 2.255;
float a = 4.078;
float range = a-w;

float m = -0.6527; 
float b = 1.30; 
float R0 = 21.91;
bool MQ4 = true;                                    /*enable MQ4 (false to diable)*/
bool MQ135 = true;                                  /*enable MQ135 (false to disable)*/

bool Mot = true;                                    /*enable motion sensor (false to disable)*/

float hue = 1.0;
bool bulb = true;

byte threshold = 0;

float LEVEL = 0;

unsigned long delayTime;

uint8_t dac_counter = 0;

bool LTR = true;                                    /*enable UV and ambient sensor (false to disable)*/



///////////////CLASSES AND OBJECTS///////////////
Adafruit_BME280 bme; 

Adafruit_PCF8591 pcf = Adafruit_PCF8591();

LTR390 ltr390(I2C_ADDRESS);

WidgetLED led1(V9);

ChainableLED leds(12, 14, NUM_LEDS);

CRGB argb[NUM_LEDS];



///////////////CUSTOM FUNCTIONS///////////////
/*int_to_volts used to convert the digital value from 0-255 from the ADC into voltage(V)*/
float int_to_volts(uint16_t dac_value, uint8_t bits, float logic_level) {
  return (((float)dac_value / ((1 << bits) - 1)) * logic_level);
}

/*BME is used to sense the temp, humidity and pressure*/
void BME(){
  if(!BME280){
    return;
  }
  bme.takeForcedMeasurement();
  Blynk.virtualWrite(V0, bme.readTemperature());
  Blynk.virtualWrite(V1, bme.readPressure() / 100.0F);
  Blynk.virtualWrite(V2, bme.readHumidity());
}

/*ADC is used to get the input from the ADC. Takes argument as the pin number of the ADC and returns the input voltage of the pin.*/
float ADC(byte op){
  pcf.analogWrite(dac_counter++);
  float a0;
  switch(op){
    case 0: a0=int_to_volts(pcf.analogRead(0), 8, ADC_REFERENCE_VOLTAGE);
    break;
    case 1: a0=int_to_volts(pcf.analogRead(1), 8, ADC_REFERENCE_VOLTAGE);
    break;
    case 2: a0=int_to_volts(pcf.analogRead(2), 8, ADC_REFERENCE_VOLTAGE);
    break;
    case 3: a0=int_to_volts(pcf.analogRead(3), 8, ADC_REFERENCE_VOLTAGE);
    break;
    default: a0=-1;
  }
  return a0;
}

/*used to detect the soil moisture level and returns the same*/
byte soilMoisture(){
  float a0 = ADC(0);
  a0 -= w;
  a0 = range - a0;
  a0 = (a0/range)*100;
  Blynk.virtualWrite(V3, a0);
  return a0;
}

/*LTRread is used to read the UV index and the ambient light value*/
void LTRread(){
  if(!LTR){
    return;
  }
  if (ltr390.newDataAvailable()) {
      if (ltr390.getMode() == LTR390_MODE_ALS) {
         Blynk.virtualWrite(V7, ltr390.getLux());
         ltr390.setGain(LTR390_GAIN_18);                  //Recommended for UVI - x18
         ltr390.setResolution(LTR390_RESOLUTION_20BIT);   //Recommended for UVI - 20-bit
         ltr390.setMode(LTR390_MODE_UVS);             
      } else if (ltr390.getMode() == LTR390_MODE_UVS) {
         Blynk.virtualWrite(V8, ltr390.getUVI());
         ltr390.setGain(LTR390_GAIN_3);                   //Recommended for Lux - x3
         ltr390.setResolution(LTR390_RESOLUTION_18BIT);   //Recommended for Lux - 18-bit
         ltr390.setMode(LTR390_MODE_ALS);
      }
  }
}

/*get1mq4 is used to read the C02 values*/
void getMQ4(){
  if(!MQ4){
    return;
  }
  Blynk.virtualWrite(V4, pcf.analogRead(1));
}

/*getMQ135 is used to read the NH4 values*/
void getMQ135(){
  if(!MQ135){
    return;
  }
  Blynk.virtualWrite(V5, pcf.analogRead(2));
}

/*HW438 is used to detect motion in the field*/
void HW438(){
  if(!Mot){
    return;
  }
  if(digitalRead(15)){
    led1.on();
  }
  else{
    led1.off();
  }
}

/*LED is used to control the chainable LEDs*/
void LED(bool v, float h){
  if(v){
    leds.setColorHSB(0, h, 1.0, 0.5);
  }
  else{
    leds.setColorHSB(0, h, 1.0, 0);
  }
}

/*batteryLEVEL is used to calculate the battery level of the battery*/
void batteryLEVEL(){
  ADC(3);
  float h = 4.25;
  float l = 3.2;
  float res = ADC(3)-l;
  res = (res/(h-l))*100;
  res = (res + LEVEL)/2;
  LEVEL = res;
  if(res >100)
  {
    res = 100;
  }
  if(res <0){
    res = 0;
  }
  Blynk.virtualWrite(V6, res);
}


/*BLYNK_WRITE is used to get the values from the server. It is invoked everytime the virtual pin changes its value.*/
BLYNK_WRITE(V10)
{   
  bool value = param.asInt();

  if(value){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
}

BLYNK_WRITE(V11)
{   
  hue = param.asFloat();
  LED(bulb, hue);
}

BLYNK_WRITE(V12)
{   
  bulb = param.asInt();
  LED(bulb, hue);
}

BLYNK_WRITE(V13)
{   
  bool timer = param.asInt();
  if(timer && soilMoisture() >= threshold){
    Blynk.virtualWrite(V10, 1);
    digitalWrite(13, HIGH);
  }
  else{
    Blynk.virtualWrite(V10, 0);
    digitalWrite(13, LOW);
  }
}

BLYNK_WRITE(V14)
{   
  threshold = param.asInt();
}

BLYNK_WRITE(V15)
{   
  bulb = param.asInt();
  Blynk.virtualWrite(V12, bulb);
  LED(bulb, hue);
}

BLYNK_WRITE(V16)
{   
  byte n=param.asInt();
  for(byte i=0;i<n;i++){
    argb[1] = CHSV(0, 255, 255);
    FastLED.show();
    delay(500);
    argb[1] = CHSV(0, 255, 0);
    FastLED.show();
    delay(100);
  }
}

BLYNK_WRITE(V17)
{   
  byte n=param.asInt();
  for(byte i=0;i<n;i++){
    argb[2] = CHSV(145, 255, 255);
    FastLED.show();
    delay(500);
    argb[2] = CHSV(145, 255, 0);
    FastLED.show();
    delay(100);
  }
}

BLYNK_WRITE(V18)
{   
  byte n=param.asInt();
  for(byte i=0;i<n;i++){
    argb[3] = CHSV(0, 0, 255);
    FastLED.show();
    delay(500);
    argb[3] = CHSV(0, 0, 0);
    FastLED.show();
    delay(100);
  }
}




///////////////SETUP///////////////
void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(argb, NUM_LEDS).setCorrection( TypicalLEDStrip );
  argb[0] = CHSV(0,255, 255);
  argb[2] = CHSV(0,255, 255);
  FastLED.show();
  delay(100);
  Blynk.begin(auth, ssid, pass);
  argb[2] = CHSV(96,255, 255);
  FastLED.show();
  delay(200);
  argb[2] = CHSV(0,255, 255);
  FastLED.show();
  if (! bme.begin(0x76, &Wire)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      BME280 = false;
      argb[2] = CHSV(0,255,0);
      FastLED.show();
      delay(100);
      argb[2] = CHSV(0,255, 255);
      FastLED.show();
      delay(200);
  }
  else{
    argb[2] = CHSV(96,255, 255);
    FastLED.show();
    delay(200);
  }
  
  argb[2] = CHSV(0,255, 255);
  FastLED.show();
  if (!pcf.begin()) {
    Serial.println("# Adafruit PCF8591 not found!");
    while (1){
      delay(10);
      argb[2] = CHSV(0,255,0);
      FastLED.show();
      delay(100);
      argb[2] = CHSV(192, 255, 255);
      FastLED.show();
      delay(200);
    }
  }
  else{
    argb[2] = CHSV(96,255,0);
    FastLED.show();
    delay(200);
  }
  argb[2] = CHSV(96,255, 255);
  FastLED.show();
  delay(200);
  argb[2] = CHSV(0,255, 255);
  FastLED.show();
  if(!ltr390.init()){
    Serial.println("LTR390 not connected!");
    LTR = false;
    argb[2] = CHSV(0,255,0);
    FastLED.show();
    delay(100);
    argb[2] = CHSV(0,255, 255);
    FastLED.show();
    delay(200);
  }
  else{
      argb[2] = CHSV(96,255, 255);
      FastLED.show();
      delay(200);
  }
  ltr390.setMode(LTR390_MODE_ALS);
  ltr390.setGain(LTR390_GAIN_3);
  ltr390.setResolution(LTR390_RESOLUTION_18BIT);
  pinMode(13, OUTPUT);
  pcf.enableDAC(true);
  Blynk.syncAll();                                      /*to sync all the previous values from the Blynk server*/
  delay(100);
}




///////////////LOOP///////////////
void loop()
{
  Blynk.run();                                          /*this should be called in every loop to update the blynk server*/
  batteryLEVEL();                                       /*these functions are called one by one to update or get the values*/
  BME();
  soilMoisture();
  LTRread();
  getMQ4();
  getMQ135();
  HW438();
}

/*
 * ################################################################################################################################################################################################################################################
 * #####################################################     END OF FILE    #######################################################################################################################################################################
 * ################################################################################################################################################################################################################################################
 */
