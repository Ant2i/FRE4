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
		window.setWindowTitle("FRE Demo");
		window.show();
		
		result = app.exec();
	}

	FRE::Engine::Destroy();

	return result;
}