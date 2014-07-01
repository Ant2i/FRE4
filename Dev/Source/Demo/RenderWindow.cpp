#include "RenderWindow.h"

#include "FreEngine.h"
#include "FreDeviceInterfaces.h"

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
	auto render = FRE::Engine::ActiveRenderDevice();
	if (render)
	{
		render->BeginFrame(_renderTarget.get());
		render->EndFrame();
	}
}

FRE::IRenderTarget * RenderWindow::CreateRenderTarget(QWidget & widget)
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