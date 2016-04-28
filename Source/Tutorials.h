#ifndef TUTORIALS_H
#define TUTORIALS_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "ogldev_util.h"
#include "ogldev_pipeline.h"
#include "ogldev_math_3d.h"

#include "ogldev_glut_backend.h"
#include "ogldev_camera.h"

#include <set>

class Tutorials
{
public:
  enum GlobalDefaults {
    WINDOW_WIDTH = 1024,
    WINDOW_HEIGHT = 768,
    WINDOW_START_X = 100,
    WINDOW_START_Y = 100
  };

  explicit Tutorials(int* argc, char* argv[]);
  virtual ~Tutorials();

  virtual void run();

protected:
  void initGlut(void (* displayFunc)(void), void (* idleFunc)(void) = nullptr, void (* specialFunc)(int, int, int) = nullptr);
  void initGlew();
  void setWindowSize(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT);
  void setWindowLocation(int topLeftX = WINDOW_START_X, int topLeftY = WINDOW_START_Y);
  int createWindow(int tutorialID);

  virtual void createVertexBuffer() = 0;
  virtual void compileShaders() = 0;
  virtual void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType) = 0;
  virtual void createIndexBuffer() = 0;
  virtual void SpecialKeyboardCB(int Key, int x, int y) = 0;

  int _width;
  int _height;
  int _startX;
  int _startY;

  std::set<int> _myWindows;
};

#endif // TUTORIALS_H
