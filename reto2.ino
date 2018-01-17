#include <LiquidCrystal.h>
#include <Servo.h>

Servo servo1; //Contructor para el servo
LiquidCrystal lcd(8,9,4,5,6,7); // define los pines en la tarjeta Arduino
int v=-1;
int puertoservo=3; //Variable que se utliza para mandar datos al servo
int trig=13;
int echo =12;

int grados; // guarda los grados que gira el brazo del servo
int tmp=0; // se utliza como condicional
int pulsominimo=650; // para el ángulo menor del servo
int pulsomaximo=2250; // para el ángulo mayor del servo
float disCalculada;
//----para la tonada--//
int spk = 2; // Variable del pin del piezo
int c[5]={131,262,523,1046,2093};       // frecuencias 4 octavas de Do
int cs[5]={139,277,554,1108,2217};      // Do#
int d[5]={147,294,587,1175,2349};       // Re
int ds[5]={156,311,622,1244,2489};    // Re#
int e[5]={165,330,659,1319,2637};      // Mi
int f[5]={175,349,698,1397,2794};       // Fa
int fs[5]={185,370,740,1480,2960};     // Fa#
int g[5]={196,392,784,1568,3136};     // Sol
int gs[5]={208,415,831,1661,3322};   // Sol#
int a[5]={220,440,880,1760,3520};      // La
int as[5]={233,466,932,1866,3729};    // La#
int b[5]={247,494,988,1976,3951};      // Si

void nota(int a, int b);            // declaración de la función auxiliar. Recibe dos números enteros.
//---fin variables para la tonada--//


void setup() 
{
  lcd.setCursor (4,1); //ubica el cursor en laposición 4 de la fila 1
  lcd.print("PRONIE"); // ESCRIBE EN LA PANTALLA
  lcd.noBlink(); //No parpade
  delay(2000); 
  //-----------------------//
  servo1.attach (puertoservo, pulsominimo, pulsomaximo); //envia el puerto de trabajo, y los angulos máximo y mínimo de trabajo
  //---------//
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT); 
  pinMode (spk, OUTPUT);
  //------//
  Serial.begin (9600);
}



void loop() 
{
  disCalculada = calcularDistancia();
  grados=servo1.read();
  Serial.println("Grados :");
  Serial.println(grados);
  delay (200);
  Serial.print("cm :");
  Serial.println(disCalculada);
  delay(200);
  if (disCalculada < 100) // Condicional que se activa si la distancia es menor de 100 cm
  {
    tmp=100; //equivale un angulo de 100 grados
    servo1.write(tmp);
    melodia();
  }
  else
  {
    tmp=0;
  }
  //delay (10); 
  servo1.write(tmp); //le da la indicación al servo de ejecutar el giro (depende de los grados en la variable)
  lcd.setCursor (1,1); //ubica el cursor en la posición 1 de la fila 1
  lcd.print("DISTANCIA "); // ESCRIBE EN LA PANTALLA
  lcd.println(disCalculada); //Mostramos en la pantalla lcd el valor de la variable
}
int calcularDistancia()
{
  long distancia;
  long duracion;
  digitalWrite (trig, LOW);
  delayMicroseconds (4);
  digitalWrite(trig, HIGH);
  delayMicroseconds (10);
  digitalWrite(trig, LOW);
  duracion=pulseIn (echo, HIGH);
  duracion=duracion / 2;
  distancia= duracion / 29;
  return distancia;
}
void melodia()
{
//**************************************/
/*                  HARRY POTTER                    */
/**************************************/
nota(b[2], 500);          
nota(e[3],1000); 
nota(g[3], 250);
nota(fs[3],250);
nota(e[3],1000);
nota(b[3],500);
nota(a[3],1250);
nota(fs[3],1000);    
nota(b[2], 500);
nota(e[3],1000);
nota(g[3],250);  
nota(fs[3],250);
nota(d[3],1000);
nota(e[3],500 );
nota(b[2],1000 );    
noTone(spk); //delay(1000);   
//nota(b[2], 500);
//nota(e[3],1000);
//nota(g[3], 250);
//nota(fs[3],250);
//nota(e[3],1000);
//nota(b[3],500);
//nota(d[4],1000);
//nota(cs[4],500);
//nota(c[4],1000);
//nota(a[3],500);
//nota(c[4],1000);
//nota(b[3],250);
//nota(as[3],250);
//nota(b[2],1000);
//nota(g[3],500);
//nota(e[3],1000);
//noTone(spk); 
//delay(2000);       
}


void nota(int frec, int t)
{
    tone(spk,frec);      // suena la nota frec recibida
    delay(t);                // para despues de un tiempo t
}
