#include <Servo.h>  


Servo servo[2];
int servo_pin[2] = { A4, A5};


int Estado = 0;
int leyo = 0;


String val = "";


int No_Servos = 2;
int No_ServosCont = 0;


int GotNumPasos = 0;
int GotDirPasos = 0;
int NumPasos = 0;
int NumPasosDados = 0;
int DirPasos = 0;
int Historico = 0;


int Titileo = 100;


int NumComandos = 5;
int NumComandosCont = 0;


int pot1 = 0;
int pot2 = 0;
int switch1 = 0;


// PIN 6 ES PARA DAR STEP
// PIN 7 PARA DIRECCION


void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(13, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  PrintMenuP();


  ServosInit();
}


void loop(void)
{
  Parpadeo(2);
  Parpadeo(3);


  pot1 = analogRead(A0);
  pot2 = analogRead(A1);


  switch1 = digitalRead(13);

  if(Estado == 0)
  {
    if(Serial.available() > 0 )
    {
      char Dato = Serial.read();


      if(Dato == '1')
      {
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        PrintMenuOp1();
      }
      else if(Dato == '2')
      {
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        PrintMenuOp2();
      }
      else if(Dato == '3')
      {
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        PrintMenuOp3();
      }
      else if(Dato == '4')
      {
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        PrintMenuOp4();
      }
      else if(Dato == '5')
      {
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        Serial.println("");
        PrintMenuOp5();
      }
    }
   
  }
  else if(Estado == 1)
  {
    if(Serial.available() > 0 )
    {
      leyo = 1;
      char Dato = Serial.read();
      val = val + Dato;
      if(Dato == ',')
      {
        if(No_ServosCont == 0)
        {
          Serial.print("Servo 1: ");
          int length = val.length();
          val.remove(length-1);
          int valor = val.toInt();
          servo[No_ServosCont].write(valor%180);
          Serial.println(val);
          No_ServosCont += 1;
          val = "";
        }
        else if(No_ServosCont == 1)
        {
          Serial.print("Servo2: ");
          int length = val.length();
          val.remove(length-1);
          int valor = val.toInt();
          servo[No_ServosCont].write(valor%180);
          Serial.println(val);
          No_ServosCont += 1;
          PrintMenuP();
        }        
      }
    }
    if(leyo == 1 && Serial.available() == 0 )
    {
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("*****INGRESO INCORRECTO, DEBE REINTENTAR*****");
      PrintMenuOp1();
    }
  }
  else if(Estado == 2)
  {
    if(Serial.available() > 0 )
    {
      leyo = 1;
      char Dato = Serial.read();
      val = val + Dato;
      if(Dato == ',')
      {
        if(GotNumPasos == 0 && GotDirPasos == 0)
        {
          Serial.print("Numero de Pasos: ");
          int length = val.length();
          val.remove(length-1);
          NumPasos = val.toInt();
          Serial.println(val);
          GotNumPasos = 1;
          val = "";
        }
        else if(GotNumPasos == 1 && GotDirPasos == 0)
        {
          Serial.print("Direccion de Pasos: ");
          int length = val.length();
          val.remove(length-1);
          DirPasos = val.toInt();
          if(DirPasos == 1)
          {
            Serial.println("DERECHA");
            digitalWrite(7, HIGH);
            Historico = Historico + NumPasos;
            GotDirPasos = 1;
          }
          else if(DirPasos == 0)
          {
            Serial.println("IZQUIERDA");
            digitalWrite(7, LOW);
            Historico = Historico - NumPasos;
            GotDirPasos = 1;
          }
          else
          {
            GotDirPasos = 0;
          }
         
          val = "";
        }  
      }
    }
    if(GotDirPasos == 0 && Serial.available() == 0 && leyo ==1)
    {
      Serial.println("");
      Serial.println("");
      Serial.println("*****INGRESO INCORRECTO, DEBE REINTENTAR*****");
      PrintMenuOp2();
    }
   
    if(GotDirPasos == 1 && Serial.available() == 0)
    {
      if(NumPasosDados < NumPasos)
      {
        digitalWrite(6, HIGH);  
        delay(1);                      
        digitalWrite(6, LOW);
        delay(1);
        NumPasosDados += 1;
      }
      else
      {
        PrintMenuP();
      }
    }
  }
  else if(Estado == 3)
  {
    if(Serial.available() > 0 )
    {
      leyo = 1;
      char Dato = Serial.read();
      val = val + Dato;
      if(Dato == ',')
      {
        Serial.print("Tiempo en ms: ");
        int length = val.length();
        val.remove(length-1);
        Titileo = val.toInt();
        Serial.println(Titileo);
        val = "";
        PrintMenuP();
      }
    }
    if(leyo == 1 && Serial.available() == 0 )
    {
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("*****INGRESO INCORRECTO, DEBE REINTENTAR*****");
      PrintMenuOp3();
    }
  }
  else if(Estado == 4)
  {
    if(Serial.available() > 0 )
    {
      char Dato = Serial.read();
      if(Dato == ',')
      {
        PrintMenuP();
      }
    }
  }
  else if(Estado == 5)
  {
    if(Serial.available() > 0 )
    {
      leyo = 1;
      char Dato = Serial.read();
      val = val + Dato;
      if(Dato == ',')
      {
        if(NumComandosCont == 0)
        {
          Serial.print("Servo 1: ");
          int length = val.length();
          val.remove(length-1);
          int valor = val.toInt();
          servo[0].write(valor%180);
          Serial.println(val);
          NumComandosCont += 1;
          val = "";
        }
        else if(NumComandosCont == 1)
        {
          Serial.print("Servo2: ");
          int length = val.length();
          val.remove(length-1);
          int valor = val.toInt();
          servo[1].write(valor%180);
          Serial.println(val);
          NumComandosCont += 1;
          val = "";
          //PrintMenuP();
        }
        else if(NumComandosCont == 2)
        {
          Serial.print("Numero de Pasos: ");
          int length = val.length();
          val.remove(length-1);
          NumPasos = val.toInt();
          Serial.println(val);
          NumComandosCont += 1;
          val = "";
        }
        else if(NumComandosCont == 3)
        {
          Serial.print("Direccion de Pasos: ");
          int length = val.length();
          val.remove(length-1);
          DirPasos = val.toInt();
          if(DirPasos == 1)
          {
            Serial.println("DERECHA");
            digitalWrite(7, HIGH);
            Historico = Historico + NumPasos;
            NumComandosCont += 1;
          }
          else if(DirPasos == 0)
          {
            Serial.println("IZQUIERDA");
            digitalWrite(7, LOW);
            Historico = Historico - NumPasos;
            NumComandosCont += 1;
          }
          else
          {
            NumComandosCont -= 3;
          }
         
          val = "";
        }  
        else if(NumComandosCont == 4)
        {
          Serial.print("Tiempo en ms: ");
          int length = val.length();
          val.remove(length-1);
          Titileo = val.toInt();
          Serial.println(Titileo);
          val = "";
        }      
      }
    }
    if(NumComandosCont < NumComandos-1 && Serial.available() == 0 && leyo == 1)
    {
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("*****INGRESO INCORRECTO, DEBE REINTENTAR*****");
      PrintMenuOp5();
    }
    if(NumComandosCont == NumComandos-1 && Serial.available() == 0 )
    {
      if(NumPasosDados < NumPasos)
      {
        digitalWrite(6, HIGH);  
        delay(1);                      
        digitalWrite(6, LOW);
        delay(1);
        NumPasosDados += 1;
      }
      else
      {
        PrintMenuP();
      }
    }
  }
}


