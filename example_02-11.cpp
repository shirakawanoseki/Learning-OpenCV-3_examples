// Example 2-11. A complete program to read in a color video and write out the log-polar-
// transformed video

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/types_c.h"
#include <iostream>


void help(char** argv ) {
	std::cout << "\n"
	<< "Read in a video, write out a log polar of it\n"
	<< argv[0] <<" <path/video> <paht/video_output>\n"
	<< "For example:\n"
	<< argv[0] << " ../tree.avi ../vout.avi\n"
	<< "\nThen read it with:\n ./example_02-10 ../vout.avi\n"
	<< std::endl;
}
	

int main( int argc, char** argv ) {
	
	if (argc != 3) {
		help(argv);
		return 0;
	}
		

  cv::namedWindow( "Example 2-11", cv::WINDOW_AUTOSIZE );
  cv::namedWindow( "Log_Polar", cv::WINDOW_AUTOSIZE );

  // ( Note: could capture from a camera by giving a camera id as an int.)
  //

  cv::VideoCapture capture( argv[1] );
  double fps = capture.get( 5 );
  cv::Size size(
    (int)capture.get( 3 ),
    (int)capture.get( 4 )
  );

  cv::VideoWriter writer;
  writer.open( argv[2], cv::VideoWriter::fourcc('M','J','P','G'), fps, size );

  cv::Mat logpolar_frame, bgr_frame;

  for(;;) {

    capture >> bgr_frame;
    if( bgr_frame.empty() ) break; // end if done

    cv::imshow( "Example 2-11", bgr_frame );

    cv::logPolar(
      bgr_frame, // Input color frame
      logpolar_frame, // Output log-polar frame
      cv::Point2f( // Centerpoint for log-polar transformation
        bgr_frame.cols/2, // x
        bgr_frame.rows/2 // y
      ),
      40, // Magnitude (scale parameter)
      CV_WARP_FILL_OUTLIERS // Fill outliers with 'zero'
    );

    cv::imshow( "Log_Polar", logpolar_frame );

    writer << logpolar_frame;

    char c = cv::waitKey(10);

    if( c == 27 ) break; // allow the user to break out

  }

  writer.release();
  capture.release();

}
