//#include <TM1638.h>

//->  TM1638 module(8, 7, 9);

int ledPins[] = { 
  40,41,42,43,44,45,46,47,48 };
int pinCount = 9;
int precision = 18;


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean affichage_speed;
boolean affichage_pneu;
boolean affichage_time;
int MillisStartBlink;
boolean blink_rpm;



struct Telemetrie
{
  String Gear;
  String Speed;
  String RPM;
  String RPM_Max;
  String TPneu_Av_G;
  String TPneu_Av_D;
  String TPneu_Ar_G;
  String TPneu_Ar_D;
  String CurrentTime;
  String LastTime;
};

typedef struct Telemetrie Telem; 
Telem iTelemetrie;

void setup() {

  Serial.begin(115200);
  //->module.setupDisplay(true, 1);
  //-> module.clearDisplay();  
  inputString.reserve(200);
  affichage_speed=true;
  for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);      
  }

  Coucou();
  digitalWrite(ledPins[0], HIGH);   
  digitalWrite(ledPins[pinCount-1], HIGH);   
    delay(1000);
  digitalWrite(ledPins[0], LOW);   
  digitalWrite(ledPins[pinCount-1], LOW); 

}

void loop() 
{
  // print the string when a newline arrives:
  if (stringComplete) {      

    ParsingBuffer(inputString); // on decoupe la chaine de caractere en valeurs uniques

    //->if (module.getButtons() == 0b00000001) // 1er bouton gauche affiche gear et speed
    //->{
    //->   affichage_speed=true; 
    //->   affichage_pneu=false;
    //->    affichage_time=false;
    //->  module.clearDisplay();
    //->  }
    /* else if (module.getButtons() == 0b00000010) // 2nd bouton gauche affiche temperatures
     {
     affichage_speed=false; 
     affichage_pneu=true;
     affichage_time=false;
     module.clearDisplay();  
     }
     
     else if (module.getButtons() == 0b000000100) // 3eme bouton gauche affiche temps
     {
     affichage_speed=false; 
     affichage_pneu=false;
     affichage_time=true;
     module.clearDisplay();      
     }*/

    Affichage_LCD();

    // clear the string:
    inputString = "";
    stringComplete = false;    

  }

}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 


    // char inChar = '5;5;5;5\n';
    // add it to the inputString:
    inputString += inChar;

    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;      
    } 
  }
}

void ParsingBuffer(String Str_Parse)
{
  //XX;XXX;XXXXX;XXXXX;XXX;XXX;XXX;XXX;XX:XX:XX;XX:XX:XX\n
  //Gear;Speed;Rpm;RpmMax;TPneuAvG;TPneuAvD;TPneuArG;TPneuArD;CurrentLap;LastLap\n

  int pos_n=0;

  //on supprime le \n en fin de chaine
  pos_n=Str_Parse.indexOf('\n');
  Str_Parse = Str_Parse.substring(0,pos_n);

  //Gear
  pos_n=Str_Parse.indexOf(';');
  String str_tmp = Str_Parse.substring(0,pos_n);

  if (str_tmp == "-1") {
    iTelemetrie.Gear = "R";
  }
  else if (str_tmp == "0") {
    iTelemetrie.Gear = "-";
  }
  else if (str_tmp == "-2") {
    iTelemetrie.Gear = "";
  }
  else {
    iTelemetrie.Gear = str_tmp;
  }    

  //On supprime les char de gear de la str de travail
  Str_Parse = Str_Parse.substring(pos_n+1,Str_Parse.length());

  //Speed
  pos_n=Str_Parse.indexOf(';');
  str_tmp = Str_Parse.substring(0,pos_n);
  iTelemetrie.Speed = str_tmp;

  //On supprime les char de gear de la str de travail
  Str_Parse = Str_Parse.substring(pos_n+1,Str_Parse.length());

  //RPM
  pos_n=Str_Parse.indexOf(';');
  str_tmp = Str_Parse.substring(0,pos_n);
  iTelemetrie.RPM = str_tmp;

  //On supprime les char de gear de la str de travail
  Str_Parse = Str_Parse.substring(pos_n+1,Str_Parse.length());

  //RPM_Max
  pos_n=Str_Parse.indexOf(';');
  str_tmp = Str_Parse.substring(0,pos_n);
  iTelemetrie.RPM_Max = str_tmp;

  //On supprime les char de gear de la str de travail
  Str_Parse = Str_Parse.substring(pos_n+1,Str_Parse.length());

  //Temp pneu av gauche
  pos_n=Str_Parse.indexOf(';');
  str_tmp = Str_Parse.substring(0,pos_n);
  iTelemetrie.TPneu_Av_G = str_tmp;

  //On supprime les char de gear de la str de travail
  Str_Parse = Str_Parse.substring(pos_n+1,Str_Parse.length());

  //Temp pneu av droit
  pos_n=Str_Parse.indexOf(';');
  str_tmp = Str_Parse.substring(0,pos_n);
  iTelemetrie.TPneu_Av_D = str_tmp;

  //On supprime les char de gear de la str de travail
  Str_Parse = Str_Parse.substring(pos_n+1,Str_Parse.length());

  //Temp pneu av droit
  pos_n=Str_Parse.indexOf(';');
  str_tmp = Str_Parse.substring(0,pos_n);
  iTelemetrie.TPneu_Ar_G = str_tmp;

  //On supprime les char de gear de la str de travail
  Str_Parse = Str_Parse.substring(pos_n+1,Str_Parse.length());

  //Temp pneu av droit
  pos_n=Str_Parse.indexOf(';');
  str_tmp = Str_Parse.substring(0,pos_n);
  iTelemetrie.TPneu_Ar_D = str_tmp;

  //On supprime les char de gear de la str de travail
  Str_Parse = Str_Parse.substring(pos_n+1,Str_Parse.length());

  //Current Time
  pos_n=Str_Parse.indexOf(';');
  str_tmp = Str_Parse.substring(0,pos_n);  
  iTelemetrie.CurrentTime= str_tmp;

  //On supprime les char de gear de la str de travail
  Str_Parse = Str_Parse.substring(pos_n+1,Str_Parse.length());

  //Last Time
  pos_n=Str_Parse.indexOf(';');
  str_tmp = Str_Parse.substring(0,pos_n);
  iTelemetrie.LastTime= str_tmp; 
}

