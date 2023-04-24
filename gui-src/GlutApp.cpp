#include "GlutApp.h"
#include "glut_app.h"
#include "image_menu.h"

//137, 38, 199
GlutApp::GlutApp(int height, int width)
  : mHeight(height), mWidth(width), mMinX(-2.0), 
    mMaxX(2.0), mMinY(-2.0), mMaxY(2.0), mInteractionMode(IM_FRACTAL), mFractalMode(M_MANDELBROT),
    mMaxNumber(200), mColor1(252, 3, 132), mColor2(92, 34, 128), mColor3(36, 3, 252), mNumColor(32), mImageNumber(1), mActionData(mInputStream, mOutputStream){
  configureMenu(mMenuData);
  //mActionData.setGrid(new ComplexFractal);
  mA = -0.8;
  mB = 0.156;
  setColorTable();
  createFractal();



  // // read1
  // mOutputStream.clear();
  // mInputStream.clear();
  // mInputStream.str("pretty-mandel-1.ppm");
  // takeAction("read1", mMenuData, mActionData);
  
  // // copy
  // mOutputStream.clear();
  // mInputStream.clear();
  // mInputStream.str("");
  // takeAction("copy", mMenuData, mActionData);
}

void GlutApp::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}

int GlutApp::getHeight() const {
  return mHeight;
}
int GlutApp::getWidth() const {
  return mWidth;
}

void GlutApp::display() {
  if ( mInteractionMode == IM_FRACTAL ){
    PPM& p = mActionData.getOutputImage();
    double max = static_cast<double>(p.getMaxColorValue());
    double r, g, b;
    int row, column;
    glBegin( GL_POINTS );
    for(row = 0; row < p.getHeight(); row++) {
      for(column = 0; column < p.getWidth(); column++) {
        r = p.getChannel(row, column, 0) / max;
        g = p.getChannel(row, column, 1) / max;
        b = p.getChannel(row, column, 2) / max;
        glColor3d(r, g, b);
        glVertex2i(column, p.getHeight()-row-1);
      }
    }
    glEnd( );
  }
  else if ( mInteractionMode == IM_COLORTABLE ){
    displayColorTable();
  }
  else if (getInteractionMode() == IM_COLOR1){
    displayColorTable(); 
  }
  else if (getInteractionMode() == IM_COLOR2){
    displayColorTable(); 
  }
}

GlutApp::InteractionMode GlutApp::getInteractionMode() {
  return mInteractionMode;
}

GlutApp::FractalMode GlutApp::getFractalMode() {
  return mFractalMode;
}

void GlutApp::displayColorTable() {
  //ColorTable& ct = mActionData.getTable();
  PPM& p = mActionData.getOutputImage();
  //double max = static_cast<double>(p.getMaxColorValue());
  double r, g, b;
  int row, column;
  glBegin( GL_POINTS );
  for(row = 0; row < p.getHeight(); row++) {
    for(column = 0; column < p.getWidth(); column++) {
      ColorTable& ct = mActionData.getTable();
      int i = column * ct.getNumberOfColors() / p.getWidth();
      r = ct[i].getChannel(0) / 255.0;
      g = ct[i].getChannel(1) / 255.0;
      b = ct[i].getChannel(2) / 255.0;
      glColor3d(r, g, b);
      glVertex2i(column, row);
      //p.setPixel(row, column, r, g, b);
      }
    }
    glEnd( );
}

void GlutApp::setInteractionMode(InteractionMode mode) {
  mInteractionMode = mode;
}

void GlutApp::setColorTable() {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << mNumColor;
    mInputStream.str(tmp.str());
  }
  takeAction("set-color-table-size", mMenuData, mActionData);

  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << 0 << " " << mColor1.getRed() << " " << mColor1.getGreen() << " " << mColor1.getBlue() << " " << (mNumColor / 2) << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue();
    mInputStream.str(tmp.str());
  }
  takeAction("set-color-gradient", mMenuData, mActionData);

  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << (mNumColor / 2) << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue() << " " << mNumColor -1 << " " << mColor3.getRed() << " " << mColor3.getGreen() << " " << mColor3.getBlue();
    mInputStream.str(tmp.str());
  }
  takeAction("set-color-gradient", mMenuData, mActionData);
}

void GlutApp::decreaseColorTableSize() {
  ColorTable& ct = mActionData.getTable();
  if (ct.getNumberOfColors() > 10){
    double new_num_colors = ct.getNumberOfColors() / 1.1;
    mNumColor = new_num_colors;
    setColorTable();
    gridApplyColorTable();
  }
}

void GlutApp::increaseColorTableSize() {
  ColorTable& ct = mActionData.getTable();
  if (ct.getNumberOfColors() < 1024){
    double new_num_colors = ct.getNumberOfColors() * 1.1;
    mNumColor = new_num_colors;
    setColorTable();
    gridApplyColorTable();
  }
}

