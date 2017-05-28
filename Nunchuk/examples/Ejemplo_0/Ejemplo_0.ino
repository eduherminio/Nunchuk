/* Author: 		Eduardo Cáceres de la Calle
 * Subject: 	Sistemas Digitales Avanzados (SDA)
 * Degree: 		Industrial Electronics and Automatic Control Engineering
 * University:	Universidad de Valladolid (UVa) - EII
 *
 * Code written in 2016, during my first contact with Arduino.
 * Uploaded for educational purposes only, don't be too hard on me :)
 * 
 */

/*
 *  Ejemplo que ilustra el uso de la librería de creación propia controlrgb.
 *	Hace que el RGB alterne entre sus colores primarios (rojo, verde, azul)
 *	con un período de t segundos.
 *	19/05/16
*/

#include <Wire.h>
#include <Nunchuk.h>
#define BAUDRATE 19200
Nunchuk nunchuk;
void setup()
{
Serial.begin(BAUDRATE);
nunchuk.init();
}
void loop()
{
nunchuk.update();
Serial.println(nunchuk.analogX, DEC);
}