void Coucou ()
{
  for (int thisPin = 0; thisPin < pinCount; thisPin++) { 
    digitalWrite(ledPins[thisPin], HIGH);   
    delay(30);                  
  } 

  for (int thisPin = 0; thisPin < pinCount; thisPin++) { 
    digitalWrite(ledPins[thisPin], LOW);   
    delay(20);                  
  } 
}

void Affichage_LCD ()
{  

  int NbLed;
  //Affichage en barre du RPM
  // Transformation string en int
  char carray_RPM[iTelemetrie.RPM.length() + 1]; //determine size of the array
  iTelemetrie.RPM.toCharArray(carray_RPM, sizeof(carray_RPM)); //put readStringinto an array
  int int_RPM = atoi(carray_RPM); //convert the array into an Integer

  char carray_RPM_Max[iTelemetrie.RPM_Max.length() + 1]; //determine size of the array
  iTelemetrie.RPM_Max.toCharArray(carray_RPM_Max, sizeof(carray_RPM_Max)); //put readStringinto an array
  int int_RPM_Max = atoi(carray_RPM_Max); //convert the array into an Integer

  if ((int_RPM > 0)) //&& (int_RPM_Max > int_RPM))
  {  
    float rapport;

    if (int_RPM > int_RPM_Max) { 
      rapport=1;
    }
    else
    {  
      rapport= ((float)int_RPM / int_RPM_Max); 
    }

    rapport = rapport/(0.95);
    NbLed = rapport*(pinCount+precision);

  }
  else NbLed=0;

  if (NbLed > precision) {
    // loop from the highest pin to the lowest:
    for (int thisPin = 0; thisPin < NbLed-precision; thisPin++) { 
      digitalWrite(ledPins[thisPin], HIGH);
    }

  }
  for (int thisPin = NbLed-precision; thisPin <= pinCount; thisPin++) { 
    digitalWrite(ledPins[thisPin], LOW);
  }


  if (NbLed - precision > pinCount) {
    if ((millis() - MillisStartBlink) > 50){
      if (blink_rpm== false) 
      {
        for (int thisPin = 0; thisPin < pinCount; thisPin++) { 
          digitalWrite(ledPins[thisPin], HIGH);     
        }
        blink_rpm= true;        
      }
      else
      {
        for (int thisPin = 0; thisPin < pinCount; thisPin++) { 
          digitalWrite(ledPins[thisPin], LOW);     
        }
        blink_rpm= false;
      }
      MillisStartBlink = millis();
    }
  }


}
