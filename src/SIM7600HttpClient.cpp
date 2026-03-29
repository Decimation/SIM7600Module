// ReSharper disable CppInconsistentNaming
// ReSharper disable CppPossiblyUninitializedMember
#include "SIM7600HttpClient.h"
#include "SIM7600Log.h"


static const char*  tag = "HttpClient";


namespace SIM7600
{
HttpClient::HttpClient() : HttpClient(nullptr)
{
}

HttpClient::HttpClient(Modem* m) : _modem(m)
{
	setModem(_modem);
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

Status HttpClient::readHead(uint8_t* outBuf, size_t* outBufLen)
{
	auto res = _modem->sendATCmdAndWaitResp("AT+HTTPHEAD", "+HTTPHEAD:");
	
	if (res != Status::Success) {
		SIM7600_LOGD(tag, "Send: %s", statusToString(res));
		return res;
	}
	auto status = _modem->parseLine(_rx_buf, 1, "+HTTPHEAD: DATA,%d", &outBufLen);
	
	if (status != Status::Success) 
	{
		SIM7600_LOGD(tag,"Parse: %s", statusToString(status));
		return status;
	}

	SIM7600_LOGI(tag, "Head len: %d", *outBufLen);
	
	size_t bRead;
	auto rb = _modem->readBytes(outBuf, *outBufLen, *outBufLen, bRead);
	SIM7600_LOGI(tag, "Head read: %s", statusToString(rb));

	return rb;
}

Status HttpClient::addPara(HttpParameter para, const char* val)
{
	Status status;
	status = _modem->sendATCmd("AT+HTTPPARA=\"%s\",\"%s\"", ParaToString(para), val);
	if (status != Status::Success) return status;

	return status;
}

const char* ParaToString(const HttpParameter para)
{
	auto f = paras_dict.find(para);

	return (*f).second;
}
}
