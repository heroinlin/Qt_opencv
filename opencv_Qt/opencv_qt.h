#ifndef OPENCV_QT_H
#define OPENCV_QT_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QPainter>
#include "ui_opencv_qt.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
class opencv_Qt : public QMainWindow
{
	Q_OBJECT

public:
	opencv_Qt(QWidget *parent = 0);
	~opencv_Qt();

private:
	Ui::opencv_QtClass ui;
	cv::Mat image;  // cvͼƬ 
	CvCapture *g_capture;
	QLabel *label = new QLabel(this);
	QImage img;

private slots:
	void on_LoadImage_clicked();
	void on_LoadVideo_clicked();
	void on_Process_clicked();
	void on_SaveImage_clicked();
	void videoplayer(CvCapture* capture);
	void opencv_Qt::Addword2Image();
};

#endif // OPENCV_QT_H
