/*
Autor: Pedro Victor Andrade Alves
Computer Engineer Student
*/

// Programa : Data e Hora com DS1307

#include "Wire.h"

#define DS1307_ADDRESS 0x68

byte zero = 0x00; 
 
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger 12
#define pino_echo 13
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

#include <Servo.h>
 
#define servoPin 6
Servo servo_motor;
void servo_slow(const int tempo, int inicio, int fim);

//Programa : Teste display Nokia 5110 usando biblioteca Adafruit

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>

// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS/CE)
// pin 7 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 7);

volatile int BOTAO = LOW;
const int bomba_entrada_agua = 3;
const int bomba_saida_agua = 5;

float quantidade_Kcal = 0; 
float energia_meta = 0;
int hora_1 = 24;
int minuto_1 = 60; 
int hora_2 = 24;
int minuto_2 = 60;
int hora_3 = 24; 
int minuto_3 = 60;
int hora_troca_agua_1 = 24;
int minuto_troca_agua_1 = 60;
int hora_troca_agua_2 = 24;
int minuto_troca_agua_2 = 60;
int i = 1;
int cmMsec, inMsec;
int minutos, horas;
int leia_balanca;
int quanti_racao_1, quanti_racao_2, quanti_racao_3;
int quan_1, quan_2, quan_3;

void setup(){
  
  Serial.begin(9600); // Comece saída Serial
  
  Wire.begin();
  SelecionaDataeHora(); //Essa linha pode ser retirada apos setar a data e hora
 
  pinMode(servoPin, OUTPUT);
  servo_motor.attach(servoPin);
  servo_motor.write(50);
  
  pinMode(bomba_entrada_agua, OUTPUT);
  pinMode(bomba_saida_agua, OUTPUT);
  attachInterrupt(0, on_off, RISING);

   //------------------------------------------------------------------
  
  travar:
  
  if(BOTAO == LOW){
    goto travar; 
  }
  /*else{
    goto ligar;
  }
 ligar:*/
  
  display.begin();
  display.clearDisplay();   //Apaga o buffer e o display
  
  display.setContrast(40); //Ajusta o contraste do display
  display.setTextSize(1);  //Seta o tamanho do texto
  display.setTextColor(BLACK); //Seta a cor do texto
  display.setCursor(0,0);  //Seta a posição do cursor
  display.println("Oi, meu nome e");  

  display.setTextSize(2); 
  display.setTextColor(BLACK);
  display.print("     AU     ");
  display.display();

  delay(4000);
  
  //------------------------------------------------------------------
  
  display.clearDisplay();   //Apaga o buffer e o display 
  
  display.setContrast(40); //Ajusta o contraste do display
  display.setTextSize(1); 
  display.setTextColor(BLACK);
  display.setCursor(0,0);  //Seta a posição do cursor
  display.print("Sou um assis- ");
  
  display.setTextColor(BLACK); 
  display.print("tente alimen- ");
  
  display.setTextColor(BLACK); 
  display.print("tar canino    ");
  display.display();
 
  delay(4000);
  
  //------------------------------------------------------------------
  
  display.clearDisplay();   //Apaga o buffer e o display
  
  display.setContrast(40); //Ajusta o contraste do display
  display.setTextSize(1); 
  display.setTextColor(BLACK);
  display.setCursor(0,0);  //Seta a posição do cursor
  display.print("Depois de for-");
  
  display.setTextColor(BLACK); 
  display.print("necer as infor");
  
  display.setTextColor(BLACK); 
  display.print("macoes, aguar-");
  
  display.setTextColor(BLACK); 
  display.print("de os horarios");
  display.display();

  delay(4000);
  
  //------------------------------------------------------------------
  
}