void GlutApp::randomColor1() {
  //ColorTable& ct = mActionData.getTable();
  PPM& p = mActionData.getOutputImage();
  int max_color_value = p.getMaxColorValue();
  mColor1.setRed(rand() % (max_color_value + 1));
  mColor1.setGreen(rand() % (max_color_value + 1));
  mColor1.setBlue(rand() % (max_color_value + 1));
  setColorTable();
  gridApplyColorTable();
}

void GlutApp::randomColor2() {
  //ColorTable& ct = mActionData.getTable();
  PPM& p = mActionData.getOutputImage();
  int max_color_value = p.getMaxColorValue();
  mColor2.setRed(rand() % (max_color_value + 1));
  mColor2.setGreen(rand() % (max_color_value + 1));
  mColor2.setBlue(rand() % (max_color_value + 1));
  setColorTable();
  gridApplyColorTable();
}

void GlutApp::zoomIn() {
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  mMinX += dx;
  mMaxX -= dx;
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  mMinY += dy;
  mMaxY -= dy;
}

void GlutApp::zoomOut() {
  double dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  double min_x = mMinX - dx;
  double max_x = mMaxX + dx;
  double dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  double min_y = mMinY - dy;
  double max_y = mMaxY + dy;
  if (min_x >= -2.0 && min_y >= -2.0 && max_x <= 2.0 && max_y <= 2.0){
    mMinX -= dx;
    mMaxX += dx;
    mMinY -= dy;
    mMaxY += dy;
  }
}

void GlutApp::moveLeft() {
  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  double min_x = mMinX - dx;
  if (min_x >= -2.0){
    mMinX -= dx;
    mMaxX -= dx;
  }
}

void GlutApp::moveRight() {
  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  double max_x = mMaxX + dx;
  if (max_x <= 2.0){
    mMinX += dx;
    mMaxX += dx;
  }
}

void GlutApp::moveDown() {
  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  double min_y = mMinY - dy;
  if (min_y >= -2.0){
    mMinY -= dy;
    mMaxY -= dy;
  }
}

void GlutApp::moveUp() {
  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  double max_y = mMaxY + dy;
  if (max_y <= 2.0){
    mMinY += dy;
    mMaxY += dy;
  }
}

void GlutApp::setFractalMode(FractalMode mode) {
  mFractalMode = mode;
}

void GlutApp::increaseMaxNumber() {
  if (mMaxNumber < 2048){
    mMaxNumber *= 1.1;
  }
}

void GlutApp::decreaseMaxNumber() {
  if (mMaxNumber > 11){
    mMaxNumber /= 1.1;
  }
}

void GlutApp::setAB(int x, int y) {
  ComplexFractal *cfptr = dynamic_cast<ComplexFractal*>(&mActionData.getGrid());
  if (getFractalMode() == M_MANDELBROT && cfptr != 0){
    mA = mMinX + x * cfptr->getDeltaX();
    mB = mMinY + y * cfptr->getDeltaY();
  }
}

void GlutApp::resetPlane() {
  mMinX = -2.0;
  mMinY = -2.0;
  mMaxX = 2.0;
  mMaxY = 2.0;
}

void GlutApp::createFractal() {
  if (getFractalMode() == M_MANDELBROT){
    selectMandelbrot();
    configureGrid(mMaxNumber);
    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
    fractalCalculate();
    gridApplyColorTable();
  }
  if(getFractalMode() == M_JULIA){
    selectJulia();
    configureGrid(mMaxNumber);
    juliaParameters(mA, mB);
    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
    fractalCalculate();
    gridApplyColorTable();
  }
  if(getFractalMode() == M_COMPLEX){
    selectComplexFractal();
    configureGrid(mMaxNumber);
    fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
    fractalCalculate();
    gridApplyColorTable();
  }
}

void GlutApp::increaseChannel(Color &color, int channel) {
  if (channel == 0){
    int red = color.getRed();
    red += 10;
    if (red > 255){
      color.setRed(255);
    }
    else{
      color.setRed(red);
    }
  }
  if (channel == 1){
    int green = color.getGreen();
    green += 10;
    if (green > 255){
      color.setGreen(255);
    }
    else{
      color.setGreen(green);
    }
  }
  if (channel == 2){
    int blue = color.getBlue();
    blue += 10;
    if (blue > 255){
      color.setRed(255);
    }
    else{
      color.setBlue(blue);
    }
  }
  setColorTable();
  gridApplyColorTable();
}

void GlutApp::decreaseChannel(Color &color, int channel) {
  if (channel == 0){
    int red = color.getRed();
    red -= 10;
    if (red < 0){
      color.setRed(0);
    }
    else{
      color.setRed(red);
    }
  }
  if (channel == 1){
    int green = color.getGreen();
    green -= 10;
    if (green < 0){
      color.setGreen(0);
    }
    else{
      color.setGreen(green);
    }
  }
  if (channel == 2){
    int blue = color.getBlue();
    blue -= 10;
    if (blue < 0){
      color.setRed(0);
    }
    else{
      color.setBlue(blue);
    }
  }
  setColorTable();
  gridApplyColorTable();
}

