#pragma once

#include <QTcpServer>

class Interface : public QTcpServer {
public:
	Interface();

private:
	void incomingConnection(qintptr socketDescriptor) override;
};
