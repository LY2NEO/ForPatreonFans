bool kont_signala = 0;
bool tinkamas_signalas = 0;
unsigned int tx_skaitiklis = 0;
unsigned long laikas = 0;
unsigned int kontr_laikos = 0;
unsigned int rodom_laikos = 0;
const int meginiai = 1300;
int saugomi_meginiai[meginiai] = {};
int skaitiklis = 0;
int fonas = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(6,INPUT);
pinMode(4,INPUT);
pinMode(8,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
laikas = micros();
if(digitalRead(4)==0){
bool signalas = digitalRead(6);

if(kont_signala!=signalas and skaitiklis<=meginiai and tinkamas_signalas==0){
  rodom_laikos = laikas - kontr_laikos;
  if(signalas==1){rodom_laikos = rodom_laikos * -1;}
  saugomi_meginiai[skaitiklis] = rodom_laikos;
  skaitiklis++;
  kont_signala = signalas;
  //Serial.println(rodom_laikos);
  kontr_laikos = laikas;
  
  if(skaitiklis>=meginiai){
  
  for(int i = 0;i<meginiai;i++){
      int tmp = saugomi_meginiai[i];
      if(tmp<0){tmp = tmp * -1;}
      if(tmp>0 and tmp<100 ){
        fonas++;
      }
    }

    if(fonas<200){
    tinkamas_signalas = 1;
    Serial.print(fonas);
    Serial.println(F("= SIGNALAS ISSAUGOTAS"));
    }else{
    tinkamas_signalas = 0;
    fonas = 0;
    skaitiklis = 0;
     Serial.println(F("NETINKAMAS NUSKAITOMA IS NAUJO"));
    }
  }
}
}else{
rodom_laikos = laikas - kontr_laikos;
if(tx_skaitiklis==0){digitalWrite(8, LOW);}
      int tmp = saugomi_meginiai[tx_skaitiklis];
      if(tmp<0){tmp = tmp * -1;}
      if(tmp<rodom_laikos and tx_skaitiklis<=meginiai){
        if(saugomi_meginiai[tx_skaitiklis]>0){
        digitalWrite(8, LOW);
        }else{
        digitalWrite(8, HIGH);
        }
        //Serial.print(tx_skaitiklis);
        //Serial.print(F("=="));
        //Serial.println(saugomi_meginiai[tx_skaitiklis]);
        tx_skaitiklis++;
        kontr_laikos = laikas;
      }
      if(tx_skaitiklis>=meginiai){
         Serial.println(F("SIGANALAS ISSIUTAS"));
         tx_skaitiklis = 0;
         digitalWrite(8, LOW);
         delay(1000);
        }
      

}
}

