#include "interface.h"
#include "protocol.h"
#include <QTcpSocket>
#include "obs-app.hpp"
#include "window-basic-main.hpp"

static OBSBasic *main = 0;

class Client : public QTcpSocket {
	Q_OBJECT
public:
	Client();
    
private slots:
	void read();

private:
	QByteArray buf;
};

Interface::Interface()
{
	main = static_cast<OBSBasic *>(App()->GetMainWindow());
//	listen();
	listen(QHostAddress::Any, 666);
}

void Interface::incomingConnection(qintptr socketDescriptor)
{
	QTcpSocket *socket = new Client;
	connect(socket, SIGNAL(disconnected()), SLOT(deleteLater()));
	socket->setSocketDescriptor(socketDescriptor);
}

Client::Client()
{
	connect(this, SIGNAL(readyRead()), SLOT(read()));
}

using namespace ObsRpc;

void Client::read()
{
	buf.append(readAll());

	while (!buf.isEmpty()) {
		const Msg *msg = reinterpret_cast<const Msg *>(buf.constData());
		switch (msg->function) {
		case SetUrl: {
			int len = sizeof(Msg) + sizeof(String);
			if (buf.length() < len) return;
			const String *url = reinterpret_cast<const String *>(msg->params);
			len += url->size;
			if (buf.length() < len) return;

			obs_data_t *settings = obs_service_defaults("rtmp_custom");
			obs_data_set_string(settings, "server", url->data);

			obs_service_t *oldService = main->GetService();
			obs_data_t *hotkeyData = obs_hotkeys_save_service(oldService);

			obs_service_t *newService = obs_service_create("rtmp_custom",
				"default_service", settings,
				hotkeyData);

			obs_data_release(settings);
			obs_data_release(hotkeyData);

			main->SetService(newService);
			main->SaveService();
			obs_service_release(newService);
			
			buf.remove(0, len);
			break;
		} case StartStreaming:
			main->StartStreaming();
			buf.remove(0, sizeof(Msg));
			break;
		case StopStreaming:
			main->StopStreaming();
			buf.remove(0, sizeof(Msg));
			break;
		default: disconnect(); return;
		}
	}
}

#include "interface.moc"
