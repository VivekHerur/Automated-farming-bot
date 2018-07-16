#include <SoftwareSerial.h>
#define WIFI_SSID        "Navya" 
#define WIFI_PASS        "Navyaisha" // Wifi Password
#define SERVER_IP     "192.168.0.135" // IP of the target server.
#define TIMEOUT     5000 //Timeout for the serial communication
#define CONTINUE    false
#define HALT        true
#define NO_OF_PARAMETERS 1 //No of parameters sending to the server.

int ok = 0;
SoftwareSerial esp8266SerialPort(10, 11); // RX, TX
String response1;
char res[300];
int cnt = 0,temp;
void exception(String msg){ //Exception occured. Print msg and stops.
  Serial.println(msg);
  Serial.println("HALT");
  while(true){
   readResponseData("");
   delay(60000);
  }
}
boolean readResponseData(String keyword){ //Receive data from the serial port. Returns true if keyword matches.
  String response,response1;
  long deadline = millis() + TIMEOUT;
  while(millis() < deadline){
    if (esp8266SerialPort.available()){
      char ch = esp8266SerialPort.read(); // Read one character from serial port and append to a string.
      response+=ch;
      if(keyword!=""){
        if(response.indexOf(keyword)>0){ //Searched keyword found.
          Serial.println(response);
          
          return true;
        }
      }
    }
  }
  Serial.println(response);
  return false;
}



/*boolean readResponseData1(String keyword){ //Receive data from the serial port. Returns true if keyword matches.
  
  long deadline = millis() + TIMEOUT;
  while(millis() < deadline){
    if (esp8266SerialPort.available()){
      char ch = esp8266SerialPort.read(); // Read one character from serial port and append to a string.
      response1+=ch; 
      res[cnt++] = ch;   
      if(keyword!=""){
        if(response1.indexOf(keyword)>0){ //Searched keyword found.
          return true;
        }
      }
    }
  }
  Serial.println(response1);
  return false;
}*/

boolean sendCommand(String command, String acknowledgement, boolean stopOnError)
{
  esp8266SerialPort.println(command);
  if (!readResponseData(acknowledgement)) 
    if (stopOnError)
      exception(command+" Failed to execute.");
    else
      return false;            // Let the caller handle it.
  return true;                   // ack blank or ack found
}



boolean initializeESP8266Module(){
  esp8266SerialPort.begin(9600);  
  esp8266SerialPort.setTimeout(TIMEOUT);
  delay(2000);

  //sendCommand("AT+RST", "ready", HALT);    // Reset & test if the module is ready  
  sendCommand("AT+GMR", "OK", CONTINUE);   // Retrieves the firmware ID (version number) of the module. 
  sendCommand("AT+CWMODE?","OK", CONTINUE);// Get module access mode. 
  sendCommand("AT+CWMODE=1","OK", HALT);    // Station mode
  sendCommand("AT+CIPMUX=1","OK", HALT);    // Allow multiple connections (we'll only use the first).

  String cmd = "AT+CWJAP=\""; cmd += WIFI_SSID; cmd += "\",\""; cmd += WIFI_PASS; cmd += "\"";
  for(int counter=0;counter<5;counter++){
    if (sendCommand(cmd, "OK", CONTINUE)){ // Join Access Point
      Serial.println("Connected to WiFi.");
      ok = 1;
      break;
    }else if(counter==4)
      exception("Connection to Wi-Fi failed. Please Check");
  }
  
  delay(5000);

  sendCommand("AT+CWSAP=?", "OK", CONTINUE); // Test connection
  sendCommand("AT+CIFSR","OK", HALT);         // Echo IP address. (Firmware bug - should return "OK".)
}

void setup()  
{
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  Serial.begin(9600);
  //Serial.println("ESP8266 Demo");
  initializeESP8266Module();
  Serial.println("Module is ready.");
}

