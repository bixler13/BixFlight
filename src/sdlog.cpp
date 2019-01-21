#include <arduino.h>
#include <SPI.h>
#include "BixFlight.h"
#include "sdlog.h"
#include "SdFat.h"

SdFat sd;
SdFile myfile;
char filename[] = "Data1.csv";

void sdlog_setup(){
  sd.begin(SDchip_pin); //SD_SCK_MHZ(30)
}

void sdlog_loop(){
  myfile.open(filename, O_RDWR | O_CREAT | O_AT_END);
  myfile.println(dt);

  myfile.close();

}


// SdFat sd;
// SdFile file; //creating the file that will be written too in the sd card
// const uint8_t chipSelect = SS;
// #define FILE_BASE_NAME "Data"
//
// ///////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////
//
// void sdlog_setup(){
//   const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
//   char fileName[13] = FILE_BASE_NAME "00.csv";
//
//   if (!sd.begin(chipSelect, SD_SCK_MHZ(10))) {
//     sd.initErrorHalt();
//   }
//
//   while (sd.exists(fileName)) {
//     if (fileName[BASE_NAME_SIZE + 1] != '9') {
//       fileName[BASE_NAME_SIZE + 1]++;
//     } else if (fileName[BASE_NAME_SIZE] != '9') {
//       fileName[BASE_NAME_SIZE + 1] = '0';
//       fileName[BASE_NAME_SIZE]++;
//     }
//     else{
//
//     }
//   }
//   if (!file.open(fileName, O_WRONLY | O_CREAT | O_EXCL)) {
//     //error("file.open");
//   }
//
//   file.print("dt , pitch , roll");
//   file.println();
//
//
// }
//
// //////////////////////////////////////////////////////////////////////////////
//
// void sdlog_loop(){
//
//
// file.print(dt);
// file.write(',');
// file.print(pitch);
// file.write(',');
// file.print(roll);
// file.println();
// }

