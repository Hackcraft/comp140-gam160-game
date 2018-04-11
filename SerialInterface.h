#pragma once

#include <serial/serial.h>
#include <string>

class SerialInterface
{
public:
	SerialInterface();
	~SerialInterface();

	void send(std::string msg);
	void getPositions();

	int getPosX() { return posX; };
	int getPosY() { return posY; };

	void setPosX(unsigned int x) { posX = x; };
	void setPosY(unsigned int y) { posY = y; };

	void close();

private:
	serial::Serial* mySerial;
	bool connected = false;

	int posX = 0;
	int posY = 0;
};

