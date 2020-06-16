#include <Arduino.h>
#include <TinyGPS++.h>

#define DEBUG(x)            Serial.print(x);
#define DEBUGLN(x)          Serial.println(x);

#define GPS_RST                                     PB2
#define GPS_RX                                      PC11
#define GPS_TX                                      PC10
#define GPS_LEVEL_SHIFTER_EN                        PC6
#define GPS_BAUD_RATE                               115200

TinyGPSPlus gps;
HardwareSerial gpsPort(GPS_RX, GPS_TX);

void setup()
{
    Serial.begin(115200);

    delay(2000);

    gpsPort.begin(GPS_BAUD_RATE);

    pinMode(GPS_LEVEL_SHIFTER_EN, OUTPUT);
    digitalWrite(GPS_LEVEL_SHIFTER_EN, HIGH);

    pinMode(GPS_RST, GPIO_PULLUP);
    //Set  Reset Pin as 0
    digitalWrite(GPS_RST, LOW);
    //Scope shows 1.12s (Low Period)
    delay(200);
    //Set  Reset Pin as 1
    digitalWrite(GPS_RST, HIGH);
    delay(100);

    //! Start GPS connamd
    gpsPort.println("@GSR");


}

void loop()
{
    // Dispatch incoming characters
    while (gpsPort.available() > 0)
        gps.encode(gpsPort.read());

    if (gps.charsProcessed() < 10) {
        DEBUGLN(F("WARNING: No GPS data.  Check wiring."));
    }

    if (gps.location.isUpdated()) {
        DEBUG(F("LOCATION   Fix Age="));
        DEBUG(gps.location.age());
        DEBUG(F("ms Raw Lat="));
        DEBUG(gps.location.rawLat().negative ? "-" : "+");
        DEBUG(gps.location.rawLat().deg);
        DEBUG("[+");
        DEBUG(gps.location.rawLat().billionths);
        DEBUG(F(" billionths],  Raw Long="));
        DEBUG(gps.location.rawLng().negative ? "-" : "+");
        DEBUG(gps.location.rawLng().deg);
        DEBUG("[+");
        DEBUG(gps.location.rawLng().billionths);
        DEBUG(F(" billionths],  Lat="));
        DEBUG(gps.location.lat());
        DEBUG(F(" Long="));
        DEBUGLN(gps.location.lng());
    }
    if (gps.date.isUpdated()) {
        DEBUG(F("DATE       Fix Age="));
        DEBUG(gps.date.age());
        DEBUG(F("ms Raw="));
        DEBUG(gps.date.value());
        DEBUG(F(" Year="));
        DEBUG(gps.date.year());
        DEBUG(F(" Month="));
        DEBUG(gps.date.month());
        DEBUG(F(" Day="));
        DEBUGLN(gps.date.day());
    }
    if (gps.time.isUpdated()) {
        DEBUG(F("TIME       Fix Age="));
        DEBUG(gps.time.age());
        DEBUG(F("ms Raw="));
        DEBUG(gps.time.value());
        DEBUG(F(" Hour="));
        DEBUG(gps.time.hour());
        DEBUG(F(" Minute="));
        DEBUG(gps.time.minute());
        DEBUG(F(" Second="));
        DEBUG(gps.time.second());
        DEBUG(F(" Hundredths="));
        DEBUGLN(gps.time.centisecond());
    }
    if (gps.speed.isUpdated()) {
        DEBUG(F("SPEED      Fix Age="));
        DEBUG(gps.speed.age());
        DEBUG(F("ms Raw="));
        DEBUG(gps.speed.value());
        DEBUG(F(" Knots="));
        DEBUG(gps.speed.knots());
        DEBUG(F(" MPH="));
        DEBUG(gps.speed.mph());
        DEBUG(F(" m/s="));
        DEBUG(gps.speed.mps());
        DEBUG(F(" km/h="));
        DEBUGLN(gps.speed.kmph());

    }
    if (gps.course.isUpdated()) {
        DEBUG(F("COURSE     Fix Age="));
        DEBUG(gps.course.age());
        DEBUG(F("ms Raw="));
        DEBUG(gps.course.value());
        DEBUG(F(" Deg="));
        DEBUGLN(gps.course.deg());
    }
    if (gps.altitude.isUpdated()) {
        DEBUG(F("ALTITUDE   Fix Age="));
        DEBUG(gps.altitude.age());
        DEBUG(F("ms Raw="));
        DEBUG(gps.altitude.value());
        DEBUG(F(" Meters="));
        DEBUG(gps.altitude.meters());
        DEBUG(F(" Miles="));
        DEBUG(gps.altitude.miles());
        DEBUG(F(" KM="));
        DEBUG(gps.altitude.kilometers());
        DEBUG(F(" Feet="));
        DEBUGLN(gps.altitude.feet());
    }
    if (gps.satellites.isUpdated()) {
        DEBUG(F("SATELLITES Fix Age="));
        DEBUG(gps.satellites.age());
        DEBUG(F("ms Value="));
        DEBUGLN(gps.satellites.value());
    } else if (gps.hdop.isUpdated()) {
        DEBUG(F("HDOP       Fix Age="));
        DEBUG(gps.hdop.age());
        DEBUG(F("ms Value="));
        DEBUGLN(gps.hdop.value());
    }

}
