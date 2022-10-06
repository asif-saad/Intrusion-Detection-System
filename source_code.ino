#include <LiquidCrystal.h>

#include <Key.h>
#include <Keypad.h>

// setting up pins
const int buzzer = 23;
const int room1 = 7;
const int room2 = 6;
const int room3 = 5;

// setting authentication password
String password = "1234";

// number of rows and columns in keypad
const byte rows = 4;
const byte cols = 4;

// keymap for keypad
char keyMap[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// keypad pin mapping -> 1:22, 2:24, 3:26, 4:28, 5:30, 6:32, 7:34, 8:36

// setting up pins for rows and columns in keypad
byte rowPins[rows] = {36, 34, 32, 30};
byte colPins[cols] = {28, 26, 24, 22};

// creating a keypad type object
Keypad myKeypad = Keypad(makeKeymap(keyMap), rowPins, colPins, rows, cols);
const int rs = 42, en = 44, d4 = 46, d5 = 48, d6 = 50, d7 = 52;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);
  pinMode(room1, INPUT);
  pinMode(room2, INPUT);
  pinMode(room3, INPUT);
  pinMode(buzzer, OUTPUT);
  //pinMode(trigger, OUTPUT);
  //pinMode(echo, INPUT);
  //pinMode(buzzer, OUTPUT);
}

void loop() {
  lcd.home();
  lcd.print(" ***** I.D.S ***** ");
  lcd.setCursor(0, 1);
  lcd.print("System Deactivated");
  lcd.setCursor(0, 2);
  lcd.print("A -> Activate System");
  lcd.setCursor(0, 3);
  lcd.print("B -> Change Password");
  char key = myKeypad.waitForKey();
  tone(buzzer, 1000);
  delay(100);
  noTone(buzzer);
  if (key == 'A') {
    long k = 0;
    lcd.clear();
    lcd.home();
    lcd.print(" ***** I.D.S ***** ");
    lcd.setCursor(0, 1);
    lcd.print("System Deactivated");
    lcd.setCursor(0, 2);
    lcd.print("Password: ");
    lcd.setCursor(11, 2);
    String temp = "";
    // taking character input one by one
    while (k < 4) {
      char key2 = myKeypad.waitForKey();
      tone(buzzer, 1000);
      delay(100);
      noTone(buzzer);
      Serial.println(key2);
      lcd.print("*");
      temp = temp + key2;
      k++;
    }
    // if right password is entered, system will activate; otherwise it will ask for password again
    if (temp == password) {
      lcd.setCursor(0, 3);
      lcd.print("Password OK");
      delay(1000);
      lcd.clear();
      lcd.home();
      lcd.print(" ***** I.D.S ***** ");
      lcd.setCursor(0, 1);
      lcd.print("System Activates in ");
      long cnt = 9;
      while (cnt > 0) {
        lcd.setCursor(9, 2);
        lcd.print(cnt);
        lcd.print(" s");
        tone(buzzer, 100);
        delay(200);
        noTone(buzzer);
        delay(800);
        cnt--;
      }
      lcd.clear();
      lcd.home();
      lcd.print(" ***** I.D.S ***** ");
      lcd.setCursor(0, 1);
      lcd.print("System Activated");
      lcd.setCursor(0, 2);
      lcd.print("A->Deactivate System");
      systemActivated(); // activation starts here
    }
    else {
      lcd.setCursor(0, 3);
      lcd.print("Password Wrong");
      delay(1000);
      lcd.clear();
      lcd.home();
    }
  }
  else if (key == 'B') {
    lcd.clear();
    lcd.home();
    lcd.print(" ***** I.D.S ***** ");
    lcd.setCursor(0, 1);
    lcd.print("System Deactivated");
    lcd.setCursor(0, 2);
    lcd.print("Old Password: ");
    lcd.setCursor(15, 2);
    String temp = "";
    // taking character one by one
    long k2 = 0;
    while (k2 < 4) {
      char key2 = myKeypad.waitForKey();
      tone(buzzer, 1000);
      delay(100);
      noTone(buzzer);
      Serial.println(key2);
      lcd.print("*");
      temp = temp + key2;
      k2++;
    }
    if (temp == password) {
      lcd.setCursor(0, 3);
      lcd.print("Password ok");
      delay(1000);
      lcd.clear();
      lcd.home();
      lcd.print(" ***** I.D.S ***** ");
      lcd.setCursor(0, 1);
      lcd.print("System Deactivated");
      lcd.setCursor(0, 2);
      lcd.print("New Password: ");
      lcd.setCursor(15, 2);
      String temp2 = "";
      // taking character one by one
      long k3 = 0;
      while (k3 < 4) {
        char key2 = myKeypad.waitForKey();
        tone(buzzer, 1000);
        delay(100);
        noTone(buzzer);
        lcd.print("*");
        temp2 = temp2 + key2;
        k3++;
      }
      password = temp2;
      lcd.setCursor(0, 3);
      lcd.print("Password Changed");
      delay(2000);
    }
    else {
      lcd.setCursor(0, 3);
      lcd.print("Password wrong");
      delay(2000);
    }
  }
}

