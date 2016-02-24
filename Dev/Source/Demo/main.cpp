#include <QApplication>
#include <QSurfaceFormat>

#include "FreEngine.h"
#include "RenderWindow.h"
#include "FAssert.h"

#include <algorithm>
#include <vector>
#include <stdio.h>

#include "FStreamMemory.h"

int main(int argc, char *argv[])
{
	//MemoryStreamWriter wStream;
	//wStream << (int)5 << std::string("18973423942345342523");
 //   
 //   MemoryStreamReader rStream(wStream.Ptr(), wStream.Size());
 //   int i = 0;
	//std::string str1;
	//rStream >> i >> str1;

#if QT_VERSION > QT_VERSION_CHECK(5, 4, 0)
	QSurfaceFormat format = QSurfaceFormat::defaultFormat();
	format.setAlphaBufferSize(0);
	format.setDepthBufferSize(0);
	format.setStencilBufferSize(0);
	QSurfaceFormat::setDefaultFormat(format);
#endif

	F_ASSERT(true);
 
	FRE::Engine::CreateParams params;
	params.renderDeviceName = L"GLRenderDevice";
	FRE::Engine::Create(params);

	int result = 0;
	{
		QApplication app(argc, argv);
		//QWidget window;
		RenderWindow window;
		window.resize(320, 240);
		window.setWindowTitle("FRE Demo");
		window.show();
		
		result = app.exec();
	}

	FRE::Engine::Destroy();

	return result;
}
