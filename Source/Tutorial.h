#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Tutorials.h"
#include <functional>

class Tutorial : public Tutorials
{
public:
  virtual ~Tutorial();

  static Tutorial& getInstance(int tutorialId, int* argc, char* argv[])
  {
    static Tutorial instance(tutorialId, argc, argv);
    return instance;
  }
  static void run();// override final;

protected:
  static void initGlut(void (* displayFunc)(void), void (* idleFunc)(void) = nullptr, void (* specialFunc)(int, int, int) = nullptr);
  static void initGlew();
  static void setWindowSize(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT);
  static void setWindowLocation(int topLeftX = WINDOW_START_X, int topLeftY = WINDOW_START_Y);
  static int createWindow(int tutorialID);

  static void createVertexBuffer();
  static void createIndexBuffer();
  static void compileShaders();
  static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
  static void SpecialKeyboardCB(int Key, int x, int y);

private:
  explicit Tutorial(int tutorialId, int* argc, char* argv[]);

  static int _tutorialID;
  static GLuint _VBO;
  static GLuint _IBO;
  static GLuint _gWorldLocation;
  static GLuint _gScaleLocation;
  static GLuint _gWVPLocation;
  static PersProjInfo _gPersProjInfo;
  static Camera* _pGameCamera;
  static char pVSFileName[255];
  static char pFSFileName[255];
  static int _width;
  static int _height;
  static int _startX;
  static int _startY;
  static std::set<int> _myWindows;


  //  static auto _createVertexBuffer;
  //  void (*)() _createVertexBuffer;
  static std::function<void (void)> _createVertexBuffer;
  static std::function<void (void)> _createIndexBuffer;
  static std::function<void (void)> _compileShaders;
  static std::function<void (void)> _displayFunc;
  static std::function<void (void)> _idleFunc;
  static std::function<void (GLuint, const char*, GLenum)> _addShaderFunc;
  static std::function<void (int, int, int)> _specialFunc;

  static std::function<void (void)> makeCreateVertexBufferFunc(GLuint& vertexObjectBuffer);
  static std::function<void (void)> makeCreateIndexBufferFunc(GLuint& indexObjectBuffer);
  static std::function<void (void)> makeCompileShadersFunc();
  static std::function<void (void)> makeDisplayFunc();
  static std::function<void (void)> makeIdleFunc();
  static std::function<void (GLuint, const char*, GLenum)> makeAddShaderFunc();
  static std::function<void (int, int, int)> makeSpecialFunc();
  //  void (*makeCreateVertexBufferFunc)(GLuint* vertexObjectBuffer);
};

#endif // TUTORIAL_H
