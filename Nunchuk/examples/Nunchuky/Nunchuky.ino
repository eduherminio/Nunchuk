/*************************************Nunchucky**********************************
 * 
 * 
 *  **********************************Autoria************************************
 *  Eduardo Caceres de la Calle
 *  11/3/16
 *  Sistemas Digitales Avanzados (SDA)
 *  Grado en Ingenieria Electronica Industrial y Automatica
 *  Universidad de Valladolid (UVa) - EII
 *  *****************************************************************************
 *  
 *  ******************************Descripción:*****************************
 *  Sketch que permite controlar un motor y servomotor con un Nunchuck 
 *  Más concretamente, realiza las siguientes funciones:
 *  - Muetra por pantalla los valores recibidos del Nunchuck
 *  - Controla la velocidad y sentido de giro del motor de DC 
 *  a partir del valor de la variable accelY, que representa
 *  la inclinación del Nunchuck en ese eje.
 *  - Controla el posicionamiento del servomotor a partir del
 *  valor de la variable accelX, que representa la inclianción
 *  del Nunchuk en ese eje.
 *  
 *  Para ello, nos basamos en nuestra librería Nunchuk (que a su
 *  vez recurre a la librería pública Wire.h) y en la librería Servo
 *  ******************************************************************
*/

#include <Wire.h>
#include <Nunchuk.h>
#include <Servo.h>

Nunchuk our_nunchuk;
Servo our_servo;

#define pin_servo 11  // Pin para controlar el servo
#define pwm 6         // Pines para controlar el motor DC
#define mi 7
#define md 8

#define BAUDRATE 19200  // Velocidad de transmisión

int direccion=0;      // Variable que almacena accelX
// Suponiendo un vehículo cuya marcha es controlada por el motor de DC
// y cuya dirección lo es por el servomotor, este valor representaría
// este último parámetro.

void monitorSerie();
/*  Muestra los valores de las variables que definen la orientación
 *  del Nunchuck por el puerto serie.
 */
 
void controlServo();
/*  Controla la posición del Servo, ajustándola según el valor de 
 *  accelX.
 */
 
void controlDC();
/*  Controla la velocidad y el sentido del giro del motor de continua
 * según el valor de accelY.
 */
 
void setup()
{
  Serial.begin(BAUDRATE);
  our_nunchuk.init();
  our_servo.attach(pin_servo);  // pinMode(pin_servo, OUTPUT);
  
  pinMode(mi, OUTPUT);
  pinMode(md, OUTPUT);
}

void loop()
{
  our_nunchuk.update();   // Refresca el estado de las variables
                          // del Nunchuck
  monitorSerie();   // Muestra todos esos valores
  
  controlServo();   // Ajusta la posición del servo
  controlDC();      // Ajusta la velocidad y sentido de giro del motor
 
}

void monitorSerie()
{
  Serial.print("\nX: ");
  Serial.print(our_nunchuk.analogX, DEC);
  Serial.print("\tY: ");
  Serial.print(our_nunchuk.analogY, DEC);
  
  Serial.print("\tX_ac: ");
  Serial.print(our_nunchuk.accelX, DEC);
  Serial.print("\tY_ac: ");
  Serial.print(our_nunchuk.accelY, DEC);
  Serial.print("\tZ_ac: ");
  Serial.print(our_nunchuk.accelZ, DEC);
  
  Serial.print("\tZ_b: ");
  Serial.print(our_nunchuk.zButton, DEC);
  Serial.print("\tC_b: ");
  Serial.print(our_nunchuk.cButton, DEC);
}

void controlServo()
{
  //  Para evitar reposicionamiento constante del servo debido a pequeños
  //  temblores al sostenerlo:
  if( (abs(our_nunchuk.accelX-direccion) > 75) )
    direccion=our_nunchuk.accelX;               // [261,725]
  
  int val_servo= map(direccion, 261,725,0,180); // [261,725] -> [0,180]
  our_servo.write(val_servo);                   
}

void controlDC()
{
   bool m_i;
   bool m_d;
   
   int velocidad=map(our_nunchuk.accelY, 272,706,-255,+255);  // [-+255]
   
   if(velocidad<0)  // Sentido de giro
   { 
     m_i=0;
     m_d=1;
   }
   
   else             // Otro sentido de giro
   {
     m_i=1;
     m_d=0;
   }
   
   digitalWrite(mi, m_i);
   digitalWrite(md, m_d);
   analogWrite(pwm, abs(velocidad));
   // Importante el detalle del abs(), es fácil olvidar que
   // analogWrite solo admite valores comprendidos en [0,+255]
}