void loop() 
{
  if(ok==1)
  {
  int sensorValue = analogRead(A0);
  Serial.println(900);
  String stringsensorValue = String(sensorValue);
 
          digitalWrite(8,LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
      delay(30000);
       digitalWrite(8,HIGH);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
      delay(30000);
      
      SendToServer("900");
      
  

  }
}


void SendToServer(String stringsensorValue)
{
   String cmd = "AT+CIPSTART=0,\"TCP\",\""; cmd += SERVER_IP; cmd += "\",80"; //Start a TCP connection.  to server SERVER_IP on port 80
  if (!sendCommand(cmd, "OK", CONTINUE)) 
    return;
  delay(2000);

 // if (!sendCommand("AT+CIPSTATUS", "OK", CONTINUE))// Check for TCP Connection status.
   // return;
    
  String  tag[NO_OF_PARAMETERS]={"Moisture"}; //Tags for the parameters
  String data[NO_OF_PARAMETERS]={stringsensorValue}; //Values for the parameters
  
  cmd = "GET /esp/Modify.php?";//Path to the target server file.
  for(int count=0;count<NO_OF_PARAMETERS;count++){
    if(count!=0)
      cmd+="&";
    cmd+=tag[count];
    cmd+="="+data[count];
  }
  Serial.println(cmd);
  cmd+=" HTTP/1.1\r\nHost: "; cmd += SERVER_IP; cmd += ":80\r\n\r\n";
  if (!sendCommand("AT+CIPSEND=0,"+String(cmd.length()), ">", CONTINUE)){
    sendCommand("AT+CIPCLOSE", "", CONTINUE);
    Serial.println("Connection timeout.");
    return;
  }
  
  sendCommand(cmd, "OK", CONTINUE);// Send data to server.
  //readResponseData1("");// Read response data received from server.
  
  /*char sem,sec;
  char sub[8];
  int i = cnt;
 for(i=0;i<cnt-3;i++)
 {
   if(res[i] == 'S' && res[i+1] == 'e' && res[i+2] == 'm')
   {
      //Serial.print(res[i+3]);
      //Serial.print(res[i+4]);
      sem=res[i+4];
      sec=res[i+9];
      sub[0] = res[i+14];
      sub[1] = res[i+15];
      sub[2] = res[i+16];
      sub[3] = res[i+17];
      sub[4] = res[i+18];
      sub[5] = res[i+19];
      if(res[i+20]!='!')
      {
        sub[6] = res[i+20];
        sub[7] = '\0';
      }
      else
        sub[6] ='\0';
      Serial.print(sem);
      Serial.print(sec);
      Serial.print(sub);
      //i = i+14;
      
   }
   
 }*/
 /*int m=0;
 for(int j=i;res[i]!='!';j++)
 {
  sub[m++] = res[j];
 }/*
 Serial.print(sub);












   /*String  tag[NO_OF_PARAMETERS1]={"id"}; //Tags for the parameters
  String data[NO_OF_PARAMETERS1]={"1CS09"}; //Values for the parameters
  
  cmd = "GET /esp/index.php?";//Path to the target server file.
  for(int count=0;count<NO_OF_PARAMETERS1;count++){
    if(count!=0)
      cmd+="&";
    cmd+=tag[count];
    cmd+="="+data[count];
  }
  Serial.println(cmd);
  cmd+=" HTTP/1.1\r\nHost: "; cmd += SERVER_IP; cmd += ":80\r\n\r\n";
  if (!sendCommand("AT+CIPSEND=0,"+String(cmd.length()), ">", CONTINUE)){
    sendCommand("AT+CIPCLOSE", "", CONTINUE);
    Serial.println("Connection timeout.");
    return;
  }
  
  sendCommand(cmd, "OK", CONTINUE);// Send data to server.
  readResponseData1("");// Read response data received from server.
  */
  
  /*Serial.print(res);
  cnt = temp;
  char tempc = res[cnt];
  Serial.print(tempc);
  Serial.print(tempc);
  Serial.print(tempc);*/
  delay(2000);
  
  
 //exception("ONCE ONLY");
}


