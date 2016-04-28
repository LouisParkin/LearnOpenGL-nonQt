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

protected:

};

#endif // TUTORIALS_H