void loop(){
  codigo();

  //##########(RAÇÃO)##################
  
  while(Serial.available() > 0){
    int leitura = Serial.parseInt();
    codigo();
        
     if(i == 1){
        quantidade_Kcal = leitura;
        i = 2;
        codigo();
      }
  
      if(i == 2){
        if(leitura != quantidade_Kcal){  
        energia_meta = leitura;
        i = 3;
        codigo();
        }
      }
      
      if(i == 3){
        if(leitura != energia_meta){
        hora_1 = leitura;
        i = 4;
        codigo();
        }
      }
      
      if(i == 4){
        if(leitura != hora_1){
        minuto_1 = leitura; 
        i = 5;
        codigo();
        } 
      }
      
      if(i == 5){
        if(leitura != minuto_1){
        hora_2 = leitura;
        i = 6;
        codigo();
        }
      }
      
      if(i == 6){
        if(leitura != hora_2){
        minuto_2 = leitura;
        i = 7;
        codigo();
        }
      }
      
      if(i == 7){
        if(leitura != minuto_2){
        hora_3 = leitura;
        i = 8;
        codigo();
        }
      }
      
      if(i == 8){
        if(leitura != hora_3){
        minuto_3 = leitura;
        i = 9;
        codigo();
        }
      }
   
   //##########(ÁGUA)##################
   
      if(i == 9){
        if(leitura != minuto_3){
        hora_troca_agua_1 = leitura;
        i = 10;
        codigo();
        }
      }
      
      if(i == 10){
        if(leitura != hora_troca_agua_1){
        minuto_troca_agua_1 = leitura;
        i = 11;
        codigo();
        }
      }
      
      if(i == 11){
        if(leitura != minuto_troca_agua_1){
        hora_troca_agua_2 = leitura;
        i = 12;
        codigo();
        }
      }
      
      if(i == 12){
        if(leitura != hora_troca_agua_2){
        minuto_troca_agua_2 = leitura;
        i = 1;
        codigo();
        }
      }
  }
         
}

  void codigo(){
    
     parar: 
        if(BOTAO == LOW){
          goto parar;  
        }
      
     Relogio_Tela();
     Sensor_Ultrassonico();
            
              if(cmMsec >= 19){ // Verifica se o recipiente da água está vazio
                  
                 display.clearDisplay();   //Apaga o buffer e o display
                
                 manutencao:
                  
                 display.setContrast(40); //Ajusta o contraste do display
                 display.setTextSize(1); 
                 display.setTextColor(BLACK);
                 display.setCursor(0,0);  //Seta a posição do cursor
                 display.print("Manutencao do ");
                  
                 display.setTextColor(BLACK);
                 display.print("nivel da agua ");

                 display.setTextColor(BLACK);
                 display.print("\n");
                  
                 display.setTextColor(BLACK);
                 display.print("LOADING...");
                 display.display();
                  
                 analogWrite(bomba_entrada_agua, 128); // A bomba d'água de entrada fica ligada até encher completamente
                 Sensor_Ultrassonico();
                  
                if(cmMsec <= 14){  // Verifica se o recipiente da água já está cheio
                    analogWrite(bomba_entrada_agua, 0); // desliga a bomba de entrada, porque o recipiente já está cheio
                    goto sair_da_manutencao; 
                  }else{
                    goto manutencao; // Precisa continuar enchendo
                  }
                  sair_da_manutencao:  
                  Relogio_Tela(); 
                  
              }
   
    if((horas == hora_1) && (minutos == minuto_1)){  // Verifica se está na hora da 1º refeição
          
             servo_slow(2, 50, 2); 
 
             display.clearDisplay();   //Apaga o buffer e o display
             
                    refeicao_1:

                    quan_1 = (quantidade_Kcal/energia_meta)*1000;
                    
                    display.setContrast(40); //Ajusta o contraste do display
                    display.setTextSize(1); 
                    display.setTextColor(BLACK);
                    display.setCursor(0,0);  //Seta a posição do cursor
                    display.print("Esta e a hora ");
                  
                    display.setTextColor(BLACK);
                    display.print("da 1 refeicao ");

                    display.setTextColor(BLACK);
                    display.print("\n");
                  
                    display.setTextColor(BLACK);
                    display.print("LOADING...");

                    display.setTextColor(BLACK);
                    display.print("\n\n");
                  
                    display.setTextColor(BLACK);
                    display.print(quan_1);

                    display.setTextColor(BLACK);
                    display.print("g de racao");
                    display.display();
               
               
             quanti_racao_1 = (((quan_1)*80)/72)+126; // Converte o valor em Kcal para ser compatível com o valor da leitura analógica 
             leia_balanca = analogRead(A0); // leitura do sensor de peso
             delay(2000);
             
             if((leia_balanca >= (quanti_racao_1)-3) && (leia_balanca <= (quanti_racao_1)+3)){ // Verifica se a quantidade de ração no recipiente é igual a predefinida
               goto sair_1_refeicao; // A quantidade de ração já é a correta, a 1º refeição terminou
             }else{
               goto refeicao_1; // continua fornecendo ração
             }

             sair_1_refeicao:

             servo_slow(2, 2, 50);
             
             while((horas == hora_1) && (minutos == minuto_1)){ // Se a ração for fornecida em menos de um minuto é preciso esperar ocorrer a mudança de minuto
               Relogio_Tela();
               Sensor_Ultrassonico();
             }
         }
         
    if((horas == hora_2) && (minutos == minuto_2)){  // Verifica se está na hora da 2º refeição
       
            servo_slow(2, 50, 2); 
            
            display.clearDisplay();   //Apaga o buffer e o display
   
                    refeicao_2:

                    quan_2 = (quantidade_Kcal/energia_meta)*1000;
                
                    display.setContrast(40); //Ajusta o contraste do display
                    display.setTextSize(1); 
                    display.setTextColor(BLACK);
                    display.setCursor(0,0);  //Seta a posição do cursor
                    display.print("O cao esta pre");
                  
                    display.setTextColor(BLACK);
                    display.print("cisando da 2  ");
                  
                    display.setTextColor(BLACK);
                    display.print("refeicao      ");

                    display.setTextColor(BLACK);
                    display.print("\n");
                  
                    display.setTextColor(BLACK);
                    display.print("LOADING...");
                    
                    display.setTextColor(BLACK);
                    display.print("\n\n");
                  
                    display.setTextColor(BLACK);
                    display.print(quan_2);

                    display.setTextColor(BLACK);
                    display.print("g de racao");
                    display.display();
               
               
             quanti_racao_2 = (((quan_2)*80)/72)+126;  // Converte o valor em Kcal para ser compatível com o valor da leitura analógica 
             leia_balanca = analogRead(A0);  // leitura do sensor de peso
             delay(2000);
             
             if((leia_balanca >= (quanti_racao_2)-3) && (leia_balanca <= (quanti_racao_2)+3)){  // Verifica se a quantidade de ração no recipiente é igual a predefinida
              goto sair_2_refeicao;  // A quantidade de ração já é a correta, a 2º refeição terminou
             }else{
              goto refeicao_2;  // continua fornecendo ração
             }

             sair_2_refeicao:
  
             servo_slow(2, 2, 50);
             
             while((horas == hora_2) && (minutos == minuto_2)){  // Se a ração for fornecida em menos de um minuto é preciso esperar ocorrer a mudança de minuto
               Relogio_Tela();
               Sensor_Ultrassonico();  
             }
       }
      
    if((horas == hora_3) && (minutos == minuto_3)){  // Verifica se está na hora da 3º refeição
       
             servo_slow(2, 50, 2); 
 
             display.clearDisplay();   //Apaga o buffer e o display
   
                    refeicao_3:

                    quan_3 = (quantidade_Kcal/energia_meta)*1000;
             
                    display.setContrast(40); //Ajusta o contraste do display
                    display.setTextSize(1); 
                    display.setTextColor(BLACK);
                    display.setCursor(0,0);  //Seta a posição do cursor
                    display.print("Essa e a ulti-");
                  
                    display.setTextColor(BLACK);
                    display.print("ma refeicao do");

                    display.setTextColor(BLACK);
                    display.print("dia           ");

                    display.setTextColor(BLACK);
                    display.print("\n");
                  
                    display.setTextColor(BLACK);
                    display.println("LOADING...");

                    display.setTextColor(BLACK);
                    display.print("\n\n");
                  
                    display.setTextColor(BLACK);
                    display.print(quan_3);

                    display.setTextColor(BLACK);
                    display.print("g de racao");
                    display.display();
               
               
             quanti_racao_3 = (((quan_3)*80)/72)+126;  // Converte o valor em Kcal para ser compatível com o valor da leitura analógica
             leia_balanca = analogRead(A0);  // leitura do sensor de peso
             delay(2000);
             
             if((leia_balanca >= (quanti_racao_3)-3) && (leia_balanca <= (quanti_racao_3)+3)){  // Verifica se a quantidade de ração no recipiente é igual a predefinida
              goto sair_3_refeicao;  // A quantidade de ração já é a correta, a 3º refeição terminou
             }else{
              goto refeicao_3;  // continua fornecendo ração
             }

             sair_3_refeicao:

             servo_slow(2, 2, 50);
              
             while((horas == hora_3) && (minutos == minuto_3)){  // Se a ração for fornecida em menos de um minuto é preciso esperar ocorrer a mudança de minuto
               Relogio_Tela();
               Sensor_Ultrassonico();
    }
        }
        
        if((horas == hora_troca_agua_1) && (minutos == minuto_troca_agua_1)){  // Verifica se está na hora da 1º troca d'água
       
                  display.clearDisplay();   //Apaga o buffer e o display
                  display.setContrast(40); //Ajusta o contraste do display
                  display.setTextSize(1); 
                  display.setTextColor(BLACK);
                  display.setCursor(0,0);  //Seta a posição do cursor
                  display.print("1 troca d agua");

                  display.setTextColor(BLACK);
                  display.print("\n");
                 
                  display.setTextColor(BLACK);
                  display.print("LOADING...");
                  display.display();
          
              Sensor_Ultrassonico();
      
              while(cmMsec < 19){  // Executa enquanto o recipiente da água não está vazio
                
                analogWrite(bomba_saida_agua, 128);  // A bomba d'água de saida fica ligada até secar  
                Sensor_Ultrassonico();
                  
              }
               
               analogWrite(bomba_saida_agua, 0);  // A água suja já foi retirada e a bomba d'água de saida é desligada
               delay(500);
  
               primeira_troca:
                                    
               analogWrite(bomba_entrada_agua, 128);  // A bomba d'água de entrada é ligada até encher o recipiente com água limpa
               Sensor_Ultrassonico();
                
               if(cmMsec <= 14){  // Verifica se o recipiente da água já está cheio
                 analogWrite(bomba_entrada_agua, 0);  // desliga a bomba de entrada, porque o recipiente já está cheio
                 goto sair_da_primeira_troca;
               }else{
                 goto primeira_troca;  // Precisa continuar enchendo
                }
                
               sair_da_primeira_troca:

               while((horas == hora_troca_agua_1) && (minutos == minuto_troca_agua_1)){  // Se a troca d'água acontecer em menos de um minuto é preciso esperar ocorrer a mudança de minuto
                  Relogio_Tela();
                  Sensor_Ultrassonico();
                 }        
        }
        
        if((horas == hora_troca_agua_2) && (minutos == minuto_troca_agua_2)){  // Verifica se está na hora da 2º troca d'água
       
                    display.clearDisplay();   //Apaga o buffer e o display                  
                    display.setContrast(40); //Ajusta o contraste do display
                    display.setTextSize(1); 
                    display.setTextColor(BLACK);
                    display.setCursor(0,0);  //Seta a posição do cursor
                    display.print("2 troca d agua");

                    display.setTextColor(BLACK);
                    display.print("\n");
                 
                    display.setTextColor(BLACK);
                    display.print("LOADING...");
                    display.display(); 
                                 
              Sensor_Ultrassonico();
      
              while(cmMsec < 19){   // Executa enquanto o recipiente da água não está vazio
                
                analogWrite(bomba_saida_agua, 128);  // A bomba d'água de saida fica ligada até secar
                Sensor_Ultrassonico();
                
              }
  
                analogWrite(bomba_saida_agua, 0);  // A água suja já foi retirada e a bomba d'água de saida é desligada
                delay(500);
  
                segunda_troca:
                  
                  analogWrite(bomba_entrada_agua, 128);  // A bomba d'água de entrada é ligada até encher o recipiente com água limpa
                  Sensor_Ultrassonico();
                
                if(cmMsec <= 14){  // Verifica se o recipiente da água já está cheio
                  analogWrite(bomba_entrada_agua, 0);  // desliga a bomba de entrada, porque o recipiente já está cheio
                  goto sair_da_segunda_troca;
                }else{
                  goto segunda_troca;  // Precisa continuar enchendo
                }
                
                sair_da_segunda_troca:

                while((horas == hora_troca_agua_2) && (minutos == minuto_troca_agua_2)){  // Se a troca d'água acontecer em menos de um minuto é preciso esperar ocorrer a mudança de minuto
                  Relogio_Tela();
                  Sensor_Ultrassonico();
                }    
        }
}


