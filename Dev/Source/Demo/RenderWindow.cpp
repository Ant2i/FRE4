#include "RenderWindow.h"

#include "Engine.h"
#include "DeviceInterfaces.h"

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
	if (FRE::Engine::GetInstance())
	{
		auto * renderDevice = FRE::Engine::GetInstance()->GetActiveRenderDevice();
		if (renderDevice)
		{
			FRE::DarkParams targetParams;
#ifdef _WIN32
			targetParams.params[0] = widget.winId();
#endif
			return renderDevice->CreateSurfaceRenderTarget(targetParams);
		}
	}
	return nullptr;
}