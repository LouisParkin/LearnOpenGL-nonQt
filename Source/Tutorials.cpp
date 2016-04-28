#include "Tutorials.h"

#include <assert.h>

Tutorials::Tutorials(int* argc, char* argv[])
{
  glutInit(argc, argv);
}

Tutorials::~Tutorials()
{

}

void Tutorials::initGlew()
{
  /// Initialize Glew
  GLenum res = glewInit();
  assert(res == GLEW_OK);
}

void Tutorials::run()
{
  ///
  /// Create vertex buffer: glGenBuffers, glBindBuffer, glBufferData.
  ///
  createVertexBuffer();

  ///
  /// Create the index buffer: glGenBuffers, glBindBuffer, glBufferData.
  ///
  createIndexBuffer();

  ///
  /// Read shaders from file, compile, verify and add to shader program.
  ///
  compileShaders();
}

void Tutorials::setWindowSize(int width, int height)
{
  _width = width;
  _height = height;
  glutInitWindowSize(_width, _height);
}

void Tutorials::setWindowLocation(int topLeftX, int topLeftY)
{
  _startX = topLeftX;
  _startY = topLeftY;
  glutInitWindowPosition(_startX, _startY);
}

int Tutorials::createWindow(int tutorialID)
{
  char title[40];

  sprintf(&title[0], "Tutorial %d", tutorialID);
  int newGlutWindow = glutCreateWindow(title);
  _myWindows.insert(newGlutWindow);

  return newGlutWindow;
}

void Tutorials::initGlut(void (* displayFunc)(), void (* idleFunc)(), void (* specialFunc)( int , int , int ))
{
  if(displayFunc != nullptr)
  {
    glutDisplayFunc(displayFunc);
  }
  if(idleFunc != nullptr)
  {
    glutIdleFunc(idleFunc);
  }
  if(specialFunc != nullptr)
  {
    glutSpecialFunc(specialFunc);
  }
}

