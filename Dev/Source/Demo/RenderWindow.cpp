#include "RenderWindow.h"
#include <QString>

#include "FreEngine.h"
#include "FreDeviceInterfaces.h"
#include "FreProfiler.h"

RenderWindow::RenderWindow()
{
	_renderTarget.reset(CreateRenderTarget(*this));

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
	CPU_PROFILE_START(FPS);

	auto device = FRE::Engine::ActiveRenderDevice();
	if (device)
	{
		device->BeginFrame(_renderTarget.get());
		//std::this_thread::sleep_for(std::chrono::milliseconds(17));
		device->EndFrame();
	}

	CPU_PROFILE_STOP(FPS);

	ShowFps();
}

FRE::RI_RenderTarget * RenderWindow::CreateRenderTarget(QWidget & widget)
{
	auto device = FRE::Engine::ActiveRenderDevice();
	if (device)
	{
		FRE::DarkParams targetParams;
		targetParams.params[0] = widget.winId();
		return device->CreateSurfaceRenderTarget(targetParams);
	}
	return nullptr;
}

void RenderWindow::ShowFps()
{
	QString strFps;
	strFps.sprintf("Fps %i", GetFrameFps());
	setWindowTitle(strFps);
}

int RenderWindow::GetFrameFps() const
{
	auto fps = FRE::Utils::Profiler::GetTime(0, "FPS");
	return 1.0 / fps.Avg;
}