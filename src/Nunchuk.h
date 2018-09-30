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

#ifndef Nunchuk_H

#define Nunchuk_H
#include <Arduino.h>

class Nunchuk
{
	public:
		int analogX;	// Byte 0 	Joystick
		int analogY;
		
		int accelX;		// Byte 1	Acelerómetro
		int accelY;
		int accelZ;
		
		int last_byte;	// Byte 5	AZ<1:0>	AZ<1:0>	AZ<1:0>	BC BZ
		
		bool zButton;	// Botones
		bool cButton;
		
		void init();	// Prepara el Nunchuk para la transmisión
		void update();	// Actualiza variables miembro de Nunchuk
	
	private:
		void _sendByte(byte registro, byte dato);
};

#endif
