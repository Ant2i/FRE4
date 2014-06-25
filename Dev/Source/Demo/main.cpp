#include <QApplication>
#include <QWidget>
#include "Engine.h"

int main(int argc, char *argv[])
{
	FRE::Engine::CreateParams params;
	params.renderDeviceName = "GLRenderDevice";
	FRE::Engine::Create(params);

	QApplication app(argc, argv);
	QWidget window;
	window.resize(320, 240);
	window.show();
	window.setWindowTitle("FRE Demo");
	int result = app.exec();

	FRE::Engine::Destroy();

	return result;
}