void Parpadeo(int pin)
{
  digitalWrite(pin, HIGH);  
  delay(Titileo);                      
  digitalWrite(pin, LOW);  
  delay(Titileo);  
}


void PrintMenuP(void)
{
  Serial.println("");
  Serial.println("----------------MENU PRINCIPAL----------------");
  Serial.println("1 - CAMBIAR SERVOS");
  Serial.println("2 - CAMBIAR POSICION DE STEPPER");
  Serial.println("3 - TIEMPO DE TITILEO");
  Serial.println("4 - OBTENER ESTATUS");
  Serial.println("5 - MODIFICAR TODO");
  Estado = 0;
}


void PrintMenuOp1(void)
{
  Serial.println("------------------ Opcion 1 ------------------");
  Serial.println("INGRESE LOS NUEVOS VALORES PARA LOS SERVOS COMO NUMERO ENTRE 1 Y 180 CON UNA COMA AL FINAL");
  Serial.println("EJEMPO: 75,150,");
  while(Serial.available() > 0 )
  {
    Serial.read();
  }
  Estado = 1;
  leyo = 0;
  val = "";


  No_ServosCont = 0;
}


void PrintMenuOp2(void)
{
  Serial.println("------------------ Opcion 2 ------------------");
  Serial.println("INGRESE LA CANTIDAD DE PASOS A DAR Y LA DIRECCION CON UNA COMA AL FINAL DE CADA VALOR");
  Serial.println("('1' PARA DERECHA Y '0' PARA IZQUIERDA)");
  Serial.println("EJEMPO: 10,1,     (10 PASOS A LA DERECHA)");
  while(Serial.available() > 0 )
  {
    Serial.read();
  }
  Estado = 2;
  leyo = 0;
  val = "";


  GotNumPasos = 0;
  GotDirPasos = 0;
  NumPasos = 0;
  NumPasosDados = 0;
  DirPasos = 0;
}


