#include "GlutApp.h"
#include "glut_app.h"
#include "image_menu.h"

GlutApp::GlutApp(int height, int width)
  : mHeight(height), mWidth(width), mActionData(mInputStream, mOutputStream) {
  configureMenu(mMenuData);
  mActionData.setGrid(new ComplexFractal);

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

void GlutApp::selectJulia() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  takeAction("julia", mMenuData, mActionData);
}

void GlutApp::selectMandelbrot() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  takeAction("mandelbrot", mMenuData, mActionData);
}

void GlutApp::selectComplexFractal() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
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
  juliaParameters( -0.8, 0.156);
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
  configureGrid(50);
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
