
int inn=6;
int foul=0;
int winner=0;
int leda=5;
int ledb=4;
long currtime=0;
long del=1000;
long deltime;
int ingame=0;
int in1=3;
int in2=2;
int buzz=10;
int resetime=5000;

void setup(){
    Serial.begin(9600);
    pinMode(inn,OUTPUT);
    pinMode(in2,INPUT_PULLUP);
    pinMode(in1,INPUT_PULLUP);
    pinMode(leda,OUTPUT);
    pinMode(ledb,OUTPUT);
    pinMode(buzz,OUTPUT);
}

void initial();
void foulchecker();
void single();
void checkwinner();
void foulfun();
void reset();

void loop(){
    initial();
    if (ingame==1){
    foulchecker();
    checkwinner();
    }
    
}

void initial(){
    if (ingame==0 && digitalRead(in1)==0 && digitalRead(in2)==0) {
    delay(1000);      
    digitalWrite(inn,HIGH);
    delay(200);
    digitalWrite(inn,LOW);
    delay(500);
    digitalWrite(inn,HIGH);
    delay(200);
    digitalWrite(inn,LOW);
    delay(500);
    digitalWrite(inn,HIGH);
    ingame=1;
    currtime=millis();
        Serial.println("Curr time");
        Serial.println(currtime);
    deltime=currtime+del;
        Serial.println("Del time");
        Serial.println(deltime);
    }
}

void foulchecker(){
    
    if (winner==0 && millis()<deltime){
        Serial.println("Checking foul");
        if(digitalRead(in1)==1){
            winner=2;
            foul=1;
            Serial.println("Foul1");
            foulfun();
        }else if(digitalRead(in2)==1){
            winner=1;
            foul=1;
            Serial.println("Foul2");
            foulfun();
        }
        
     }
    
    
}

void single(){
      if (winner==1){
        Serial.println("1 is winner");
          digitalWrite(leda,HIGH);
      }else if(winner==2){
        Serial.println("2 is winner");
            digitalWrite(ledb,HIGH);
        }
    delay(resetime);
    reset();
}

void checkwinner(){
    if (foul==0 && millis()>deltime){
        digitalWrite(inn,LOW);
       if (digitalRead(in1)==1) {
            winner=1;
            single();
        }else if(foul==0 && digitalRead(in2)==1){
            winner=2;
            single();
            
        }
    }
}

void foulfun(){
    digitalWrite(buzz,HIGH);
    if (winner==1){
        digitalWrite(leda,HIGH);
        delay(200);
        digitalWrite(buzz,LOW);
        delay(resetime);
        reset();
    }else if (winner==2){
        digitalWrite(ledb,HIGH);
        delay(200);
        digitalWrite(buzz,LOW);
        delay(resetime);
        reset();
    }
    
}

void reset(){
    winner=0;
    ingame=0;
    foul=0;
    digitalWrite(leda,LOW);
    digitalWrite(ledb,LOW);
    digitalWrite(inn,LOW);
    digitalWrite(buzz,LOW);
}
