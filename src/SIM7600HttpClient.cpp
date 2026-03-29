// ReSharper disable CppInconsistentNaming
// ReSharper disable CppPossiblyUninitializedMember
#include "SIM7600HttpClient.h"
#include "SIM7600Log.h"


static const char* tag = "HttpClient";


namespace SIM7600
{
HttpClient::HttpClient() : HttpClient(nullptr)
{
}

HttpClient::HttpClient(Modem* m) : _modem(m)
{
}

HttpClient::~HttpClient()
{
	disconnect();
}

Status HttpClient::disconnect()
{
}


Status HttpClient::setModem(Modem* const modem)
{
	if (modem == nullptr) return Status::InvalidModem;

	SIM7600_LOGI(tag, "Setting modem for client %u", _client_id);

	_modem  = modem;
	_tx_buf = _modem->_tx_buf;
	_rx_buf = _modem->_rx_buf;

	return Status::Success;
}

Status HttpClient::connect()
{
}

Status HttpClient::addPara(HttpPara para, const char* val)
{
	Status status;
	status = _modem->sendATCmd("AT+HTTPPARA=\"%s\",\"%s\"", ParaToString(para), val);
	if (status != Status::Success) return status;

	return status;
}

const char* ParaToString(const HttpPara para)
{
	auto f = paras_dict.find(para);

	return (*f).second;
}
}
