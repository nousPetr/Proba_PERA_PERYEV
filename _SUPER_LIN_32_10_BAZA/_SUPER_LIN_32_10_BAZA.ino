    // Библиотека для работы с текстовым дисплеем
    #include <LiquidCrystalRus.h>
    #include <EEPROM.h>   


#include <Wire.h>

unsigned char Daten [30];
    

const char _0[] PROGMEM = " 0";
const char _1[] PROGMEM = " 1";
const char _2[] PROGMEM = " 2";
const char _3[] PROGMEM = " 3";
const char _4[] PROGMEM = " 4";
const char _5[] PROGMEM = " 5";
const char _6[] PROGMEM = " 6";
const char _7[] PROGMEM = " 7";
const char _8[] PROGMEM = " 8";
const char _9[] PROGMEM = " 9";
const char _10[] PROGMEM = "10";
const char _11[] PROGMEM = "11";
const char _12[] PROGMEM = "12";
const char _I2C[]PROGMEM={"Сбой по шине I2C"};
const char SUPERMATIC[]PROGMEM={"SUPERMATIC NT v1"};
const char AQVATROL[]={"  А-ЛАБОР  N"};  // eeprom    unsigned char AQVATROL[]={"AQVATROL   N"};
const char SUPERMATIC_R[]={"СУПЕРМАТИК NT v2"};
const char vrem[]={"ВРЕМЯ"};
const char vnesh[]={"ВНЕШН"};  
const char obem[]={"ОБЪЕМ"};
const char vr_obem[]={"ВР+ОБ"};
const char d_week[]={"ДЕНЬ "};

const char pusk_[] PROGMEM = "ПУСК";
const char stop_[] PROGMEM = "СТОП";
const char chasov[] PROGMEM = "ЧАСОВ";
const char dney[] PROGMEM = " ДНЕЙ";
const char vnesh_signal[] PROGMEM = "  ВНЕШНИЙ СИГНАЛ";
const char stroka_pusto[] PROGMEM = "                ";
const char week_day1[] PROGMEM = "Пн";
const char week_day2[] PROGMEM = "Вт";
const char week_day3[] PROGMEM = "Ср";
const char week_day4[] PROGMEM = "Чт";
const char week_day5[] PROGMEM = "Пт";
const char week_day6[] PROGMEM = "Сб";
const char week_day7[] PROGMEM = "Вс";
const char vremeni[] PROGMEM = "    ВРЕМЕНИ     ";
const char vnesh_signalu[] PROGMEM = "ВНЕШНЕМУ СИГНАЛУ";
const char obemu[] PROGMEM = "    ОБЪЕМУ      ";
const char vremeni_i_obyom[] PROGMEM = " ВРЕМЕНИ+ОБЪЕМУ ";
const char den_nedeli[] PROGMEM = "  ДЕНЬ НЕДЕЛИ   ";

const char vrem_[] PROGMEM = "ВРЕМЯ           ";
const char regeneratsiya[] PROGMEM = "РЕГЕНЕРАЦИЯ";
const char cherez[] PROGMEM = " ЧЕРЕЗ ";
const char dlitelnost[] PROGMEM = "  ДЛИТЕЛЬНОСТЬ  ";
const char minut[] PROGMEM = " МИНУТ ";
const char zapret[] PROGMEM = "ЗАПРЕТ-";
const char vrem_data[] PROGMEM = "ВРЕМЯ   ДАТА ";
const char vrem_i_data[] PROGMEM = "ВРЕМЯ И ДАТА";
const char tip_filtra[] PROGMEM = " ТИП УСТАНОВКИ  ";

const char _00[] PROGMEM = "  ";
const char _000[] PROGMEM = "   ";
const char _0000[] PROGMEM = "    ";
const char FSB[] PROGMEM = "FSB";  // FBR  FBS  FAS  SU5  SD4  SD5
const char filtrov[] PROGMEM = " ФИЛЬТРОВ ";
const char filtr[] PROGMEM = "ФИЛЬТР ";
const char vodoschetchik[] PROGMEM = "  ВОДОСЧЕТЧИК   ";
const char _100[] PROGMEM = "100";
const char message[] PROGMEM = "Global pgm string";

