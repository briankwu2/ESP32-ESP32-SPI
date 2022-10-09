#include <Arduino.h>
#include <SPI.h>

#define BAUD_RATE 115200
//Prototype

static void hspi_send_command(); 

static const u_int32_t spiCLK = 1000000; // 1MHZ Clock speed
SPIClass *hspi = NULL;

void setup() {
  // put your setup code here, to run once:


  //
  hspi = new SPIClass(HSPI);
  Serial.begin(BAUD_RATE);
  Serial.print("MOSI PIN: ");
  Serial.println(MOSI);
  Serial.print("MISO PIN: ");
  Serial.println(MISO);
  Serial.print("SCK Pin: ");
  Serial.println(SCK);
  Serial.print("SS Pin: ");
  Serial.println(SS);

  // Initialize the SPIClass with the pin numbers defined by the ESP32
  // SCK = 18U, MISO = 19U, MOSI = 23U, SS = 5U
  hspi->begin(SCK, MISO, MOSI, SS);
  pinMode(SS,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  // Run the send function every 100ms. 
  hspi_send_command();
  delay(100);

}

/**
 * @brief Sends "0" and "1" every 1 second to the peripheral ESP32.
 * 
 */
static void hspi_send_command() {
  byte data_on =  0b00000001; // data 1 to turn LED_ON
  byte data_off = 0b00000000; // data 0 to turn LED_OFF

  //Code to send "0" to the peripheral controlelr
  hspi->beginTransaction(SPISettings(spiCLK, MSBFIRST, SPI_MODE0));
  digitalWrite(SS, LOW); // Select Chip?
  hspi->transfer(data_off);
  digitalWrite(SS, HIGH);
  hspi->endTransaction();
  delay(1000);


  hspi->beginTransaction(SPISettings(spiCLK, MSBFIRST, SPI_MODE0));
  digitalWrite(SS, LOW); // Select Chip?
  hspi->transfer(data_on);
  digitalWrite(SS, HIGH);
  hspi->endTransaction();
  delay(1000);



}