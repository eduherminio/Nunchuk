/* Author: 		Eduardo Cáceres de la Calle
 * Subject: 	Sistemas Digitales Avanzados (SDA)
 * Degree: 		Industrial Electronics and Automatic Control Engineering
 * University:	Universidad de Valladolid (UVa) - EII
 *
 * Code written in 2016, during my first contact with Arduino.
 * Uploaded for educational purposes only, don't be too hard on me :)
 * 
 */

/*  Librería que permite controlar un motor y un servomotor usando
 *	un nunchuk.
 *  4/06/16
 *
 * Desarrollada sobre:
 *
 * Nunchuk.h – Librería para controlar el nunchuk.
 *
 * Copyright 2016
 *
 *
 * Basada en:
 * http://www.windmeadow.com/node/42
 * http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 * http://wiibrew.org/wiki/Wiimote/Extension_Controllers
 *
 */

using namespace std;

#include <Arduino.h>
#include <Wire.h>
#include "Nunchuk.h"
#define ADDRESS 0x52

void Nunchuk::init()	// Prepara al Nunchuk para la transmisión
{
	Wire.begin();
	Nunchuk::_sendByte(0xF0, 0x55);
	Nunchuk::_sendByte(0xFB, 0x00);
	Nunchuk::update();
}

void Nunchuk::update()	// Actualiza variables miembro de Nunchuk
{
	int count = 0;
	int valores[6];		// Bytes que recibirá del Nunchuk: 5
	Wire.requestFrom(ADDRESS, 6);
	
	while(Wire.available())
	{
		valores[count] = Wire.read();
		count++;
	}
	
	
	analogX = valores[0];	// Lectura valores joystick.
	analogY= valores[1];
	
	accelX= valores[2];		// Lectura valores del acelerómetro
	accelY= valores[3];
	accelZ= valores[4];
	
	accelX= accelX<<2;		// Hacemos hueco para dos bits más
	accelY=accelY<<2;
	accelZ=accelZ<<2;
	
	last_byte= valores[5];	// Lectura último byte
	
	zButton= (last_byte & 0x01);	// Extracción bit 8
	zButton^=1;				// Nivel bajo -> Nivel alto
	
	cButton= (last_byte & 0x02);	// Extracción bit 7
	cButton^=1;				// Nivel bajo -> Nivel alto
	
	// 	Extracción de dos últimos bits cada vez, tras descartar
	//	2, 4 y 6 respectivamente por la derecha
	accelX+= (last_byte>>2) & 0x03;
	accelY+= (last_byte>>4) & 0x03;
	accelZ+= (last_byte>>6) & 0x03;
	
	Nunchuk::_sendByte(0x00, 0x00);
}

void Nunchuk::_sendByte(byte registro, byte dato)
{
	Wire.beginTransmission(ADDRESS);
	Wire.write(registro);	// Escribe en el buffer
	Wire.write(dato);		// Escribe en el buffer
	Wire.endTransmission();	// Manda el buffer, finaliza com.
	delay(10);
}