//&&&&&&&&&&  taimer  enkoder  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    unsigned char i =0;

    unsigned long timSec;
    unsigned int  Sec_1=1;
    unsigned int  Sec_2=0;
    unsigned long Sec_3=1;
    unsigned long Sec_4=0;

    unsigned int  Sec_1_old=0;
    unsigned int  Sec_2_old=0;
    unsigned long Sec_3_old=0;
    unsigned long Sec_4_old=0;

    //&&&&&&&&&&  taimer  enkoder  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
     
    // Задаём имя пинов дисплея
    constexpr uint8_t PIN_RS = 9;
    constexpr uint8_t PIN_EN = 8;
    constexpr uint8_t PIN_DB4 = 7;
    constexpr uint8_t PIN_DB5 = 6;
    constexpr uint8_t PIN_DB6 = 5;
    constexpr uint8_t PIN_DB7 = 4;
  
    /*
     * Создаём объект для работы с текстовым дисплеем
     * LiquidCrystalRus lcd(RS, EN, DB4, DB5, DB6, DB7);
     * Подробности подключения:
     * http://wiki.amperka.ru/products:display-lcd-text-16x2
    */
     
    LiquidCrystalRus lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);
         //Конфигурация вх - вых

    unsigned char cont_encoder =0;
    unsigned char cont_push_btn=0;    

    
    constexpr uint8_t _OK   = 15;  // KEY
    constexpr uint8_t _mins = 16;  // S2
    constexpr uint8_t _pls  = 17;  // S1

    constexpr uint8_t _K  = 14;    // LCD  Green o---|<|---[2k]---o +5v
     

byte Flags_1 = 0; // все флаги в false
// можно задефайнить названия
// цифры по порядку 0-7
#define old_ok   0
#define old_pls  1
#define old_mins 2
#define new_ok   3
#define new_pls  4
#define new_mins 5
#define encoder  6
#define push_btn_1 7



