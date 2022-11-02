#define BLYNK_TEMPLATE_ID "TMPLswhElqSM"
#define BLYNK_DEVICE_NAME "WEATHER MONITOR"
#define BLYNK_AUTH_TOKEN "4ePCkpFQE2FZhjvu-Ufxb50IJdh0A-4g"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


char auth[] =  BLYNK_AUTH_TOKEN ; //Enter the Auth code which was send by Blink
char ssid[] = "Dialog 4G 025";  //Enter your WIFI Name
char pass[] = "jangu1234";  //Enter your WIFI Password
String show="";
WidgetLCD lcd(V1);
DHT dht(D3, DHT11); //(sensor pin,sensor type)
BlynkTimer timer;

void weather() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int r = analogRead(D4);
  bool eventTrigger=false;
  const int ldrpin = A0;
pinMode(ldrpin,INPUT);
int rawData = analogRead(ldrpin);
  r = map(r, 0, 1023, 100, 0);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, t);  //V0 is for Temperature
  Blynk.virtualWrite(V6, h);  //V1 is for Humidity
  Blynk.virtualWrite(V4, r);  //V2 is for Rainfall
  lcd.clear();
lcd.print(0,0,"Temperature:"+String(t));
lcd.print(0,1,"Humidity:"+String(h));


//  Blynk.virtualWrite(V3,l);
if(rawData<900 && eventTrigger==false){
  eventTrigger=true;
  if(r>2  ){
  Blynk.logEvent("rain",String("oopps! its raining out their don't Forget to get umbrella with you"));
   Blynk.logEvent("temperature",String("it is a bright outside,Temperature about:")+t);
    Blynk.logEvent("humidity",String("Humidity about:")+h);
  
   Serial.println(String("oopps! its raining out their don't Forget to get umbrella with you"));
   Serial.println(String("Surrounding is bright outside,Temperature about:")+t);
     Serial.println(String("Humidity about:")+h);
  delay(3000);
}
else{
  //--------temperature code-------
  
  if(t<35){
 // eventTrigger=true;
  Blynk.logEvent("temperature",String("Pretty Bright day to play out Sir,\n I like to say it's a pretty good day to play any sport you may like.\nTemperature:")+t);
  Serial.println(String("Pretty bright day to play out Sir,\n I like to say it's a pretty good day to play any sport you may like.\nTemperature:")+t);        //   -------------serial mointer
  delay(3000);

  
//----------humidity code------------

  if(h<60){
  Blynk.logEvent("humidity",String("with humidity about:")+h);
    Serial.println(String("with humidity about:")+h);              //     ---------serial moniter
     delay(3000);
  }
  else{
     Blynk.logEvent("humidity",String("humidity is rising:")+h);
    Serial.println(String(" humidity is rising:")+h);
  delay(3000);
  }
  }
  else if(t >= 35 ){
  //eventTrigger=true;
  Blynk.logEvent("temperature",t+String("Sir, for your concern please do carry a water bottle will going out it's really hot."));
  Serial.println("Sir, for your concern please do carry a water bottle will going out it's really hot.");
  delay(3000);
  //----------humidity code------------

  if(h<60){
  Blynk.logEvent("humidity",String(" it is a pretty bright day sir, with humidity about:")+h);
    Serial.println(String(" it is a pretty bright day sir, with humidity about:")+h);
     delay(3000);
  }
  else{
     Blynk.logEvent("humidity",String("its Quite dark out Sir,humidity is rising:")+h);
    Serial.println(String("its Quite dark out Sir, humidity is rising:")+h);
  delay(3000);
  }
  }
  

}}


//----------------------------------------night------------------------------------------------
else if(rawData>900 && eventTrigger==false ){
eventTrigger=true;
  if(r>2  ){
    
  Blynk.logEvent("rain",String("oopps! its raining out their don't Forget to get umbrella with you"));
Blynk.logEvent("temperature",String("Surrounding is dark outside,Temperature about:")+t);
    Blynk.logEvent("humidity",String("Humidity about:")+h);
  
   Serial.println(String("oopps! its raining out their don't Forget to get umbrella with you"));
   Serial.println(String("Surrounding is dark outside,Temperature about:")+t);
     Serial.println(String("Humidity about:")+h);
  delay(2000);
  
}
else{
 

  //--------temperature code-------
  eventTrigger=true;
  if(t<35){
 // eventTrigger=true;
  Blynk.logEvent("temperature",t+String(""));
  Serial.println(String("Temperature: ")+t);
  delay(3000);
  
  
//----------humidity code------------

  if(h<60){
  Blynk.logEvent("humidity",String("its Quite dark out Sir,Do carry a torch with you \n humidity is about:")+h);
   Serial.println(String("its Quite dark out Sir,Do carry a torch with you \n humidity is about:")+h);
  delay(3000);
  }
  else{
     Blynk.logEvent("humidity",String("its Quite dark out Sir,humidity is rising:")+h);
    Serial.println(String("its Quite dark out Sir, humidity is rising:")+h);
  delay(3000);
  }
  }
  else if(t >= 35 ){
  //eventTrigger=true;
  Blynk.logEvent("temperature",t+String("Sir, for your concern please do carry a water bottle will going out it's really hot."));
  Serial.println("Sir, for your concern please do carry a water bottle will going out it's really hot.");
  delay(3000);
  //----------humidity code------------

  if(h<60){
  Blynk.logEvent("humidity",String("its Quite dark out Sir,Do carry a torch with you \n humidity is about:")+h);
   Serial.println(String("its Quite dark out Sir,Do carry a torch with you \n humidity is about:")+h);
  delay(3000);
  }
  else{
     Blynk.logEvent("humidity",String("its Quite dark out Sir,humidity is rising:")+h);
    Serial.println(String("its Quite dark out Sir, humidity is rising:")+h);
  delay(3000);
  }
  }
   eventTrigger=true;
  Blynk.logEvent("rain",String("hmm! don't try your luck it might rain carry a umbrella"));
  Serial.println(String("hmm! don't try your luck it might rain carry a umbrella"));
  delay(3000);

}

}
  
  if (rawData<900) {
    WidgetLED led1(V3);
    led1.on();

   

 }
 else{
    WidgetLED led1(V3);
    led1.off();

 }
}

void setup() {
  Serial.begin(9600); // See the connection status in Serial Monitor
 
  
  Blynk.begin(auth," ONE","12345@12345");
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(10L, weather);
}

void loop() {
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
