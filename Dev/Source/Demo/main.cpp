#include <QApplication>

#include "FreEngine.h"
#include "RenderWindow.h"
#include "FAssert.h"

#include <algorithm>
#include <vector>
#include <stdio.h>

int main(int argc, char *argv[])
{
	F_ASSERT(true);

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