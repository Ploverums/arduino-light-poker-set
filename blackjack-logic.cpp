// ssd1306 - Version: Latest 
#include <font6x8.h>
#include <nano_engine.h>
#include <nano_gfx.h>
#include <nano_gfx_types.h>
#include <sprite_pool.h>
#include <ssd1306.h>
#include <ssd1306_16bit.h>
#include <ssd1306_1bit.h>
#include <ssd1306_8bit.h>
#include <ssd1306_console.h>
#include <ssd1306_fonts.h>
#include <ssd1306_generic.h>
#include <ssd1306_uart.h>

// Adafruit GFX Library - Version: Latest 
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

// ArduinoGraphics - Version: Latest 
#include <ArduinoGraphics.h>

/*
SET UP FOR BLACKJACK: ADJUST FOR POKER
*/
int total1 = 0;
int total2 = 0;
int total3 = 0;
int total4 = 0;
int currentPlayerTotal = 0;
int currentPlayer = 1;
String suits[4] = {" Clubs", " Diamonds", " Hearts", " Spades"};
String cards[4][13] = {
  {"1" + suits[0], "2" + suits[0], "3" + suits[0], "4" + suits[0], "5" + suits[0], "6" + suits[0], "7" + suits[0], "8" + suits[0], "9" + suits[0], "10" + suits[0], "11" + suits[0], "12" + suits[0], "13" + suits[0]},
  {"1" + suits[1], "2" + suits[1], "3" + suits[1], "4" + suits[1], "5" + suits[1], "6" + suits[1], "7" + suits[1], "8" + suits[1], "9" + suits[1], "11" + suits[1], "11" + suits[1], "12" + suits[1], "13" + suits[1]},
  {"1" + suits[2], "2" + suits[2], "3" + suits[2], "4" + suits[2], "5" + suits[2], "6" + suits[2], "7" + suits[2], "8" + suits[2], "9" + suits[2], "12" + suits[2], "11" + suits[2], "12" + suits[2], "13" + suits[2]},
  {"1" + suits[3], "2" + suits[3], "3" + suits[3], "4" + suits[3], "5" + suits[3], "6" + suits[3], "7" + suits[3], "8" + suits[3], "9" + suits[3], "13" + suits[3], "11" + suits[3], "12" + suits[3], "13" + suits[3]}
};
int checker[4][13] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0}
};
int drawCard(){
  bool badDraw = true;
  while(badDraw == true){
      int suitval = 0 + (rand() % static_cast<int>(3 - 0 + 1));
int cardval = 0 + (rand() % static_cast<int>(12 - 0 + 1));
if(checker[suitval][cardval] == 0){
Serial.println(cards[suitval][cardval]);
checker[suitval][cardval] = 1;
badDraw = false;
if(cardval > 9){
  return 10;
}
else if(cardval> 0){
  return cardval += 1;
}
else{
  return 21;
}
}
  continue;
}
}
int turn = 0;
const int hitButtonPin = 2;
int hitButtonState = 0;
const int standButtonPin = 3;
int standButtonState = 0;
void setup() {
  srand(analogRead(0));
  pinMode(hitButtonPin, INPUT);
  Serial.begin(9600);
  for(int x=1; x<=4; x++){
  int playertotal = drawTwo(x);
  Serial.print("PLAYER ");
  Serial.print(x);
  Serial.print(" TOTAL:");
  Serial.println(playertotal);
  if(x == 1){
  total1 = playertotal;
  }
  if(x == 2){
  total2 = playertotal;
  }
  if(x == 3){
  total3 = playertotal;
  }
  if(x == 4){
  total4 = playertotal;
  }
   Serial.println("-------------------------------------");
  }
}
int standButtonPressed = 0;
int hitButtonPressed = 0;
bool inPlay = false;
void loop(){
if(currentPlayer == 1 && inPlay == false){
  currentPlayerTotal = total1;
}
if(currentPlayer == 2 && inPlay == false){
  currentPlayerTotal = total2;
}
if(currentPlayer == 3 && inPlay == false){
  currentPlayerTotal = total3;
}
if(currentPlayer == 4 && inPlay == false){
  currentPlayerTotal = total4;
}
if(currentPlayer == 1 && inPlay == true){
  total1  = currentPlayerTotal;
}
if(currentPlayer == 2 && inPlay == true){
  total2  = currentPlayerTotal;
}
if(currentPlayer == 3 && inPlay == true){
  total3  = currentPlayerTotal;
}
if(currentPlayer == 4 && inPlay == true){
  total4  = currentPlayerTotal;
}
hitButtonState = digitalRead(hitButtonPin);
if(hitButtonState == HIGH && hitButtonPressed == 0){
  hitButtonPressed = 1; 
  int nTotal = hit(currentPlayerTotal);
  currentPlayerTotal = nTotal;
  inPlay = true;
}
if(hitButtonState == LOW && hitButtonPressed == 1){
  hitButtonPressed = 0;
}
standButtonState = digitalRead(standButtonPin);
if(standButtonState == HIGH && standButtonPressed == 0){
  standButtonPressed = 1; 
  stand(currentPlayerTotal);
}
if(standButtonState == LOW && standButtonPressed == 1){
  standButtonPressed = 0;
}


bust(currentPlayerTotal);

}

int drawTwo(int player){
  int total = 0;
  Serial.print("PLAYER ");
  Serial.print(player);
  Serial.println(" HAND:");
  for(int x=0; x<2; x++){
  int draw = drawCard();
  total += draw;
}
if(total > 21){
  total -= 20;
  if(total == 11){
    total = 21;
  }
}

 return total;
}
void tableDraw(){
  
    for(int x=0; x<3; x++){
    drawCard();
    }
if(turn == 1){
  for(int x=0; x<2; x++){
    int badDraw = drawCard();
    if(badDraw > 0){
      x -= 1;
    }
  }
}
if(turn == 2){
  for(int x=0; x<2; x++){
    int badDraw = drawCard();
    if(badDraw > 0){
      x -= 1;
    }
  }
}
}
void bust(int total){
if(total > 21){
  Serial.print("Bust! You broke now. ¯\_(ツ)_/¯");
  currentPlayer += 1;
  inPlay = false;
}
} 

int hit(int total){
  if(total != 21){
    int hitCard = drawCard();
    if(hitCard == 21){
      if((total + 11) > 21){
        hitCard = 1;
      }
      else{
        hitCard = 11;
      }
    }
    Serial.print("HIT: CARD DRAWN ");
    Serial.println(hitCard);
    total += hitCard;
    Serial.print("NEW TOTAL: ");
    Serial.println(total);
    return total;
  }
}
void stand(int total){
  if(total < 22){
  Serial.print("STAND: PLAYER ");
  Serial.print(currentPlayer);
  Serial.print(" FINAL TOTAL:");
  Serial.print(total);
  currentPlayer += 1;
  inPlay = false;
  }
}
void compareToHouse(){
  
}