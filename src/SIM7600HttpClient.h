// HttpClient.h

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppRedundantCastExpression
#pragma once

#include <new>

#include "SIM7600Common.h"
#include "SIM7600ClientManager.h"
#include "SIM7600Modem.h"
#include <stdlib.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#ifdef TARGET_AVR
#include <ArxContainer.h>
#endif
#include <new.h>


namespace SIM7600
{
enum class HttpParameter
{
	URL,
	ConnectTimeout,
	ReceiveTimeout,
	ContentType,
	Accept,
	UserAgent,
	SslCfg,
	UserData,
	Break,
	BreakEnd,
	RespTimeout,
	COUNT
};

static const size_t MAP_SIZE = static_cast<size_t>(HttpParameter::COUNT);

class HttpClient : public ClientManager<HttpClient, SIM7600_HTTP_MAX_CLIENTS>
{
public:
	HttpClient();
	explicit HttpClient(Modem* m);
	~HttpClient();

	Status setModem(Modem* const modem);

	Status connect();
	Status disconnect();
	Status addPara(HttpParameter, const char*);
	Status HttpClient::readHead(uint8_t* outBuf, size_t* outBufLen);

private:
	Modem* _modem;
	char*  _tx_buf;
	char*  _rx_buf;
};


static const arx::stdx::map<HttpParameter, const char*, MAP_SIZE> paras_dict =
{
	AddMap_K(HttpParameter::URL),
	AddMap_KS(HttpParameter::ConnectTimeout, "CONNECTTO"),
	AddMap_KS(HttpParameter::ReceiveTimeout, "RECVTO"),
	AddMap_KS(HttpParameter::ContentType, "CONTENT"),
	AddMap_K(HttpParameter::Accept),
	AddMap_KS(HttpParameter::UserAgent, "UA"),
	AddMap_K(HttpParameter::SslCfg),
	AddMap_K(HttpParameter::UserData),
	AddMap_K(HttpParameter::Break),
	AddMap_K(HttpParameter::BreakEnd),
	AddMap_KS(HttpParameter::RespTimeout, "RESPTO"),
};

const char* ParaToString(HttpParameter para);
}
