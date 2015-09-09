#include "RenderWindow.h"
#include <QString>

#include "FreEngine.h"
#include "RDMethods.h"
#include "FreProfiler.h"

RenderWindow::RenderWindow()
{
	FRE::PixelFormatInfo formatInfo = FRE::RDGetPixelFormatInfo(FRE::EPixelFormat::BGRA8);
    
	_renderTarget = CreateRenderOutput(*this);
	QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(Draw()));
	_timer.start(0);
}

RenderWindow::~RenderWindow()
{

}

void RenderWindow::resizeEvent(QResizeEvent * resizeEvent)
{
	if (_renderTarget)
	{
		auto & size = resizeEvent->size();
		_renderTarget->SetSize(size.width(), size.height());
	}
}

void RenderWindow::Draw()
{
	//CPU_PROFILE_START(FPS);

	FRE::RDBeginFrame();
	FRE::RDBeginDrawing(_renderTarget);
	FRE::RDClear(true, FRE::Color(1.0f, 0.0f, 0.0f, 1.0f), true, 0.0f, false, 0);
	FRE::RDEndDrawing(true);
	FRE::RDEndFrame();

	//CPU_PROFILE_STOP(FPS);
	ShowFps();
}

FRE::RDRenderOutputRef RenderWindow::CreateRenderOutput(QWidget & widget)
{
	FRE::DarkParams targetParams;
	targetParams.params[0] = widget.winId();
	return FRE::RDCreateSurfaceRenderOutput(targetParams);
}

void RenderWindow::ShowFps()
{
	QString strFps;
	strFps.sprintf("Fps %i", GetFrameFps());
	setWindowTitle(strFps);
}

int RenderWindow::GetFrameFps() const
{
	//auto fps = FRE::Utils::Profiler::GetTime(0, "FPS");
	//return 1.0 / fps.Avg;
	return 0;
}