Color &GlutApp::fetchColor() {
  if (getInteractionMode() == IM_COLOR1){
    return mColor1;
  }
  if (getInteractionMode() == IM_COLOR2){
    return mColor2;
  }
  else {
    static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
    return c;
  }
}

void GlutApp::increaseRed() {
  increaseChannel(fetchColor(), 0);
}

void GlutApp::decreaseRed() {
  decreaseChannel(fetchColor(), 0);
}

void GlutApp::increaseGreen() {
  increaseChannel(fetchColor(), 1);
}

void GlutApp::decreaseGreen() {
  decreaseChannel(fetchColor(), 1);
}

void GlutApp::increaseBlue() {
  increaseChannel(fetchColor(), 2);
}

void GlutApp::decreaseBlue() {
  decreaseChannel(fetchColor(), 2);
}

void GlutApp::writeImage() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");

  {
    std::stringstream tmp;
    tmp << "image-" << mImageNumber << ".ppm";
    mInputStream.str(tmp.str());
  }
  mImageNumber += 1;
  takeAction("write", mMenuData, mActionData);
}

void GlutApp::selectJulia() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  setFractalMode(M_JULIA);
  takeAction("julia", mMenuData, mActionData);
}

void GlutApp::selectMandelbrot() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  setFractalMode(M_MANDELBROT);
  takeAction("mandelbrot", mMenuData, mActionData);
}

void GlutApp::selectComplexFractal() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  setFractalMode(M_COMPLEX);
  takeAction("complex-fractal", mMenuData, mActionData);
}

void GlutApp::configureGrid(int max) {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << mHeight << " " << mWidth << " " << max;
    mInputStream.str(tmp.str());
  }
  takeAction("grid", mMenuData, mActionData);
}

void GlutApp::juliaParameters(double a, double b) {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << a << " " << b;
    mInputStream.str(tmp.str());
  }
  takeAction("julia-parameters", mMenuData, mActionData);
}

void GlutApp::fractalPlaneSize(double x_min, double x_max, double y_min, double y_max) {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << x_min << " " << x_max << " "<< y_min << " " << y_max;
    mInputStream.str(tmp.str());
  }
  takeAction("fractal-plane-size", mMenuData, mActionData);
}

void GlutApp::fractalCalculate() {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  takeAction("fractal-calculate", mMenuData, mActionData);
}

void GlutApp::gridApplyColorTable() {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  takeAction("grid-apply-color-table", mMenuData, mActionData);
}

void GlutApp::createJulia() {
  // julia
  selectJulia();
  // grid
  configureGrid(200);
  // julia-parameters
  juliaParameters(0.45, -0.32);
  // fractal-plane-size
  fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
  // fractal-calculate
  fractalCalculate();
  // grid-apply-color-table
  gridApplyColorTable();
}

void GlutApp::createJulia2() {
  // julia
  selectJulia();
  // grid
  configureGrid(100);
  // julia-parameters
  juliaParameters(-0.8, 0.156);
  // fractal-plane-size
  fractalPlaneSize(-1.5, 1.5, -1.5, 1.5);
  // fractal-calculate
  fractalCalculate();
  // grid-apply-color-table
  gridApplyColorTable();
}

void GlutApp::createMandelbrot() {
  // mandelbrot
  selectMandelbrot();
  // grid
  configureGrid(500);
  // fractal-plane-size
  fractalPlaneSize(-5.0, 0.2, -1.0, 3.0);
  // fractal-calculate
  fractalCalculate();
  // grid-apply-color-table
  gridApplyColorTable();
}

void GlutApp::createMandelbrot2() {
  // mandelbrot-power
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  takeAction("mandelbrot-power", mMenuData, mActionData);
  // grid
  configureGrid(200);
  // set mandelbrot power
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << 4.0;
    mInputStream.str(tmp.str());
  }
  takeAction("set-mandelbrot-power", mMenuData, mActionData);
  // fractal-plane-size
  fractalPlaneSize(-1.5, 1.5, -1.5, 1.5);
  // fractal-calculate
  fractalCalculate();
  // grid-apply-color-table
  gridApplyColorTable();
}

void GlutApp::createComplexFractal() {
  // complex fractal
  selectComplexFractal();
  // grid
  configureGrid(100);
  // fractal-plane-size
  fractalPlaneSize(-1.0, 1.0, -1.0, 1.0);
  // fractal-calculate
  fractalCalculate();
  // grid-apply-color-table
  gridApplyColorTable();
}

void GlutApp::createComplexFractal2() {
  // complex fractal
  selectComplexFractal();
  // grid
  configureGrid(450);
  // fractal-plane-size
  fractalPlaneSize(-1.9, 1.2, -1.2, 1.9);
  // fractal-calculate
  fractalCalculate();
  // grid-apply-color-table
  gridApplyColorTable();
}