void PrintMenuOp3(void)
{
  Serial.println("------------------ Opcion 3 ------------------");
  Serial.println("INGRESE EL TIEMPO EN MS DESEADO PARA EL PARPADEO CON UNA COMA AL FINAL");
  Serial.println("EJEMPO: 75,       (EL VALOR PREDETERMINADO ES DE 100ms)");
  while(Serial.available() > 0 )
  {
    Serial.read();
  }
  Estado = 3;
  leyo = 0;
  val = "";
}


void PrintMenuOp4(void)
{
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("------------------ ESTATUS DEL SISTEMA ------------------");
 // Serial.println("ENVIE UNA COMA PARA REGRESAR AL MENU PRINCIPAL");
  Serial.print("Posicion Servo 1: ");
  Serial.println(servo[0].read());
  Serial.print("Posicion Servo 2: ");
  Serial.println(servo[1].read());
  Serial.print("Posicion Steper: ");
  Serial.println(Historico);
  Serial.print("Tiempo en ms de parpadeo de Leds: ");
  Serial.println(Titileo);
  Serial.print("Posicion Potenciometro 1: ");
  Serial.println(pot1);
  Serial.print("Posicion Potenciometro 2: ");
  Serial.println(pot2);
  Serial.print("Estado PushButton: ");
  if(switch1 == 1)
  {
    Serial.println("PRESIONADO");
  }
  else if(switch1 == 0)
  {
    Serial.println("SUELTO");
  }
  while(Serial.available() > 0 )
  {
    Serial.read();
  }
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Estado = 4;
}


void PrintMenuOp5(void)
{
  Serial.println("------------------ Opcion 5 ------------------");
  Serial.println("INGRESE LOS NUEVOS VALORES PARA LOS SERVOS COMO NUMERO ENTRE 1 Y 180 CON UNA COMA AL FINAL DE CADA UNO");
  Serial.println("SEGUIDO POR EL NUMERO DE PASOS Y LA DIRECCION CON UNA COMA AL FINAL DE CADA VALOR (1 = DERECHA Y ");
  Serial.println("0 = IZQUIERDA) CULMINANDO CON TIEMPO EN MS DESEADO PARA EL PARPADEO CON UNA COMA AL FINAL");
  Serial.println("");
  Serial.println("EJEMPO: 75,150,12,0,50,   (Servo1: 75°, Servo2: 150°, Pasos: 12, Direccion: Izquierda, Parpadeo: 50ms)");
  while(Serial.available() > 0 )
  {
    Serial.read();
  }
  Estado = 5;
  leyo = 0;
  val = "";


  NumComandosCont = 0;
  NumPasos = 0;
  NumPasosDados = 0;
  DirPasos = 0;
}


void ServosInit()
{
  for (int i = 0; i < 2; i++)
  {    
    servo[i].attach(servo_pin[i]);
    delay(50);  
  }
}