byte Flags_2 = 0; // все флаги в false
// можно задефайнить названия
// цифры по порядку 0-7
#define old_ok     0
#define old_pls    1
#define old_mins   2
#define new_ok     3
#define new_pls    4
#define new_mins   5
#define push_btn   6
#define push_btn_2 7 //Флаг долгого нажатия  _Ok



    
     
    void setup()
    {
        Serial.begin(9600);           // start serial for output
      
      // Устанавливаем размер экрана
      // Количество столбцов и строк
      lcd.begin(16, 2);
      // Устанавливаем курсор в колонку 5 и строку 0
      lcd.setCursor(5, 0);
      // Печатаем первую строку
      lcd.print("Привет");
      // Устанавливаем курсор в колонку 3 и строку 1
      lcd.setCursor(3, 1);
      // Печатаем вторую строку
      lcd.print("от Азюрки");

      delay(2000);



      pinMode(_OK, INPUT);  
      pinMode(_pls, INPUT);  
      pinMode(_mins, INPUT); 

      pinMode(_K, OUTPUT);       







String LCD_16_0 ; 
String LCD_16_1;
//LCD_16_0.reserve(1); 
//LCD_16_1.reserve(17);  ;  
String str ("This is a string");  
String str1 = String("is a string"); 
String str2 = String("This ring"); 
//  for ( i = 0; i < 10; i++)
//  {
//   // str[10]={"slave_adr1=0x20"};
//  Serial.print(str);
//    Serial.print("\t");
//  } 
LCD_16_0=&str1[0];
 Serial.println(LCD_16_0);
  for ( i = 0; i < 11; i++)
  {
  Serial.print(str1[i]);
  Serial.print("\t");
  } 
   Serial.println("str1[i]");
    for ( i = 0; i < 11; i++)
  {
  Serial.print(str2[i]);
  Serial.print("\t");
  } 
 Serial.println("str2[i]");


Serial.println(_0);


// **********************  I2C  ***************************
  Wire.begin(0x42);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event

    Wire.onRequest(requestEvent); // зарегистрировать событие. <--
    // <--Отправляет данные как ведомое устройство I2C/TWI.


//  *********************  I2C  *****************************
 
      
    }
     
    void loop() 
     {



          if(millis()- timSec >10)// Интервал 20 милиСек
         {  
              timSec = millis();
             if(Sec_1)
             {
             Sec_1++;// первый таймер ... запускается записью еденички..
               digitalWrite(_K, HIGH);   // turn the LED on (HIGH is the voltage level)
                  delay(1);                       // wait for a second
               digitalWrite(_K, LOW);
               //_K=!_K;               //....отсчитывает до 21 минуты              
             }

             if(Sec_2)Sec_2++;// второй таймер ... запускается записью еденички..
                              //....отсчитывает до 21 минуты 

              Sec_3++;
             if(Sec_3>101)
             {
                Sec_3=1;// третий таймер ... запускается записью еденички..
                Serial.println("-----> Sek_3<-----");        //....отсчитывает до 21 минуты 
              
              }
                              

                                 
       // push buton .... push buton ....push buton .... push buton ....push buton .... push buton ....              
                  if (digitalRead(_OK))
                   {  
                    // Serial.print("NO push_btn   cont_push_btn=");Serial.println(cont_push_btn);
                      if ((cont_push_btn)&&(Sec_2))
                      {

                        Sec_2_old=Sec_2;
                         bitClear(Flags_2,push_btn );
                         bitClear(Flags_1,push_btn_1 );
                         bitClear(Flags_2,push_btn_2 );

                        if((cont_push_btn>5)&&(cont_push_btn<50))
                          {
                            bitSet(Flags_1,push_btn_1 );// короткое нажатие
                          }
                        if(cont_push_btn>100)
                          {
                            bitSet(Flags_2,push_btn_2 );//длинное нажатие
                            bitClear(Flags_1,push_btn_1 );
                          }             
                                                           //asm volatile ("nop ");
                      }
                      else
                      {
                         asm volatile ("nop ");
                      };
                     cont_push_btn=0;
                     //Sec_2=0;//  выключили  таймер 2 
                    }
                else
                    { 
                       cont_push_btn++;                       
                       Sec_2=1;
                         if(cont_push_btn>3)
                          {
                            bitSet(Flags_2,push_btn );
                        //     Serial.print("push_btn  cont_push_btn=");Serial.println(cont_push_btn);
                             if(cont_push_btn>200)
                             {
                              cont_push_btn=200;
                             }                             
                          }                       
                                                        


                    };
         // push buton .... push buton ....push buton .... push buton ....push buton .... push buton ....                             
                       

                     


                 
            //encoder....encoder....encoder....encoder....encoder....encoder....encoder....
                       if (bitRead(Flags_1,encoder ))// если FLAG_1 .6 == true
           {

                     if (digitalRead(_pls)&&digitalRead(!_mins))
                    {
                      cont_encoder++;
                     }

                     if (digitalRead(!_pls)&&digitalRead(_mins))
                     {
                      cont_encoder--;
        
                     }
                bitClear(Flags_1,encoder);
            }
            if (digitalRead(_pls)&&digitalRead(_mins))
                    {
                       bitSet(Flags_1,encoder);
                     }
             //encoder....encoder....encoder....encoder....encoder....encoder....encoder....

          };

//
//          if (digitalRead(_pls))  bitSet(Flags_1,new_pls );
//          else  bitClear(Flags_1, new_pls);
//          if (digitalRead(_mins))  bitSet(Flags_1,new_mins );
//          else  bitClear(Flags_1, new_mins);
//          if (digitalRead(_OK))  bitSet(Flags_1,new_ok );
//          else  bitClear(Flags_1, new_ok);          


      if(Sec_1>5)// 100 mSec
      {

        Sec_1=1;
          lcd.clear();
  // Serial.print("cont_encoder="); Serial.println( cont_encoder);

  //lcd.print((const __FlashStringHelper*)_5);
    lcd.print("cont_encoder=");lcd.print( cont_encoder);

    
//************************************************************************
//Serial.println(digitalRead(_OK));
//if (digitalRead(_OK))
//{
//    bitSet(Flags_2,push_btn_2);
//
//}
//else 
//{
//  // установить  в false
//  bitClear(Flags_2,push_btn_2);
//  
//}
//***********************************************************************
    
        lcd.setCursor(0, 1);
        digitalRead(_pls);

        lcd.print("_pls=");
             if (digitalRead(_pls))
         {
           lcd.print("1 ");
        
         }
         else
         {
         lcd.print("0 ");
         }

                 digitalRead(_mins);

        lcd.print("_mins=");
             if (digitalRead(_mins))
         {
           lcd.print("1 ");
        
         }
         else
         {
         lcd.print("0 ");
         }
   // delay(20);

   
   // push buton .....LCD....push buton .....LCD....push buton .....LCD....push buton .....LCD..
//                    if (digitalRead(_OK))
//                    {
//                      bitSet(Flags_1, push_btn_1);
//                     }
                   
                   if (bitRead(Flags_1, push_btn_1)) 
                               {// если push_btn_1 == true
                                // Устанавливаем курсор в позицию 15 второй  строки
                                 lcd.setCursor(14, 1);
                                 lcd.print("o");
                       //      Serial.print("push_btn_1");// Serial.println( cont_encoder);
                               };
                   if (bitRead(Flags_2, push_btn_2)) 
                               {// если push_btn_2 == true
                                // Устанавливаем курсор в позицию 15 второй  строки
                                 lcd.setCursor(14, 1);                                                                
                                 lcd.print("U");
                     //       Serial.print("push_btn_2  ");
                               }
                     if(Sec_2>200)// второй таймер отсчитал 4 сек после отпуска кнопки
                     {
                      Sec_2=0;// второй таймер СТОП
                      
                      bitClear(Flags_1,push_btn_1 );
                      bitClear(Flags_2,push_btn_2 );
                      //надписи  о нажатии кнопки стёр....
                     }
   // push buton .....LCD....push buton .....LCD....push buton .....LCD....push buton .....LCD..
   
   Serial.println((const __FlashStringHelper*)_0);  
   Serial.println((const __FlashStringHelper*)_1);
   Serial.println((const __FlashStringHelper*)_2);
   Serial.println((const __FlashStringHelper*)_3);
   Serial.println((const __FlashStringHelper*)_4);            
   Serial.println((const __FlashStringHelper*)_5);             

  // send what's going on to the serial monitor.
  Serial.println("17"); Serial.println("17"); Serial.println("17"); 

 
  // New line on display
  Serial.println();
delay(500);
      }

     }



     

