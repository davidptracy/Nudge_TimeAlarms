/*SET TIME FROM LINUX CLOCK ON ARDUINO YUN
DAVID TRACY || github.com/davidptracy */

#include <Process.h>
#include <Time.h>
#include <TimeAlarms.h>


String curDateTime = "";

void setup() {
  Serial.begin(9600); 

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

  // THIS IS CASTING THE SERIAL READ FROM THE SHELL COMMAND INTO A STRING THAT WE CAN PARSE
  while (checkTime.available() > 0) {
    char c = checkTime.read();
    curDateTime.concat(c);
  }
  
  //THIS IS SETTING UP THE RULES TO PARSE THE STRING

  int firstDash = curDateTime.indexOf("-");
  int secondDash = curDateTime.lastIndexOf("-");
  int indexOfT = curDateTime.indexOf("T");
  int firstColon = curDateTime.indexOf(":");
  int secondColon = curDateTime.lastIndexOf(":");
  
  //THIS IS SPLITTING THE curDateTime STRING INTO DIGESTABLE CHUNKS AND CONVERTING THEM TO INTS

  int curYear = curDateTime.substring(0, firstDash).toInt();
  int curMonth = curDateTime.substring(firstDash + 1, secondDash).toInt();
  int curDay = curDateTime.substring(secondDash + 1, indexOfT).toInt();
  int curHour = curDateTime.substring(indexOfT + 1, firstColon).toInt();
  int curMin = curDateTime.substring(firstColon + 1, secondColon).toInt();
  int curSec = curDateTime.substring(secondColon + 1, curDateTime.length() - 1).toInt();

  //PRINT THE INTS FOR DEBUGGING 
  Serial.println(curYear);
  Serial.println(curMonth);
  Serial.println(curDay);
  Serial.println(curHour);
  Serial.println(curMin);
  Serial.println(curSec);
  
  //THIS IS USING THE INTS TO SET THE TIME FOR USE WITH ALARMS
  setTime(curHour, curMin, curSec, curDay, curMonth, curYear);

  if (timeStatus() != timeSet)
    Serial.println("Yun time is not synced");
  else
    Serial.println("Yun time is synced");

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalClockDisplay();
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

