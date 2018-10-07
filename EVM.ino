#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display



int votes[4]={0,0,0,0};
char inbyte;
String pwd="PASSWORD";                         //Default Password
String inpt="";
boolean flag=false;
boolean securitygranted=false;           
int i;



void setup() 
{
  Serial.begin(9600);                    //Begin serial communication
  lcd.init(); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
  lcd.backlight();

  
  pinMode(2, INPUT_PULLUP);              //Setting pins as input
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  //Intro
  lcd.setCursor(0,0);
  lcd.print(" VOTING MACHINE ");
  lcd.setCursor(0,1);
  lcd.print(" {NOT AVILABLE} ");
  Serial.println("ENTER PASSWORD");

  //Function for Serial Input
  serialEvent();
}



void loop() 
{
  

  while(flag==true)                     //Check flag for "V" command
  
  {
    
    //Button for Person 1
    if(digitalRead(2) == HIGH) 
    {
      flag=false;
      lcd.setCursor(0,0);
      lcd.print("  VOTED Person1 ");                  //Example candidate name
      lcd.setCursor(0,1);
      lcd.print("thank for voting");
      votes[0]=votes[0]+1;
      Next();
      }
      
     //Button for person 2
     else if(digitalRead(3) == HIGH)
      {
        flag=false;
        lcd.setCursor(0,0);
        lcd.print("  VOTED Person2 ");
        lcd.setCursor(0,1);
        lcd.print("thank for voting");
        votes[1]=votes[1]+1;
        Next();
        
      }
      
      
      //Button for person 3
      else if(digitalRead(4) == HIGH) 
      {
        flag=false;
        lcd.setCursor(0,0);
        lcd.print("  VOTED Person3 ");
        lcd.setCursor(0,1);
        lcd.print("thank for voting");
        votes[2]=votes[2]+1;
        Next();
      }
      
      
      //Button for Person 4
      else if(digitalRead(5) == HIGH)
      {
        flag=false;
        lcd.setCursor(0,0);
        lcd.print("  VOTED Person4 ");
        lcd.setCursor(0,1);
        lcd.print("thank for voting");
        votes[3]=votes[3]+1;
        Next();
     }
     
  }
}



void serialEvent()                     
  {
    while(Serial.available())
    {
      inbyte=(char)Serial.read();                   //Reading incoming character
      if(securitygranted==false)
      {
         inpt += inbyte;
         inbyte='\n';
      }   
    }
  
    commandcheck();
  
  }


void commandcheck()                         
  {
    switch (securitygranted)                    //See for the security permissions
    {
      case false: 
      {
        if(inpt==pwd)                          //Checking for password match
        {
          securitygranted=true;
          inbyte='\n';
          inpt="";
          Serial.println("NOW VOTING CAN BE DONE");
          Serial.println("Call for a voter");
          
          lcd.setCursor(0,0);
          lcd.print(" VOTING MACHINE ");

          lcd.setCursor(0,1);
          lcd.print("Show Your IDCard");
        }
        
        else if((inpt!=pwd)&&(inpt.length()>7))        //Mismatch
        {
          Serial.println(inpt);
          inpt=""; 
          inbyte='\n';
          Serial.println("WRONG PASSWORD");
          Serial.println("ENTER PASSWORD");
          delay(100);
          Serial.begin(9600);
        }
        break;
      }
      
      case true: 
      {
        
        if(inbyte=='V')             
        {
          flag=true;                             //Allowing voter to cast a single vote
          Serial.println("\n");
          Serial.println("Voter Allowed To Vote");
          lcd.setCursor(0,0);
          lcd.print("   PLEASE VOTE  ");
          lcd.setCursor(0,1);
          lcd.print("                ");

          inbyte='\n';
        }
        
        else if(inbyte=='R')
        {
          for(i=0;i<=3;i++)//Displaying vote tally
          Serial.println(votes[i]);
          inbyte='\n';
        }
        
        else
        {
          Serial.println(" UNKNOWN");
        }
        
        break;
      }
    }
  }

void Next(){
          delay(1600);
          lcd.setCursor(0,0);
          lcd.print(" VOTING MACHINE ");

          lcd.setCursor(0,1);
          lcd.print("Show Your IDCard");
          
      Serial.println("\n");
      Serial.println("Voted Call for Next Voter");
}

