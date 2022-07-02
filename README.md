# SMART-AGRICULTURE-FARMING
Smart Agriculture Farming using IoT for Efficient Crop Growth
/* ####################################################################################################################################################################
 * ########################     SMART Agriculture Farming Using IoT for Efficient Crop Growth     #####################################################################
 * ####################################################################################################################################################################
 * SMART Agriculture Farming is a open source project done to ease the use of efficient resources. The project focuses on the different aspects of the soil coditions
 * such as soil moisture and soil NPK values and controls the values by either the irrigation system or the nutrient supply system. The project uses the ESP8266 to 
 * connect to the Blynk servers to fetch or post values. The app can be replicated using the QR code.
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
