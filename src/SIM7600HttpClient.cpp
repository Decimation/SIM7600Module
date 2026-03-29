// ReSharper disable CppInconsistentNaming
#include "SIM7600HttpClient.h"
#include "SIM7600Log.h"


namespace SIM7600
{
SIM7600HttpClient::SIM7600HttpClient() : SIM7600HttpClient(nullptr)
{
}

SIM7600HttpClient::SIM7600HttpClient(Modem* m) : _modem(m)
{
}

SIM7600HttpClient::~SIM7600HttpClient()
{
	disconnect();
}

Status SIM7600HttpClient::disconnect()
{
	
}

Status SIM7600HttpClient::setModem(Modem* const modem)
{
	if (modem == nullptr) return Status::InvalidModem;

	SIM7600_LOGI(tag, "Setting modem for client %u", _client_id);

	_modem  = modem;
	_tx_buf = _modem->_tx_buf;
	_rx_buf = _modem->_rx_buf;

	return Status::Success;
}
}