void alarmActivated(int roomNumber)
{
  //Serial.println(digitalRead(room1));
  lcd.clear();
  lcd.home();
  lcd.print(" ***** I.D.S ***** ");
  lcd.setCursor(0, 1);
  lcd.print("Intrusion detected!!");
  lcd.setCursor(0, 2);
  if (roomNumber == 1) lcd.print("## Room1 breached ##");
  else if (roomNumber == 2) lcd.print("## Room2 breached ##");
  lcd.setCursor(0, 3);
  lcd.print("A -> Stop Alarm");
  digitalWrite(buzzer, HIGH);
  char key5 = myKeypad.waitForKey();
  if (key5 == 'A') {
    lcd.clear();
    lcd.print(" ***** I.D.S ***** ");
    lcd.setCursor(0, 1);
    lcd.print("Intrusion detected!!");
    lcd.setCursor(0, 2);
    Serial.println(roomNumber);
    if (roomNumber == 1) lcd.print("## Room1 breached ##");
    else if (roomNumber == 2) lcd.print("## Room2 breached ##");
    lcd.setCursor(0, 3);
    lcd.print("Password: ");
    int k5 = 0;
    String temp5 = "";
    while (k5 < 4) {
      char key6 = myKeypad.waitForKey();
      temp5 = temp5 + key6;
      lcd.print("*");
      k5++;
    }
    if (temp5 == password) {
      lcd.setCursor(0, 3);
      digitalWrite(buzzer, LOW);
      lcd.print("   Password ok   ");
      delay(2000);
    }
    else {
      lcd.setCursor(0, 3);
      lcd.print(" Password Wrong ");
      delay(1000);
      alarmActivated(roomNumber);
    }
  }
  else {
    alarmActivated(roomNumber);
  }
}

void systemActivated()
{
  int room1status = digitalRead(room1);
  int room2status = digitalRead(room2);
  Serial.println(room1status + room2status);
  if (room1status == 1) {
    alarmActivated(1);
    return;
  }
  else if (room2status == 1) {
    alarmActivated(2);
    return;
  }
  char key3 = myKeypad.getKey();
  bool flag = false;
  if (key3 == 'A') {
    tone(buzzer, 1000);
    delay(100);
    noTone(buzzer);
    long k4 = 0;
    lcd.clear();
    lcd.home();
    lcd.print(" ***** I.D.S ***** ");
    lcd.setCursor(0, 1);
    lcd.print("System Activated");
    lcd.setCursor(0, 2);
    lcd.print("Password: ");
    lcd.setCursor(11, 2);
    String temp = "";
    // taking character one by one
    while (k4 < 4) {
      char key4 = myKeypad.waitForKey();
      tone(buzzer, 1000);
      delay(100);
      noTone(buzzer);
      lcd.print("*");
      temp = temp + key4;
      k4++;
    }
    if (temp == password) {
      lcd.setCursor(0, 3);
      lcd.print("Password ok");
      delay(2000);
      flag = true;
    }
    else {
      lcd.setCursor(0, 3);
      lcd.print("Password Wrong");
      delay(2000);
      lcd.clear();
      lcd.home();
      lcd.print(" ***** I.D.S ***** ");
      lcd.setCursor(0, 1);
      lcd.print("System Activated");
      lcd.setCursor(0, 2);
      lcd.print("A->Deactivate System");
      lcd.clear();
      lcd.home();
      lcd.print(" ***** I.D.S ***** ");
      lcd.setCursor(0, 1);
      lcd.print("System Activated");
      lcd.setCursor(0, 2);
      lcd.print("A->Deactivate System");
      systemActivated();
    }
  }
  delay(1000);
  if (!flag) systemActivated();
  else loop();
}
