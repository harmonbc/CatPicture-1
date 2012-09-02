#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
  private:
	  Surface* mySurface_; //Surface with pixel array

	  //Track frames
	int frame_number_;
	boost::posix_time::ptime app_start_time_;

	
	struct triangle_info{
		int height;
		int base;
		int corner;
	};

	//Width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024; //Must be the next power of 2 bigger or equal to app dimensions

	/**
	 * Draws rectangle on the canvas 
	 *
	 * TODO
	 *
	 * Satisfies requirement A.1
	 */
	void placeRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2, int rect_width, int rect_height, Color8u border);

	/**
	 * Places a bunch of lines forming an asterisk where the cursor clicks 
	 *
	 * TODO Describe the logic
	 *
	 * Satisfies requirement A.3
	 *
	 */
	void drawLine(uint8_t* pixels, int x1, int y1, int x2, int y2);

	/**
	 * Draws a Sierpinski triangle on the surface
	 *
	 * TODO Describe the logic
	 *
	 * Satisfies requirement A.7
	 *
	 */
	void placeTriangle(uint8_t* pixels, int iterations);

	/**
	 * Places a circle where the click occurs
	 *
	 * TODO Describe the logic
	 *
	 */
	void placeCircle(uint8_t* pixels, int x1, int y1, int x2, int y2, int rect_width, int rect_height, Color8u fill1, Color8u border1, Color8u fill2, Color8u border2);

	/**
	 * Blurs edges of image
	 *
	 * TODO Describe the logic
	 *
	 */
	void blurEdges(uint8_t* image_to_blur, uint8_t* blur_pattern);

	/**
	*	Returns x value from pixel array
	*/
	int xConverter(uint8_t* pixels);
	
	/**
	*	Returns y value from pixel array
	*/
	int yConverter(uint8_t* pixels);
};

void CatPictureApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::placeRectangle(uint8_t* pixels, int startx, int starty, int endx, int endy, int rect_width, int rect_height, Color8u border){
	int colorNoter = 0;
	int currentY;
	int currentX;
	bool in_horiz_border;
	bool in_vert_border; 
	int x_distance_from_start;
	int y_distance_from_start;
	int rectHeight = endy - starty;
	int rectLength = endx - startx;
	int rects_along;
	int rect_col;
	int rects_tall;
	int rect_row;

	for (currentY = starty; currentY<=endy; currentY++){
		y_distance_from_start = currentY - starty;
		rects_tall = y_distance_from_start%rectHeight;
		rect_row = y_distance_from_start%rectLength;
		in_horiz_border = (rect_row == 0 || rect_row == rect_height-1);			
		for(currentX = startx; currentX <= endx; currentX++){
			x_distance_from_start = currentX - starty;
			rects_along = x_distance_from_start/rect_width;

			rect_col = x_distance_from_start/rect_width;
			in_vert_border = (rect_col == 0 || rect_col == rect_width-1);
			if(in_horiz_border || in_vert_border){
				pixels[3*(currentX + currentY*kTextureSize)] = border.r;
				pixels[3*(currentX + currentY*kTextureSize)+1] = border.g;
				pixels[3*(currentX + currentY*kTextureSize)+2] = border.b;
			}
		}
	}
}
	


void CatPictureApp::setup()
{
	mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	uint8_t* dataArray = (*mySurface_).getData();
	for (int i = 0; i < 1000; i+=10){
		for (int j = 0; j < 500; j += 50){
			placeRectangle(dataArray,5+i,10+j,100+i,100+j*2,2,90,Color8u(120,129,29));
		}
	}
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
}

void CatPictureApp::draw()
{
	// Draw the surface 
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
