/* This example uses time from the Choronodot http://www.adafruit.com/products/255  a RTC (Real Time Clock). TimeAlarm can be used to trigger alarms. It is a useful way
to schedule interactions without the need for network connectivity. The clock,  being battery powered, is not affected by power cycles on the arduino, scheduled
interactions occur at the defined time.
The TimeAlarm portion of the example is unaltered. the orginal code, and Time library installation instructions
in can be found here. http://www.pjrc.com/teensy/td_libs_TimeAlarms.html  */



#include <Process.h>
#include <Time.h>
#include <TimeAlarms.h>


String curDateTime = "";
String curYear, curHour, curMin, curSec;

void setup() {
  Serial.begin(9600);
  //    setSyncProvider(RTC.get);   // the function to get the time from the RTC

  while (!Serial);     // do nothing until the serial monitor is opened
  Bridge.begin();  // make contact with the linux processor

  //  Alarm.alarmRepeat(8, 30, 0, MorningAlarm); // 8:30am every day
  //  Alarm.alarmRepeat(19, 16, 0, EveningAlarm); // 5:45pm every day
  //  Alarm.alarmRepeat(dowSaturday, 8, 30, 30, WeeklyAlarm); // 8:30:30 every Saturday
  //
  //  Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds
  //  Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds

  delay(2000);

  Process checkTime;  // initialize a new process
  checkTime.runShellCommand("date \"+%FT%T\"");  // command you want to run

  // while there's any characters coming back from the process, print them to the serial monitor:
  while (checkTime.available() > 0) {
    char c = checkTime.read();
    curDateTime.concat(c);
  }

  int firstDash = curDateTime.indexOf("-");
  int secondDash = curDateTime.lastIndexOf("-");
  int indexOfT = curDateTime.indexOf("T");
  int firstColon = curDateTime.indexOf(":");
  int secondColon = curDateTime.lastIndexOf(":");

  String yearString = curDateTime.substring(0, firstDash);
  String monthString = curDateTime.substring(firstDash + 1, secondDash);
  String dayString = curDateTime.substring(secondDash + 1, indexOfT);
  String hourString = curDateTime.substring(indexOfT + 1, firstColon);
  String minString = curDateTime.substring(firstColon + 1, secondColon);
  String secString = curDateTime.substring(secondColon + 1, curDateTime.length()-1);

  Serial.println(yearString);
  Serial.println(monthString);
  Serial.println(dayString);
  Serial.println(hourString);
  Serial.println(minString);
  Serial.println(secString);

  //  setTime(c);


  //  if (timeStatus() != timeSet)
  //    Serial.println("Unable to sync with the RTC");
  //  else
  //    Serial.println("RTC has set the system time");

}

void loop() {
  // put your main code here, to run repeatedly:
  //  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
  //Serial.println(curDateTime);
  //Serial.println(curYear);
}

void MorningAlarm() {
  Serial.println("Alarm: - turn lights off");
}

void EveningAlarm() {
  Serial.println("Alarm: - turn lights on");
}

void WeeklyAlarm() {
  Serial.println("Alarm: - its Monday Morning");
}

void ExplicitAlarm() {
  Serial.println("Alarm: - this triggers only at the given date and time");
}

void Repeats() {
  Serial.println("15 second timer");
}

void OnceOnly() {
  Serial.println("This timer only triggers once");
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits)
{
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

