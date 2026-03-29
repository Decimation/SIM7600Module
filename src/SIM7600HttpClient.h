// SIM7600HttpClient.h

// ReSharper disable CppInconsistentNaming
#pragma once

#include "SIM7600Common.h"
#include "SIM7600ClientManager.h"
#include "SIM7600Modem.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

namespace SIM7600
{
class SIM7600HttpClient : public ClientManager<SIM7600HttpClient, SIM7600_HTTP_MAX_CLIENTS>
{
public:
	SIM7600HttpClient();
	SIM7600HttpClient(Modem* m);
	~SIM7600HttpClient();

	Status setModem(Modem* const modem);

	Status init();
	Status disconnect();

private:
	Modem* _modem;
	char*  _tx_buf;
	char*  _rx_buf;
};
}