void on_off(){
      BOTAO = !BOTAO;
      if(BOTAO == LOW){
        display.clearDisplay();   //Apaga o buffer e o display
        display.display(); 
      }else{
        display.begin();
      }
    }

void Sensor_Ultrassonico(){
      
  //Le as informacoes do sensor, em cm e pol
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //delay(1000);
      
}
  

void SelecionaDataeHora(){   //Seta a data e a hora do DS1307

  byte segundos = 0; //Valores de 0 a 59
  minutos = 24; //Valores de 0 a 59
  horas = 9; //Valores de 0 a 23
  byte diadomes = 22; //Valores de 1 a 31
  byte mes = 3; //Valores de 1 a 12
  byte ano = 16; //Valores de 0 a 99
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //Stop no CI para que o mesmo possa receber os dados

  //As linhas abaixo escrevem no CI os valores de 
  //data e hora que foram colocados nas variaveis acima
  Wire.write(ConverteParaBCD(segundos));
  Wire.write(ConverteParaBCD(minutos));
  Wire.write(ConverteParaBCD(horas));
  Wire.write(ConverteParaBCD(diadomes));
  Wire.write(ConverteParaBCD(mes));
  Wire.write(ConverteParaBCD(ano));
  Wire.write(zero); //Start no CI
  Wire.endTransmission();
   
}

