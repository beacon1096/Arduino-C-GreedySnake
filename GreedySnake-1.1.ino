#include <LedControl.h>
const int sSize=425;
int speedSnake=333;
int biteItselfTime=0;
const bool debugMode=false;
bool dieAtBegin=false;
LedControl lc=LedControl(12,11,10,5);
int tail=0,head=2;
int snakeLength=3;
//bool screenCleared=false;
short gameStatement=1;
int i,j;
int x,y,k;
int foodx,foody;
bool foodEaten=false;
bool restart=false;
bool ledLighted[8][8];
struct pos{
  int x,y;
  };
struct pos s[sSize];
char dire='W';
int tx,ty;
void setup() {
  lc.setIntensity(0,1);
  lc.shutdown(0,false);
  lc.clearDisplay(0);
  s[0].x=4;s[0].y=4;
  s[1].x=4;s[1].y=5;
  s[2].x=5;s[2].y=4;
  tail=0;head=2;foodEaten=false;restart=false;gameStatement=1;dire='W';
  if(debugMode==true){
    Serial.begin(9600);
    //speedSnake=Serial.read();
    if(dieAtBegin==true)gameStatement=2;
  }
}
void readJoyStick(){
  x=analogRead(A0);
  y=analogRead(A1);
  if(x<50 && dire!='A') dire='D';
  if(x>950 && dire!='D') dire='A';
  if(y<50 && dire!='W') dire='S';
  if(y>950 && dire!='S') dire='W';
  if(debugMode==true){
    Serial.print("x=");Serial.print(x);Serial.print("y=");Serial.println(y);
  }
}
void genFood(){
  int flag;
  do
  {
    flag=0;
    foodx=analogRead(A0)%8;
    foody=analogRead(A1)%8;
   for(i=head;i>=tail;i--){
     if(s[i].x==foodx && s[i].y==foody){
        flag=1;break;
      }
   }
  }while(flag==1);
  foodEaten=false;
}
void getFood(){
  if(s[head].x==foodx &&s[head].y==foody){
    //head++;s[head].x=foodx;s[head].y=foody;
    tail--;foodEaten=true;snakeLength++;
  }
}
void showX(){
  //if(screenCleared==false)
    lc.clearDisplay(0);
  lc.setLed(0,0,0,true);
  lc.setLed(0,1,1,true);
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,3,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,6,6,true);
  lc.setLed(0,7,7,true);
  lc.setLed(0,0,7,true);
  lc.setLed(0,1,6,true);
  lc.setLed(0,2,5,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,4,3,true);
  lc.setLed(0,5,2,true);
  lc.setLed(0,6,1,true);
  lc.setLed(0,7,0,true);
  //screenCleared=true;
  //if(screenCleared==true)
  restartGame();
}
void showO(){
  lc.clearDisplay(0);
  lc.setLed(0,0,2,true);
  lc.setLed(0,0,3,true);
  lc.setLed(0,0,4,true);
  lc.setLed(0,0,5,true);
  lc.setLed(0,2,0,true);
  lc.setLed(0,3,0,true);
  lc.setLed(0,4,0,true);
  lc.setLed(0,5,0,true);
  lc.setLed(0,7,2,true);
  lc.setLed(0,7,3,true);
  lc.setLed(0,7,4,true);
  lc.setLed(0,7,5,true);
  lc.setLed(0,2,7,true);
  lc.setLed(0,3,7,true);
  lc.setLed(0,4,7,true);
  lc.setLed(0,5,7,true);
  lc.setLed(0,1,1,true);
  lc.setLed(0,1,6,true);
  lc.setLed(0,6,1,true);
  lc.setLed(0,6,6,true);
  
}
void recharge(){
  lc.clearDisplay(0);
  lc.setLed(0,0,0,true);
  lc.setLed(0,1,0,true);
  lc.setLed(0,2,0,true);
  lc.setLed(0,3,0,true);
  lc.setLed(0,4,0,true);
  lc.setLed(0,5,0,true);
  lc.setLed(0,6,0,true);
  lc.setLed(0,7,0,true);
  
  lc.setLed(0,0,7,true);
  lc.setLed(0,1,7,true);
  lc.setLed(0,2,7,true);
  lc.setLed(0,3,7,true);
  lc.setLed(0,4,7,true);
  lc.setLed(0,5,7,true);
  lc.setLed(0,6,7,true);
  lc.setLed(0,7,7,true);
  int tailN=0,cuProcess=tail;
  for(tailN=0;cuProcess<=sSize;tailN++)
  {
    s[tailN].x=s[cuProcess].x;
    s[tailN].y=s[cuProcess].y;
    cuProcess++;
   }
   tail=0;head=snakeLength-1;
   gameStatement=1;pauseGame();
}
void restartGame(){
  while(restart==false){
    k=analogRead(A2);
    if(k<1000)restart=true;delay(1000);
  }
  setup();
  gameStatement=1;
  }
void pauseGame(){
  delay(250);
  gameStatement=5;
  while(gameStatement==5){
    k=analogRead(A2);
    if(k<1000)gameStatement=1;delay(1000);
  }
}  
void loop() {
  if(gameStatement==1){
    getFood();
    if(foodEaten==true)genFood();
    readJoyStick();
    if(dire=='D'){tx=s[head].x;ty=s[head].y+1;}
    if(dire=='A'){tx=s[head].x;ty=s[head].y-1;}
    if(dire=='W'){tx=s[head].x-1;ty=s[head].y;}
    if(dire=='S'){tx=s[head].x+1;ty=s[head].y;}
    k=analogRead(A2);if(k<1000)gameStatement=4;
    head++;
    s[head].x=tx;s[head].y=ty;
    tail++;
    lc.clearDisplay(0);
    lc.shutdown(0,true);lc.shutdown(0,false);
    for(i=tail;i<=head;i++){
     if(debugMode==true){
       if(s[i].x>=8)s[i].x=s[i].x-8;
       if(s[i].y>=8)s[i].y=s[i].y-8;
       if(s[i].x<0)s[i].x=s[i].x+8;
       if(s[i].y<0)s[i].y=s[i].y+8; 
      }
     if(debugMode==false)
      if(s[i].x>=8 || s[i].y>=8 || s[i].x<=-1 || s[i].y<=-1)gameStatement=2;
     lc.setLed(0,s[i].x,s[i].y,true);
    }
    if(debugMode==false)
    {
      biteItselfTime=0;
      for(i=tail;i<=head;i++){
        for(j=i+1;j<=head;j++){
          if(s[i].x==s[j].x && s[i].y==s[j].y) biteItselfTime++;
          if(biteItselfTime>=1)gameStatement=2;
        }
     }
    }
    lc.setLed(0,foodx,foody,true);
    if(snakeLength==64)gameStatement=3;
    delay(speedSnake);Serial.print("x=");Serial.print(x);Serial.print("y=");Serial.println(y);
  }
  if(gameStatement==2)showX();
  else if(gameStatement==3)showO();
  if(gameStatement==4)pauseGame();
  if(head==sSize)gameStatement=6;
  if(gameStatement==6)recharge();
}
