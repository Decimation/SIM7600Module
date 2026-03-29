// HttpClient.h

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
class HttpClient : public ClientManager<HttpClient, SIM7600_HTTP_MAX_CLIENTS>
{
public:
	HttpClient();
	HttpClient(Modem* m);
	~HttpClient();

	Status setModem(Modem* const modem); 

	Status connect();
	Status disconnect();

private:
	Modem* _modem;
	char*  _tx_buf;
	char*  _rx_buf;
};
}
