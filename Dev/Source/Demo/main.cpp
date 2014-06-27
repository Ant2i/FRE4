#include <QApplication>

#include "Engine.h"
#include "RenderWindow.h"

int main(int argc, char *argv[])
{
	FRE::Engine::CreateParams params;
	params.renderDeviceName = "GLRenderDevice";
	FRE::Engine::Create(params);

	int result = 0;
	{
		QApplication app(argc, argv);
		RenderWindow window;
		window.resize(320, 240);
		window.show();
		window.setWindowTitle("FRE Demo");

		result = app.exec();
	}

	FRE::Engine::Destroy();

	return result;
}