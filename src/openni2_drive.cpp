/*************************
OpenNI2 Deep, Color and Fusion Image
Author: Xin Chen, 2013.2
Blog: http://blog.csdn.net/chenxin_130
*************************/

#include <stdlib.h>
#include <iostream>
#include <string>
#include "OpenNI.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
using namespace openni;

void CheckOpenNIError( Status result, string status )
{ 
	if( result != STATUS_OK ) 
		cerr << status << " Error: " << OpenNI::getExtendedError() << endl;
}

int main( int argc, char** argv )
{
	Status result = STATUS_OK;  
    
	//OpenNI2 image
	VideoFrameRef oniDepthImg;
    VideoFrameRef oniColorImg;

	//OpenCV image
	cv::Mat cvBGRImg;
	Mat color,depth;
	char key = 0 ;
	char Saverbg[256],Savedepth[256];
	int imagecount=0;

	//【1】
	// initialize OpenNI2
    result = OpenNI::initialize();
	CheckOpenNIError( result, "initialize context" );  

	// open device  
	Device device;
    result = device.open( openni::ANY_DEVICE );

   
	//【2】
	// create depth stream 
    VideoStream oniDepthStream;
    result = oniDepthStream.create( device, openni::SENSOR_DEPTH );
   CheckOpenNIError( result, "create depth" );
	//【3】
	// set depth video mode
		VideoMode modeDepth;
		modeDepth.setResolution( 512, 424);
    modeDepth.setFps( 30 );
    modeDepth.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );
    oniDepthStream.setVideoMode(modeDepth);
	// start depth stream
    result = oniDepthStream.start();
  CheckOpenNIError( result, "start depth" );

	 // create color stream
    VideoStream oniColorStream;
    result = oniColorStream.create( device, openni::SENSOR_COLOR );
    CheckOpenNIError( result, "create color" );

	// set color video mode
	 VideoMode modeColor;
		modeColor.setResolution( 640, 480);
    modeColor.setFps( 30 );
    modeColor.setPixelFormat( PIXEL_FORMAT_RGB888 );
    oniColorStream.setVideoMode( modeColor);
    // start color stream
      result = oniColorStream.start();
   CheckOpenNIError( result, "start color" );

//【4】
	// set depth and color imge registration mode
	if( device.isImageRegistrationModeSupported(IMAGE_REGISTRATION_DEPTH_TO_COLOR ) )
	{
		device.setImageRegistrationMode( IMAGE_REGISTRATION_DEPTH_TO_COLOR );
	}

	// 创建OpenCV图像窗口
	//namedWindow("image", CV_WINDOW_AUTOSIZE);
	//namedWindow("depth", CV_WINDOW_AUTOSIZE);

	while( true )
	{  
			if( oniDepthStream.readFrame( &oniDepthImg ) == STATUS_OK )
			{
				cv::Mat cvRawImg16U( oniDepthImg.getHeight(), oniDepthImg.getWidth(), CV_16UC1, (void*)oniDepthImg.getData() );
				//【5】
				//resize( cvRawImg16U, depth, Size(640, 360));
				cv::imshow( "depth",cvRawImg16U);
			}
		// read frame
		if( oniColorStream.readFrame( &oniColorImg ) == STATUS_OK )
		{
			// convert data into OpenCV type
			cv::Mat cvRGBImg( oniColorImg.getHeight(), oniColorImg.getWidth(), CV_8UC3, (void*)oniColorImg.getData() );
			cv::cvtColor( cvRGBImg, cvBGRImg, CV_RGB2BGR );
			//resize(cvBGRImg , color, Size(640, 360));
			cv::imshow( "image", cvBGRImg);
		}
		key=cvWaitKey(10);
		if (key == 13)
										{
											 imagecount++;
											 sprintf(Saverbg,"/home/bobo/code/kinect2_drive/data/rgb_png/%01d.png",imagecount);
											 sprintf(Savedepth,"/home/bobo/code/kinect2_drive/data/depth_png/%01d.png",imagecount);
											 imwrite(Saverbg,depth);
											 imwrite(Savedepth,color);
										}
		// 终止快捷键
		if (key == 27)
			break;
	}

    //OpenNI2 destroy
    oniDepthStream.destroy();
    oniColorStream.destroy();
    device.close();
    OpenNI::shutdown();

	return 0;
}

