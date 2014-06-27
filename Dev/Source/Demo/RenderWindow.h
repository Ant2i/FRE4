#pragma once

#include <QWidget>
#include <QResizeEvent>
#include <QTimer>

#include "Releaser.h"
#include <memory>

namespace FRE
{
	class IRenderTarget;
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
	static FRE::IRenderTarget * CreateRenderTarget(QWidget & widget);
	std::unique_ptr<FRE::IRenderTarget, Releaser<FRE::IRenderTarget>> _renderTarget;
	QTimer _timer;
};