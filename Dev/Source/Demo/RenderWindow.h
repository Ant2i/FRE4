#pragma once

#include <QWidget>
#include <QResizeEvent>
#include <QTimer>

#include "FreReleaser.h"
#include <memory>

namespace FRE
{
	class RI_RenderTarget;
}

class RenderWindow : public QWidget
{
	Q_OBJECT
public:
	RenderWindow();
	virtual ~RenderWindow();

public slots:
	void Draw();

protected:
	virtual void resizeEvent(QResizeEvent *) override;

private:
	static FRE::RI_RenderTarget * CreateRenderTarget(QWidget & widget);
	std::unique_ptr<FRE::RI_RenderTarget, Releaser<FRE::RI_RenderTarget>> _renderTarget;
	QTimer _timer;

	 void ShowFps();
	 int GetFrameFps() const;
};