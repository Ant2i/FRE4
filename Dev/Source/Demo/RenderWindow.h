#pragma once

#include <QWidget>
#include <QResizeEvent>
#include <QTimer>

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
	static FRE::RDRenderOutputRef CreateRenderOutput(QWidget & widget);
	FRE::RDRenderOutputRef _renderTarget;
	QTimer _timer;

	 void ShowFps();
	 int GetFrameFps() const;
};