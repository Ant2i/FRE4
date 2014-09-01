#pragma once

#include <QWidget>
#include <QResizeEvent>
#include <QTimer>

#include "FreReleaser.h"
#include "FreRDResources.h"

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
	static FRE::RenderTargetRef CreateRenderTarget(QWidget & widget);
	FRE::RenderTargetRef _renderTarget;
	QTimer _timer;

	 void ShowFps();
	 int GetFrameFps() const;
};