byte ConverteParaBCD(byte val){ //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val)  { //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}


void Relogio_Tela(){

     Wire.beginTransmission(DS1307_ADDRESS);
     Wire.write(zero);
     Wire.endTransmission();
     Wire.requestFrom(DS1307_ADDRESS, 7);
     int segundos = ConverteparaDecimal(Wire.read());
     minutos = ConverteparaDecimal(Wire.read());
     horas = ConverteparaDecimal(Wire.read() & 0b111111);  
     int diadomes = ConverteparaDecimal(Wire.read());
     int mes = ConverteparaDecimal(Wire.read());
     int ano = ConverteparaDecimal(Wire.read());
        
    display.clearDisplay();   //Apaga o buffer e o display
    
    display.setContrast(40); //Ajusta o contraste do display
    display.setTextSize(1); 
    display.setTextColor(BLACK);
    display.setCursor(0,0);  //Seta a posição do cursor
    display.print("Assistente: AU");

    display.setTextColor(BLACK);
    display.print("\n");
  
    display.setTextColor(BLACK);
    display.print(horas);

    display.setTextColor(BLACK);
    display.print(":");

    display.setTextColor(BLACK);
    display.print(minutos); 

    display.setTextColor(BLACK);
    display.print(":");

    display.setTextColor(BLACK);
    display.print(segundos);

    display.setTextColor(BLACK);
    display.print("\n\n");

    display.setTextColor(BLACK);
    display.print("AGUA");

    display.setTextColor(BLACK);
    display.print("\n");

    display.setTextColor(BLACK);
    display.print("Distancia: ");

    display.setTextColor(BLACK);
    display.print(cmMsec);
    display.display();  

}

void servo_slow(const int tempo, int inicio, int fim){

  bool option=0;
  if(fim > inicio) option=0;

  else option=1;

  if(!option){
    for(int i=inicio;i<fim;i++){
      servo_motor.write(i);
      delay(tempo);
    }
    
  }else{
    for(int j=inicio;j>fim;j--){
      servo_motor.write(j);
      delay(tempo);
    }
  } 
}



