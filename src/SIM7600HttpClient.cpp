// ReSharper disable CppInconsistentNaming
// ReSharper disable CppPossiblyUninitializedMember
#include "SIM7600HttpClient.h"
#include "SIM7600Log.h"
#include "SIM7600Common.h"

static const char* tag = "HttpClient";


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
	return {};
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
	return {};
}

Status HttpClient::readHead(uint8_t* outBuf, size_t* outBufLen)
{
	auto res = _modem->sendATCmdAndWaitResp("AT+HTTPHEAD", "+HTTPHEAD:");

	if (res != Status::Success) {
		SIM7600_LOGD(tag, "Send: %s", statusToString(res));
		return res;
	}
	auto status = _modem->parseLine(_rx_buf, 1, "+HTTPHEAD: DATA,%d", &outBufLen);

	if (status != Status::Success) {
		SIM7600_LOGD(tag, "Parse: %s", statusToString(status));
		return status;
	}

	SIM7600_LOGI(tag, "Head len: %d", *outBufLen);

	size_t bRead;
	auto   rb = _modem->readBytes(outBuf, *outBufLen, *outBufLen, bRead);
	SIM7600_LOGI(tag, "Head read: %s", statusToString(rb));

	return rb;
}

Status HttpClient::addParameter(const HttpParameter para, const char* val) const
{
	auto   string = parameterToString(para);
	Status status   = _modem->sendATCmd(R"(AT+HTTPPARA="%s","%s")", string, val);

	if (status != Status::Success) {
		SIM7600_LOGD(tag, "addParameter [%s] -> send: %s", string, statusToString(status));
		return status;
	}

	return status;
}

const char* parameterToString(const HttpParameter para)
{
	const auto f = HttpParasMap.find(para);

	return f->second;
}
}
