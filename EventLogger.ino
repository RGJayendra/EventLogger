// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>

char timedatebuf[65];  // Time and Date string buffer

// Operation order input number  1A
  int CB_On_Order          = 22;
  int CB_Off_Order         = 24;
  int Line_Ds_On_Order     = 30;
  int Line_Ds_Off_Order    = 32;
  int B_Ds1_On_Order       = 38;
  int B_Ds1_Off_Order      = 42;
  int B_Ds2_On_Order       = 23;
  int B_Ds2_Off_Order      = 25;
 // int E_SW_Release         = 49;
// Equipment status input number  1B
  int CB_On           = 26;
  int CB_Off          = 28;
  int Line_Ds_On      = 34;
  int Line_Ds_Off     = 36;
  int B_Ds_On         = 40;
  int B_Ds_Off        = 44;
  int B_Ds2_On        = 27;
  int B_Ds2_Off       = 29;
  int E_SW_On         = 46;
  int E_SW_Off        = 48;
  int Vt_Mcb_Trip     = 31;
  int Pole_Discrepancy= 35;
  int Cb_Mcb_Trip     = 37;
  int Spring_Discharge= 39;
  int Sf6_Lockout     = 41;
  int Sf6_Alarm       = 43;
  int Sync_Not_Ok     = 45;
  int Interlock_Not_Ok = 47;

RTC_DS1307 rtc;

// Operation order variables   2A
  boolean CB_ON_ORDER;           
  boolean CB_OFF_ORDER;
  boolean LINE_DS_ON_ORDER;
  boolean LINE_DS_OFF_ORDER;
  boolean B_DS1_ON_ORDER;
  boolean B_DS1_OFF_ORDER;
  boolean B_DS2_ON_ORDER;
  boolean B_DS2_OFF_ORDER;
 // boolean E_SW_RELEASE;

// Equipment status variables   2B

  boolean CB_ON;
  boolean CB_OFF;
  boolean LINE_DS_ON;
  boolean LINE_DS_OFF;
  boolean B_DS_ON;
  boolean B_DS_OFF;
  boolean B_DS2_ON;
  boolean B_DS2_OFF;
  boolean E_SW_ON;
  boolean E_SW_OFF;
  boolean VT_MCB_TRIP;
  boolean POLE_DISCREPANCY;
  boolean CB_MCB_TRIP;
  boolean SPRING_DISCHARGE;
  boolean SF6_LOCKOUT;
  boolean SF6_ALARM;
  boolean SYNC_NOT_OK;
  boolean INTERLOCK_NOT_OK;
  
// Previous equipment status variables  3B

  boolean CB_ON_P;
  boolean CB_OFF_P;
  boolean LINE_DS_ON_P;
  boolean LINE_DS_OFF_P;
  boolean B_DS_ON_P;
  boolean B_DS_OFF_P;
  boolean B_DS2_ON_P;
  boolean B_DS2_OFF_P;
  boolean E_SW_ON_P;
  boolean E_SW_OFF_P;
  boolean VT_MCB_TRIP_P;
  boolean POLE_DISCREPANCY_P;
  boolean CB_MCB_TRIP_P;
  boolean SPRING_DISCHARGE_P;
  boolean SF6_LOCKOUT_P;
  boolean SF6_ALARM_P;
  boolean SYNC_NOT_OK_P;
  boolean INTERLOCK_NOT_OK_P;


  


// Status change variable

boolean STATE_CHANGE;



void setup () {

  Serial.begin(9600);
  
  while (!Serial) {;} // wait for serial port to connect. Needed for native USB port only
  
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(49)) {
      Serial.println("initialization failed!");
      while (1);}
      
  Serial.println("initialization done.");
  
  if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      Serial.flush();
      while (1) delay(10);}
  
  if (! rtc.isrunning()) {
      Serial.println("RTC is NOT running, let's set the time!");
      // When time needs to be set on a new device, or after a power loss, the
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));}
  
  }

