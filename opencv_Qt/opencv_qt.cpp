#include "opencv_qt.h"

int countFrames = 0;
int key;
int stopflag = 1;
int flag = 0;
bool flipflag = false;
int speed = 33;
opencv_Qt::opencv_Qt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_LoadImage_clicked()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(on_Process_clicked()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(on_LoadVideo_clicked()));
}

opencv_Qt::~opencv_Qt()
{

}
void opencv_Qt::on_LoadImage_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
	if (fileName != NULL)
	{
		/*image = cv::imread(fileName.toStdString().data());
		cv::namedWindow("Original Image");
		cv::imshow("Original Image", image);*/
		image = cv::imread(fileName.toStdString().data());
		cv::cvtColor(image, image, CV_BGR2RGBA);
		img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB32);
		label->move(10, 10);
		label->setPixmap(QPixmap::fromImage(img));
		label->resize(label->pixmap()->size());
		label->show();
	}
}
void opencv_Qt::on_LoadVideo_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Image Files (*.avi *.mp4 *.flv *.rmvb)"));
	if (fileName != NULL)
	{
		g_capture = cvCreateFileCapture(fileName.toStdString().data());
		videoplayer(g_capture);
	}
}
void opencv_Qt::on_Process_clicked()
{
	flipflag=!flipflag;
	cv::flip(image, image, 1);
	img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB32);
	//Addword2Image();
	label->setPixmap(QPixmap::fromImage(img));
	label->resize(label->pixmap()->size());
	label->show();
	/*cv::namedWindow("Output Image");
	cv::imshow("Output Image", image);*/
}
void opencv_Qt::on_SaveImage_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
	if (fileName != NULL)
	{ 
		//���ΪͼƬ��ѹ���ȡ�0/100
		int n = 100;
		//����ͼƬ
		img.save(fileName.toStdString().data(), "JPG", n);
		//cv::imwrite(fileName.toStdString().data(), image); 
	}
}
void opencv_Qt::Addword2Image()
{
	QPainter painter(&img);
	//���û�ˢģʽ
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	//�ı仭�ʺ�����
	QPen pen = painter.pen();
	pen.setColor(Qt::red);
	QFont font = painter.font();
	font.setBold(true);//�Ӵ�
	font.setPixelSize(30);//�ı������С
	painter.setPen(pen);
	painter.setFont(font);
	//�����ֻ�����ͼƬ����λ��
	painter.drawText(img.rect(), Qt::AlignCenter, "s  c  z");
}
void opencv_Qt::videoplayer(CvCapture* capture)
{
	//��ȡ��Ƶ����֡��
	int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	//�ڴ���show�ϴ�������ΪPosition�Ĺ�����
	while (countFrames < numFrames)
	{
		if (flag==1){break;}
		IplImage* frame = cvQueryFrame(capture);
		if (!frame) break;
		countFrames++;
		cvShowImage("videoplayer", frame);
		/************************************************************************/
		image = NULL;
		image = cv::Mat(frame, 1);
		if(flipflag==true)cv::flip(image, image, 1);//���淴ת
		cv::cvtColor(image, image, CV_BGR2RGBA);
		img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB32);
		label->move(10, 10);
		label->setPixmap(QPixmap::fromImage(img));
		label->resize(label->pixmap()->size());
		label->show();                                                              
		/************************************************************************/
		char savename[256];
		sprintf(savename, "./images/%07d.jpg", countFrames);
		if (stopflag == 1)
			key = cvWaitKey(speed);
		else key = cvWaitKey(0);
		switch (key)
		{
		case 27:{ flag = 1; break; }
		case 32:{ stopflag = !stopflag; break; }
		case 'c':{ countFrames -= 1; cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'C':{  countFrames -= 1;  cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'd':{ countFrames -= 2; if (countFrames < 0)countFrames = 0; cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'D':{ countFrames -= 2; if (countFrames < 0)countFrames = 0;  cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 's':{ cvSaveImage(savename, frame, 0); break; }
		case 'S':{ cvSaveImage(savename, frame, 0); break; }
		case 'o':{ speed += 10; break; }
		case 'i':{ speed -= 10; break; }
		case 'l':{ countFrames += 5; if (countFrames < numFrames) cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'L':{ countFrames += 5; if (countFrames < numFrames) cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		default:{}
		}
		//������ ������Ƶ�Ĳ��� �����ƶ�
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("videoplayer");
}
