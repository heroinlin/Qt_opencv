#include "opencv_qt.h"
#include <QtWidgets/QApplication>
#include "cv.h"
#include "highgui.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	opencv_Qt w;
	/*cvNamedWindow("Plant", CV_WINDOW_AUTOSIZE);
	IplImage* img = NULL;
	img = cvLoadImage(argv[1]);
	cvShowImage("Plant", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Plant");*/
	w.show();
	return a.exec();
}
