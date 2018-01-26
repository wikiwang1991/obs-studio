#include "interface.h"
#include "protocol.h"
#include <QTcpSocket>
#include "obs-app.hpp"
#include "window-basic-main.hpp"

struct AddSourceData {
	obs_source_t *source;
	bool visible;
};

static OBSBasic *main = 0;

static void AddSource(void *_data, obs_scene_t *scene)
{
	AddSourceData *data = (AddSourceData *)_data;
	obs_sceneitem_t *sceneitem;

	sceneitem = obs_scene_add(scene, data->source);
	obs_sceneitem_set_visible(sceneitem, data->visible);
}

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
		case Configure: {
			int len = sizeof(Msg) + sizeof(ConfigParam);
			if (buf.length() < len) return;
			const ConfigParam *config = reinterpret_cast<const ConfigParam *>(msg->params);
			len += config->url.size;
			if (buf.length() < len) return;

			main->CreateDefaultScene(true);
			int width = config->width, height = config->height;
			{
				obs_source_t *source = obs_source_create("monitor_capture", "Display Capture", NULL, nullptr);
				OBSData settings = obs_source_get_settings(source);
				obs_properties_t *properties = obs_source_properties(source);
				obs_property_t *property = obs_properties_get(properties, "monitor");
				long long val = obs_property_list_item_int(property, config->moniter);
				obs_data_set_int(settings, "monitor", val);
				obs_source_update(source, settings);
				obs_property_modified(property, settings);

				if (!(width && height)) {
					const char *name = obs_property_list_item_name(property, config->moniter);

					char display[8];
					int idx = -1, cx, cy, x, y;
					sscanf(name, "%s %d: %ldx%ld @ %ld,%ld", display, &idx, &cx, &cy, &x, &y);
					assert(idx == config->moniter);

					if (!width) width = cx;
					if (!height) height = cy;
				}

				OBSScene scene = main->GetCurrentScene();

				AddSourceData data;
				data.source = source;
				data.visible = true;

				obs_enter_graphics();
				obs_scene_atomic_update(scene, AddSource, &data);
				obs_leave_graphics();
			}
			{
				config_t *basicConfig = main->Config();

				config_set_uint(basicConfig, "Video", "BaseCX", width);
				config_set_uint(basicConfig, "Video", "BaseCY", height);
				config_set_uint(basicConfig, "Video", "OutputCX", width);
				config_set_uint(basicConfig, "Video", "OutputCY", height);

				config_set_uint(basicConfig, "Video", "FPSType", 2);
				config_set_uint(basicConfig, "Video", "FPSNum", config->fpsNum);
				config_set_uint(basicConfig, "Video", "FPSDen", config->fpsDen);

				main->ResetVideo();
			}
			{
				obs_data_t *settings = obs_service_defaults("rtmp_custom");
				obs_data_set_string(settings, "server", config->url.data);

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
			}

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
