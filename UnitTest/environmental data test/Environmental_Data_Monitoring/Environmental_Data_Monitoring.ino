/*
 *  This code is modified based on BME280 Environmental Data Monitoring Sample Code
 *  made by DFRobot under the GNU Lesser General Public License
 *  the link to the sample code:
 *  https://wiki.dfrobot.com/SIM7000_Arduino_NB-IoT_LTE_GPRS_Expansion_Shield_SKU__DFR0505_DFR0572#target_6
 *  
 */

#include <DFRobot_BME280.h>
#include "Wire.h"

typedef DFRobot_BME280_IIC    BME;    // ******** use abbreviations instead of full names ********

/**IIC address is 0x77 when pin SDO is high (BME280 sensor module)*/
/**IIC address is 0x76 when pin SDO is low  (SIM7000)*/
BME   bme(&Wire, 0x76);   // select TwoWire peripheral and set sensor address

#define SEA_LEVEL_PRESSURE    1015.0f

// show last sensor operate status
void printLastOperateStatus(BME::eStatus_t eStatus)
{
  if (BME::eStatusOK){
    Serial.println("All working properly");
  } else  if (BME::eStatusErr){
    Serial.println("unknow error");
  } else if (BME::eStatusErrDeviceNotDetected){
    Serial.println("device not detected");
  }else  if (BME::eStatusErrParameter){
    Serial.println("parameter error");
  } else{
    Serial.println("unknown error");
  }
}

void setup()
{
  Serial.begin(9600);
  bme.reset();
  Serial.println("bme read data test");
  while(bme.begin() != BME::eStatusOK) {
    Serial.println("bme begin faild");
    printLastOperateStatus(bme.lastOperateStatus);
    //delay(2000);
  }
  Serial.println("bme begin success");
  //delay(100);
}

void loop()
{
  float   temp = bme.getTemperature();
  uint32_t    pressure = bme.getPressure();
  float   alti = bme.calAltitude(SEA_LEVEL_PRESSURE, pressure);
  float   humi = bme.getHumidity();

  while (millis() % 500 == 0){
    Serial.println();
    Serial.println("Data collected: ");
    Serial.println( (String) "temperature : " + temp + " C"); 
    Serial.println((String) "pressure : " + pressure + " Pa"); 
    Serial.println((String)"altitude : " + alti + " m"); 
    Serial.println((String)"humidity : " + humi + " %"); 
  }
  

  //delay(1000);
}