// функция, которая выполняется всякий раз, когда данные получены от мастера
// эта функция регистрируется как событие, см. setup()
void receiveEvent(int howMany) 
{
  while (1 < Wire.available()) { // просмотреть все, кроме последнего
    char c = Wire.read(); // получить байт как символ
    Serial.print(c);         // напечатать  символ
  }
  int x = Wire.read();    // получить байт как целое число
  Serial.println(x);         // напечатать целое число

}

// функция, которая выполняется всякий раз, когда данные запрашиваются мастером
// эта функция регистрируется как событие, см. setup()
void requestEvent() 
{
Daten[0]++;


  Wire.write(Daten,10); //ответить сообщением размером 32 байт
 // Wire.write(" @he"); //ответить сообщением размером 32 байт// как и ожидал мастер
 // Wire.write(x); //ответить сообщением размером 32 байт
 
}

//***************************************************************************
//******************   EEPROM  **********************************************
//***************************************************************************

//  void writeEEPROM()
//
//  {
//
//     int address = 10;
//  //  char *newString[] = myString.c_str();
//
//     for (byte i; i<sizeof(newString); i++)
//      {
//         EEPROM.put(address, newString[i]);
//      }
//     address +=sizeof(newString);
//     
//  }

//  eeprom    unsigned char slave_adr1_0x20[]={"slave_adr1=0x20"};  
/*
void setup() {
  // установить FLAG5 в true
  bitSet(myFlags, FLAG5);
  // установить FLAG1 в true
  bitSet(myFlags, FLAG1);
  // установить FLAG1 в false
  bitClear(myFlags, FLAG1);
  // считать FLAG5
  bitRead(myFlags, FLAG5);
  // условие с флагом 7
  if (bitRead(myFlags, FLAG7)) {
    // если FLAG7 == true
  }
}
*/                       




// eeprom    unsigned char slave_adr1_0x20[]={"slave_adr1=0x20"}; 
//unsigned char str[10]={"slave_adr1=0x20"};
//unsigned char str1[10]={"slave_adr1=0x21"};
//unsigned char str2[10]={"slave_adr1=0x22"};
//char* str = "text";
//char* str1;
//char* str2;
//char address=20;    /////////////////////////////////////////////////////
//char address1=40;  /////////////////////////////////////////////////////
//char address2=60; /////////////////////////////////////////////////////

// Выделяем память для str1
//str  =  char[20];
//str1 =  char[20];
//str2 =  char[20];
// Вставляем какие-то данные
//str1[0] = 'a';
//str1[1] = 'b';
//str1[2] = 'c';
// Запись в EEPROM str1
//EEPROM.put(address1, str1);
// Освобождаем память от str1
//delete [] str1;
// Запись в EEPROM str = "text" - статический массив символов
//EEPROM.put(address, str);
/*****************************************
Перезагружаем контроллер
*****************************************/
// Читаем из EEPROM в str1
//EEPROM.get(address1, str1); // Читает ерунду
// Читаем из EEPROM в str2
//EEPROM.get(address, str2); // Читает нормально - str = "text"!.