void loop () {

  STATE_CHANGE = LOW;

//Reading operation order and status input///////////////////////////////////// 

    CB_ON_ORDER=digitalRead(CB_On_Order);
    CB_OFF_ORDER=digitalRead(CB_Off_Order);///////////////4B
    CB_ON=digitalRead(CB_On);
    CB_OFF=digitalRead(CB_Off);////////////////////////////////////////5B
    LINE_DS_ON_ORDER=digitalRead(Line_Ds_On_Order);
    LINE_DS_OFF_ORDER=digitalRead(Line_Ds_Off_Order);
    LINE_DS_ON=digitalRead(Line_Ds_On);
    LINE_DS_OFF=digitalRead(Line_Ds_Off); 
    B_DS1_ON_ORDER=digitalRead(B_Ds1_On_Order);
    B_DS1_OFF_ORDER=digitalRead(B_Ds1_Off_Order);
    B_DS_ON=digitalRead(B_Ds_On);
    B_DS_OFF=digitalRead(B_Ds_Off);
    B_DS2_ON_ORDER=digitalRead(B_Ds2_On_Order);
    B_DS2_OFF_ORDER=digitalRead(B_Ds2_Off_Order);
    B_DS2_ON=digitalRead(B_Ds2_On);
    B_DS2_OFF=digitalRead(B_Ds2_Off);
//    E_SW_RELEASE=digitalRead(E_SW_Release);
    E_SW_ON=digitalRead(E_SW_On);
    E_SW_OFF=digitalRead(E_SW_Off);
    VT_MCB_TRIP=digitalRead(Vt_Mcb_Trip);
    POLE_DISCREPANCY=digitalRead(Pole_Discrepancy);  
    CB_MCB_TRIP=digitalRead(Cb_Mcb_Trip);
    SPRING_DISCHARGE=digitalRead(Spring_Discharge);
    SF6_LOCKOUT=digitalRead(Sf6_Lockout);
    SF6_ALARM=digitalRead (Sf6_Alarm);
    SYNC_NOT_OK=digitalRead(Sync_Not_Ok);
    INTERLOCK_NOT_OK=digitalRead(Interlock_Not_Ok);
    
//Detecting Equipment State change/////////////////////////////////////////////
   
  if (not((CB_ON_P == CB_ON)and             //Q0
     (CB_OFF_P == CB_OFF)))//////////////////6B
     {STATE_CHANGE = HIGH;}

  if (STATE_CHANGE == HIGH) {      //Updating state of equipment if state change true/////////////////////////////
      CB_ON_P = CB_ON;
      CB_OFF_P = CB_OFF;     }

  if (not((LINE_DS_ON_P == LINE_DS_ON)and  //Q9
        (LINE_DS_OFF_P == LINE_DS_OFF)))
        {STATE_CHANGE =HIGH;}    

  if (STATE_CHANGE == HIGH){
      LINE_DS_ON_P  = LINE_DS_ON;
      LINE_DS_OFF_P = LINE_DS_OFF;
  }
  if (not((B_DS_ON_P == B_DS_ON)and  //Q1
        (B_DS_OFF_P == B_DS_OFF)))
        {STATE_CHANGE =HIGH;}    

  if (STATE_CHANGE == HIGH){
      B_DS_ON_P  = B_DS_ON;
      B_DS_OFF_P = B_DS_OFF;
  }
  if (not((B_DS2_ON_P == B_DS2_ON)and  //Q2
        (B_DS2_OFF_P == B_DS2_OFF)))
        {STATE_CHANGE =HIGH;}    

  if (STATE_CHANGE == HIGH){
      B_DS2_ON_P  = B_DS2_ON;
      B_DS2_OFF_P = B_DS2_OFF;
  }

  if (not((E_SW_ON_P == E_SW_ON)and  //Q9
        (E_SW_OFF_P == E_SW_OFF)))
        {STATE_CHANGE =HIGH;}    

  if (STATE_CHANGE == HIGH){
      E_SW_ON_P = E_SW_ON;
      E_SW_OFF_P = E_SW_OFF;
  }



  if (not((VT_MCB_TRIP_P == VT_MCB_TRIP)and  //Q2
        (POLE_DISCREPANCY_P == POLE_DISCREPANCY)and
        (CB_MCB_TRIP_P == CB_MCB_TRIP)and
        (SPRING_DISCHARGE_P == SPRING_DISCHARGE)and
        (SF6_LOCKOUT_P == SF6_LOCKOUT)and
        (SF6_ALARM_P == SF6_ALARM)and
        (SYNC_NOT_OK_P == SYNC_NOT_OK)and
        (INTERLOCK_NOT_OK_P == INTERLOCK_NOT_OK)))
        {STATE_CHANGE =HIGH;}    




  if (STATE_CHANGE == HIGH){
      VT_MCB_TRIP_P  = VT_MCB_TRIP;
      POLE_DISCREPANCY_P = POLE_DISCREPANCY;
      CB_MCB_TRIP_P  = CB_MCB_TRIP;
      SPRING_DISCHARGE_P  = SPRING_DISCHARGE;
      SF6_LOCKOUT_P  = SF6_LOCKOUT;
      SF6_ALARM_P  = SF6_ALARM;
      SYNC_NOT_OK_P  = SYNC_NOT_OK;
      INTERLOCK_NOT_OK_P = INTERLOCK_NOT_OK;
  }




  
  

  
  
// 
//writng data to SD Card//////////////////////////////////////////////////////

  if ((CB_ON_ORDER == HIGH)or (CB_OFF_ORDER == HIGH)or(STATE_CHANGE == HIGH)or
     (LINE_DS_ON_ORDER == HIGH) or(LINE_DS_OFF_ORDER == HIGH) or
     (B_DS1_ON_ORDER == HIGH) or(B_DS1_OFF_ORDER == HIGH) or
     (B_DS2_ON_ORDER == HIGH) or(B_DS2_OFF_ORDER == HIGH)){
        
       DateTime now = rtc.now();
    //Circuit Breaker (Q0).4A
        if (CB_ON_ORDER==HIGH)sprintf(timedatebuf,"Date:-%02d/%02d/%02d  Time:-%02d:%02d:%02d ---->Circuit Breaker ON Order",now.day(),now.month(),now.year(),now.hour(),now.minute(),now.second());
        else if (CB_OFF_ORDER==HIGH)sprintf(timedatebuf,"Date:-%02d/%02d/%02d  Time:-%02d:%02d:%02d ---->Circuit Breaker OFF Order",now.day(),now.month(),now.year(),now.hour(),now.minute(),now.second());
        
  
    //Line disconnector (Q9)
       else if (LINE_DS_ON_ORDER == HIGH)sprintf(timedatebuf,"Date:-%02d/%02d/%02d Time:-%02d:%02d:%02d---->  Line Disconnector ON Order",now.day(),now.month(),now.year(),now.hour(),now.minute(),now.second());
       else if(LINE_DS_OFF_ORDER==HIGH)sprintf(timedatebuf,"Date:-%02d/%02d/%02d Time:-%02d:%02d:%02d---->Line Disconnector OFF Order",now.day(),now.month(),now.year(),now.hour(),now.minute(),now.second());
    //bus disconnector(Q1)
       else if (B_DS1_ON_ORDER == HIGH)sprintf(timedatebuf,"Date:-%02d/%02d/%02d Time:-%02d:%02d:%02d---->Bus01 Disconnector ON Order",now.day(),now.month(),now.year(),now.hour(),now.minute(),now.second());
       else if(B_DS1_OFF_ORDER==HIGH)sprintf(timedatebuf,"Date:-%02d/%02d/%02d Time:-%02d:%02d:%02d---->Bus01 Disconnector OFF Order",now.day(),now.month(),now.year(),now.hour(),now.minute(),now.second());
     //Earth Switch
     //bus disconnector(Q2)
       else if (B_DS2_ON_ORDER == HIGH)sprintf(timedatebuf,"Date:-%02d/%02d/%02d Time:-%02d:%02d:%02d---->Bus02 Disconnector ON Order",now.day(),now.month(),now.year(),now.hour(),now.minute(),now.second());
       else if(B_DS2_OFF_ORDER==HIGH)sprintf(timedatebuf,"Date:-%02d/%02d/%02d Time:-%02d:%02d:%02d---->Bus02 Disconnector OFF Order",now.day(),now.month(),now.year(),now.hour(),now.minute(),now.second());
       else if (STATE_CHANGE==HIGH)sprintf(timedatebuf,"Date:-%02d/%02d/%02d  Time:-%02d:%02d:%02d ---->Eq. State or Alarm Change",now.day(),now.month(),now.year(),now.hour(),now.minute(), now.second());
    



       
////////////////////////Creating file to write the event////////////////////////

      
        File dataFile = SD.open("event.txt", FILE_WRITE);  // Open or Create file 

////////////////////////Writing Control Order to file/////////////////////////////       

      if (dataFile) {  // Check if file exist on SD Card
         dataFile.println(timedatebuf);
         Serial.println(timedatebuf);
         
////////////////////////Equipment States////////////////////////////////////////////////    
        if (VT_MCB_TRIP ==HIGH){                                  //vt mcb trip.
           dataFile.println ("VT MCB TRIP");  
           Serial.println   ("VT MCB TRIP");}            
        if (POLE_DISCREPANCY==HIGH){                              //pole discrepancy.
           dataFile.println ("POLE DISCREPANCY");  
           Serial.println   ("POLE DISCREPANCY");}   

        if (CB_MCB_TRIP==HIGH){                                  //cb mcb trip.
           dataFile.println ("CB_MCB_TRIP");  
           Serial.println   ("CB_MCB_TRIP");} 

        if (SPRING_DISCHARGE==HIGH){                             //spring discharge.
           dataFile.println ("SPRING_DISCHARGE");  
           Serial.println   ("SPRING_DISCHARGE");} 

        if (SF6_LOCKOUT==HIGH){                                  //sf.6 lockout
           dataFile.println ("SF6 LOCK OUT");  
           Serial.println   ("SF6 LOCK OUT");} 

        if (SF6_ALARM==HIGH){                                    //sf6. alarm.
           dataFile.println ("SF6 ALARM");  
           Serial.println   ("SF6 ALARM");} 

        if (SYNC_NOT_OK==HIGH){                                  //sync not ok.
           dataFile.println ("Sync Ok");  
           Serial.println   ("Sync Ok");} 
        if (INTERLOCK_NOT_OK==HIGH){                             //interlock not ok.
           dataFile.println ("Inter Lock Not OK.");  
           Serial.println   ("Inter Lock Not OK.");}

            
         if (CB_ON == HIGH){                                      //Circuit Breaker(Q0).
           dataFile.println ("");
           Serial.println ("");
           dataFile.println ("Circuit Breaker    (Q0) -ON");    
           Serial.println   ("Circuit Breaker    (Q0) -ON");} 
         if (CB_OFF == HIGH){
           dataFile.println ("");
           Serial.println ("");
           dataFile.println ("Circuit Breaker    (Q0) -OFF");
           Serial.println   ("Circuit Breaker    (Q0) -OFF");}   
         if (LINE_DS_ON==HIGH){                                   //Line Disconnector(Q9).
           dataFile.println ("Line Disconnector  (Q9) -ON");  
           Serial.println   ("Line Disconnector  (Q9) -ON");} 
         if (LINE_DS_OFF==HIGH){
           dataFile.println ("Line Disconnector  (Q9) -OFF");  
           Serial.println   ("Line Disconnector  (Q9) -OFF");} 
         if (B_DS_ON==HIGH){                                      //Bus Disconnector(Q1).
           dataFile.println ("Bus01 Disconnector (Q1) -ON");  
           Serial.println   ("Bus01 Disconnector (Q1) -ON");} 
        if (B_DS_OFF==HIGH){
           dataFile.println ("Bus01 Disconnector (Q1) -OFF");  
           Serial.println   ("Bus01 Disconnector (Q1) -OFF");} 
           if (B_DS2_ON==HIGH){                                   //Bus Disconnector(Q2).
           dataFile.println ("Bus02 Disconnector  (Q2) -ON");  
           Serial.println   ("Bus02 Disconnector  (Q2) -ON");} 
        if (B_DS2_OFF==HIGH){
           dataFile.println ("Bus02 Disconnector (Q2) -OFF");  
           Serial.println   ("Bus02 Disconnector (Q2) -OFF");}    
        if (E_SW_ON== HIGH){                                      //Earth Switch(Q9).
           dataFile.println ("Earth Switch       (Q9) -ON");  
           Serial.println   ("Earth Switch       (Q9) -ON");
           Serial.println ("");
           dataFile.println ("");}
        if (E_SW_OFF== HIGH){                            
            dataFile.println("Earth Switch       (Q9) -OFF");  
            Serial.println  ("Earth Switch       (Q9) -OFF");
            Serial.println ("");
            dataFile.println ("");}  
         
           
 ////////////////////////Closing file after writing Equipment States//////////////////////// 
         
         dataFile.close();  // Close file      
      }  
      
      else {
        Serial.println("error opening event.txt"); // if file not on SD Card
      } 
    }  
    

  
 while ((digitalRead(CB_On_Order)== HIGH)or(digitalRead(CB_Off_Order)==HIGH)or     //5A
        (digitalRead(Line_Ds_On_Order )== HIGH)or(digitalRead(Line_Ds_Off_Order )==HIGH)or
        (digitalRead(B_Ds1_On_Order )== HIGH)or(digitalRead(B_Ds1_Off_Order )==HIGH)or 
        (digitalRead(B_Ds2_On_Order )== HIGH)or(digitalRead(B_Ds2_Off_Order )==HIGH))
        {  } // wait until IR is HIGH again
 
  
 delay(100);

  
}
