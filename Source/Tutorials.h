#ifndef TUTORIALS_H
#define TUTORIALS_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "ogldev_util.h"
#include "ogldev_pipeline.h"
#include "ogldev_math_3d.h"

#include "ogldev_glut_backend.h"
#include "ogldev_camera.h"
#include "ogldev_texture.h"

#include <set>

class Tutorials
{
public:
  enum GlobalDefaults {
    WINDOW_WIDTH_1_14 = 1024,
    WINDOW_HEIGHT_1_14 = 768,
    WINDOW_WIDTH_15 = 1920,
    WINDOW_HEIGHT_15 = 1080,
    WINDOW_WIDTH_16 = 1280,
    WINDOW_HEIGHT_16 = 1024,
    WINDOW_START_X = 100,
    WINDOW_START_Y = 100
  };

  struct Vertex
  {
      Vector3f m_pos;
      Vector2f m_tex;

      Vertex() {}

      Vertex(Vector3f pos, Vector2f tex)
      {
          m_pos = pos;
          m_tex = tex;
      }
  };

  explicit Tutorials(int* argc, char* argv[]);
  virtual ~Tutorials();

protected:

};

#endif // TUTORIALS_H
