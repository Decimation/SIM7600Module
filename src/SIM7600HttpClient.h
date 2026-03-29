// HttpClient.h

// ReSharper disable CppInconsistentNaming
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
enum class HttpPara
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

static const size_t MAP_SIZE = static_cast<size_t>(HttpPara::COUNT);

class HttpClient : public ClientManager<HttpClient, SIM7600_HTTP_MAX_CLIENTS>
{
public:
	HttpClient();
	HttpClient(Modem* m);
	~HttpClient();

	Status setModem(Modem* const modem);

	Status connect();
	Status disconnect();
	Status addPara(HttpPara, const char*);

private:
	Modem* _modem;
	char*  _tx_buf;
	char*  _rx_buf;
};


#define AddMapEntryS(e, s) {e, #s}
#define AddMapEntry(e) AddMapEntryS(e,e)

static const arx::stdx::map<HttpPara, const char*, MAP_SIZE> paras_dict =
{
	AddMapEntry(HttpPara::URL),
	AddMapEntryS(HttpPara::ConnectTimeout, "CONNECTTO"),
	AddMapEntryS(HttpPara::ReceiveTimeout, "RECVTO"),
	AddMapEntryS(HttpPara::ContentType, "CONTENT"),
	AddMapEntry(HttpPara::Accept),
	AddMapEntryS(HttpPara::UserAgent, "UA"),
	AddMapEntry(HttpPara::SslCfg),
	AddMapEntry(HttpPara::UserData),
	AddMapEntry(HttpPara::Break),
	AddMapEntry(HttpPara::BreakEnd),
	AddMapEntryS(HttpPara::RespTimeout, "RESPTO"),
};

const char* ParaToString(HttpPara para);
}
