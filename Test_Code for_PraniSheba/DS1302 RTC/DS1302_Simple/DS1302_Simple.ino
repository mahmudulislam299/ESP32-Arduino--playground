#include <ThreeWire.h>  
#include <RtcDS1302.h>

//ThreeWire myWire(4,5,2); // IO, SCLK, CE
ThreeWire myWire(21,22,5); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);






void setup () 
{
    Serial.begin(115200);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
  

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
      Serial.println("RTC lost confidence in the DateTime!");
      Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
}

void loop () 
{
    Serial.print("running : "); Serial.println(Rtc.GetIsRunning());
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now); 
    Serial.println();
    Serial.println(tmElements2unix(now));
    Serial.println();
    printDateTime(unix2tmElements(tmElements2unix(now)));
    Serial.println();
    Serial.println();
    Serial.println();

    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }
   
    
    delay(5000); // ten seconds
}

#define countof(a) (sizeof(a) / sizeof(a[0]))


void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