//setup
  //sd.begin(SDchip_pin);

  //loop
  // log_file = sd.open("DATA.txt", FILE_WRITE);
  //
  // if (log_file){
  //   log_file.print(dt,3);
  //   log_file.print(" , ");
  //   log_file.print(pitch,1);
  //   log_file.print(" , ");
  //   log_file.println(roll,1);
  // }
  // log_file.close();

  /*
 *  Sensor: MPU 6050
 */

 /*
  *  Sensor: MPU 6050
  */
 //
 // #include <SPI.h>
 // //#include <SD.h>
 // #include <SdFat.h>
 // SdFat SD;
 // #include<Wire.h>
 // #include "MPU6050_6Axis_MotionApps20.h"
 //
 // const int chipSelect = 10; //SD Card CS
 // const int MPU = 0x68; // I2C address of the sensor
 // //int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
 // int16_t ax, ay, az, gx, gy, gz;
 // int SwitchPin = 3;
 // int StepsSinceLastFlush = 1;
 // int WaitingLine = 0;
 //
 // MPU6050 mpu;
 //
 // char filename[12] = "DATA001.csv";
 // char numb[4];
 // String str;
 //
 // String dataString = "";
 //
 // unsigned long SamplingTime;
 // unsigned long SampleCounter = 1;
 // unsigned long starttime = 0;
 //
 //
 //
 //
 // void setup()
 // {
 //   Serial.begin(9600);
 //   setParametersForMPU();
 //   pinMode(SwitchPin, INPUT);
 //   SearchSensor(); // I2C Scanner
 //   InitializeSDCard();
 // }
 //
 //
 //
 // void loop()
 // {
 //
 //   if (digitalRead(SwitchPin) == 0) {
 //
 //     filename[4] = '0';
 //     filename[5] = '0';
 //     filename[6] = '1';
 //
 //     for (int m = 1; m < 999; m++) { //Maximum 999 Files.
 //
 //       str = String(m);
 //       str.toCharArray(numb, 4);
 //       if (m < 10) {
 //         filename[6] = numb[0];
 //       }
 //       else if (m < 100) {
 //         filename[6] = numb[1];
 //         filename[5] = numb[0];
 //       }
 //       else {
 //         filename[4] = numb[0];
 //         filename[5] = numb[1];
 //         filename[6] = numb[2];
 //       }
 //       if (!SD.exists(filename)) {
 //         break;
 //       }
 //
 //     }
 //
 //     Serial.println();
 //     Serial.print("Writing to file:  ");
 //     Serial.println(filename);
 //
 //
 //
 //     Serial.print("Starting Data at: ");
 //     Serial.print(millis());
 //     Serial.println(" ms");
 //     int SwitchOn = digitalRead(SwitchPin);
 //     SamplingTime = 0;
 //     File dataFile = SD.open(filename, FILE_WRITE);
 //     starttime = millis();
 //
 //     while (digitalRead(SwitchPin) == 0) { //start and stop data with switch
 //
 //       for (int counter = 1; counter < 300; counter++) { //switch is read every 300 samples
 //         //Improves Performance?--
 //
 //
 //         mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //Raw Data
 //
 //
 //
 //
 //         dataString = "";
 //         dataString += String(SampleCounter);
 //         dataString += ",";
 //         dataString += String(millis());
 //         dataString += ",";
 //         dataString += String(millis() - SamplingTime);
 //         SamplingTime = millis();
 //         dataString += ",";
 //         dataString += String(ax);
 //         dataString += ",";
 //         dataString += String(ay);
 //         dataString += ",";
 //         dataString += String(az);
 //         dataString += ",";
 //         dataString += String(gx);
 //         dataString += ",";
 //         dataString += String(gy);
 //         dataString += ",";
 //         dataString += String(gz);
 //         //Find more efficient way to save the data
 //
 //         dataFile.println(dataString); //Saves the datastring to SD or some other place?
 //
 //
 //
 //
 //
 //         //Serial.println(sizeof(dataString));
 //
 //
 //         if (StepsSinceLastFlush >= 54) { //54 in this case is a random value
 //           //works fine, because as I see it each DataString has a size of 6 bytes
 //           //so the SD Card always saves about 300 bytes of the 512 bytes possible
 //
 //           dataFile.flush();
 //           StepsSinceLastFlush = 1;
 //         }
 //
 //         StepsSinceLastFlush++;
 //         SampleCounter++;
 //
 //
 //       }
 //
 //     }
 //
 //
 //     dataFile.close(); //Save everything to SD
 //
 //     Serial.println ();
 //     Serial.print ("Stop Data at:   ");
 //     unsigned long endtime = millis();
 //
 //     Serial.println(endtime);
 //     Serial.println("Finished writing file");
 //     Serial.print(((endtime - starttime) * 0.001) );
 //     Serial.println("   Seconds");
 //     Serial.print((float)SampleCounter / ((float)(endtime - starttime) * 0.001) );
 //     Serial.println("   Hz");
 //
 //   }
 //   else { //Waiting Line
 //
 //
 //
 //     while (!SD.begin(chipSelect)) {
 //       Serial.println("");
 //       Serial.println(F("Card failed, or not present"));
 //       delay(4000);
 //
 //
 //     }
 //     if (WaitingLine == 0) {
 //       Serial.println(F("Switch is off"));
 //       delay(1000);
 //       Serial.println("Ready...");
 //       WaitingLine++;
 //     }
 //     if (WaitingLine > 40) {
 //       Serial.println(F("."));
 //       WaitingLine = 0;
 //       delay(1000);
 //     }
 //     else {
 //       Serial.print(F("."));
 //       delay(1000);
 //       WaitingLine++;
 //     }
 //   }
 //
 // }
 //
 //
 //
 //
 // //--------------------------------------------
 // //            FUNCTIONS
 //
 //
 //
 //
 // void InitializeSDCard()
 // {
 //   Serial.println(F("Initializing SD card..."));
 //   while (!SD.begin(chipSelect)) {
 //
 //     Serial.println(F("Card failed, or not present"));
 //     delay(4000);
 //
 //
 //   }
 //   Serial.println(F("card initialized."));
 // }
 //
 //
 //
 //
 //
 //
 //
 //
 //
 //
 // void SearchSensor() { //I2CScanner Adaption
 //
 //
 //   Serial.println("Scanning...");
 //   byte error, address;
 //   int nDevices;
 //
 //   nDevices = 0;
 //   for (address = 1; address < 127; address++ )
 //   {
 //     // The i2c_scanner uses the return value of
 //     // the Write.endTransmisstion to see if
 //     // a device did acknowledge to the address.
 //     Wire.beginTransmission(address);
 //     error = Wire.endTransmission();
 //
 //     if (error == 0)
 //     {
 //       Serial.print("I2C device found at address 0x");
 //       if (address < 16)
 //         Serial.print("0");
 //       Serial.print(address, HEX);
 //       Serial.println("  !");
 //
 //       nDevices++;
 //     }
 //     else if (error == 4)
 //     {
 //       Serial.print("Unknow error at address 0x");
 //       if (address < 16)
 //         Serial.print("0");
 //       Serial.println(address, HEX);
 //     }
 //   }
 //   if (nDevices == 0) {
 //     Serial.println("No I2C devices found\n");
 //     delay(10000);
 //   }
 //   else
 //     Serial.println("done\n");
 //
 //
 //
 // }
 //
 //
 //
 // void setParametersForMPU() { // No idea...
 //   mpu.initialize();
 //   //mpu.reset();
 //   //delay(100);
 //   //mpu.resetSensors();
 //
 //   mpu.setFullScaleAccelRange(11);
 //   mpu.setFullScaleGyroRange(11);
 //
 //   uint8_t rateset = 7;
 //   mpu.setRate(rateset);
 //
 //   mpu.setSleepEnabled(false);
 //   //mpu.setDLPFMode(MPU6050_DLPF_BW_42);
 //   mpu.setXAccelOffset(3648);
 //   mpu.setYAccelOffset(-2789);
 //   mpu.setZAccelOffset(1010);
 //   mpu.setXGyroOffset(107);
 //   mpu.setYGyroOffset(-42);
 //   mpu.setZGyroOffset(44);
 //   mpu.setAuxVDDIOLevel(1);//Sets High Level of Voltage
 //   //mpu.setDLPFMode(0);
 //   //mpu.setMasterClockSpeed(9);
 //   //uint8_t x = mpu.getAccelerometerPowerOnDelay();
 //   //Serial.println(x);
