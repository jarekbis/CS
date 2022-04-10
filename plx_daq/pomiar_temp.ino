/*
 * Program do odczytu pomiarów temperatury
 */

#include <OneWire.h>

// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// https://github.com/milesburton/Arduino-Temperature-Control-Library
OneWire  ds(10);  // on pin 10 (a 4.7K resistor is necessary)
void setup() {

  // open serial connection
    Serial.begin(9600);

    //Serial.println("CLEARDATA"); // clears sheet starting at row 2
    Serial.println("CLEARSHEET"); // clears sheet starting at row 1
    
  // nazwy trzech kolumn do pierwszego wiersza "Timer", "Temperatura"
    Serial.println("LABEL,Timer,Temperatura,millis/1000");

  // ustaw nazwy dla trzech checkbox 
   Serial.println("CUSTOMBOX1,LABEL,Zatrzymać odczyty po 250?");
   Serial.println("CUSTOMBOX2,LABEL,Wznowić odczyty po 350?");
   Serial.println("CUSTOMBOX3,LABEL,Zakończyć po 450?");

  // check 2 of the 3 checkboxes (first two to true, third to false)
    Serial.println("CUSTOMBOX1,SET,1");
    Serial.println("CUSTOMBOX2,SET,1");
    Serial.println("CUSTOMBOX3,SET,0");
}

void loop() {
  int i = 0;
  byte present=0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;
  //https://www.pjrc.com/teensy/td_libs_OneWire.html
  if ( !ds.search(addr)) {
      //Serial.println("Nie widzę czujnika!");
      //Serial.println();
      ds.reset_search();
      delay(250);
      return;
   }
  // pierwszy odczytany bajt pozwala okreslic rodzaj czujnika
  switch (addr[0]) {
    case 0x10:
      //Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      //Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      //Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      //Serial.println("Urzadzenie spoza rodziny DS18x20.");
      return;
  } 
  ds.reset();  //po określeniu modelu czujnika
  ds.select(addr);  //ustawiamy jego adress
  ds.write(0x44);        //
  
  delay(1000);
  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);
  for ( byte j = 0; j < 9; j++)      // odczyt 9 bajtów
    data[j] = ds.read();
  int16_t raw = (data[1] << 8) | data[0];
   if(type_s){
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
    // simple print out of number and millis. Output e.g.,: "DATA,DATE,TIME,TIMER,4711,13374,AUTOSCROLL_20"
  i++;
  Serial.println( (String) "DATA,TIMER," + celsius + "," + (float)millis()/1000 + ",AUTOSCROLL_20" );
      // alternative writing method:
        /* Serial.print("DATA,DATE,TIME,TIMER,");
        Serial.print(i++); Serial.print(",");
        Serial.println(millis()); 
        Serial.print(","); Serial.println("AUTOSCROLL_20"); */

    // clear some cells in Excel (rectangle range from B10 to D20)
    //  if(i==100)
    //    Serial.println("ClearRange,B,10,D,20");

    // do a simple beep in Excel on PC
      if(i==150)
        Serial.println("BEEP");

    // read a value (in this case integer) from Excel (from a sheet by name)
      if(i==200)
      {
        Serial.println("CELL,GET,FROMSHEET,Simple Data,E,4"); // ==> request value from sheet
       // Serial.println("CELL,GET,E4"); ==> short version to read from active sheet in Excel
        int readvalue = Serial.readStringUntil(10).toInt(); // get response. Note: the '10' is important! Always use but never change ;-)
        Serial.println( (String) "Value of cell E4 is: " + readvalue); // result displayed in Excel DirectDebugWindow to double check
     }

    // check value of custombox1 on PLX DAQ in Excel and if
    // checkbox is checked then send the command to pause logging
      if(i==250)
      {
        Serial.println("CUSTOMBOX1,GET");
        int stoplogging = Serial.readStringUntil(10).toInt();
        // this information can be seen in the direct debug window on PLX DAQ in Excel
        Serial.println( (String) "Value of stoplogging/checkbox is: " + stoplogging);
        if(stoplogging) 
          Serial.println("PAUSELOGGING");
      }

    // get a true random number from the computer
      if(i==300)
      {
        Serial.println("GETRANDOM,-4321,12345"); // between -4321 to 12345
        int rndseed = Serial.readStringUntil(10).toInt();
        Serial.println( (String) "Got random value '" + rndseed + "' from Excel" );
        // Note: this information is not posted to the Excel sheet because "DATA" is missing
        // instead this information can be seen in the direct debug window
      }

    // and now resume logging
      if(i==350)
      {
        Serial.println("CUSTOMBOX2,GET");
        int resumelogging = Serial.readStringUntil(10).toInt();
        if(resumelogging) 
          Serial.println("RESUMELOGGING");
      }   

    // post to specific cells on default sheet as well as named sheet
      if(i==400)
      {
        Serial.println("CELL,SET,G10,400 test 1 string"); // default sheet active in PLX DAQ Excel
        Serial.println("CELL,SET,ONSHEET,Simple Data,G,11,400 test 2 string"); // named sheet available in PLX DAQ Excel
      }
       
    // and for forced quit of Excel with saving the file first
      if(i==450)
      {
        Serial.println("CUSTOMBOX3,GET");
        if(Serial.readStringUntil(10).toInt()) {
          Serial.println("SAVEWORKBOOKAS,450-Lines-File");
          Serial.println("FORCEEXCELQUIT");
        }
        else
          Serial.println("No forced Excel quit requested!");
      }
}
