#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Tutorials.h"
#include <functional>

class Tutorial : public Tutorials
{
public:
  explicit Tutorial(int tutorialId, int* argc, char* argv[]);
  virtual ~Tutorial();

    virtual void run() override final;

  protected:
    virtual void createVertexBuffer();
    virtual void createIndexBuffer();
    virtual void compileShaders();
    virtual void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
    virtual void SpecialKeyboardCB(int Key, int x, int y);

private:
    int _tutorialID;

  GLuint _VBO, _IBO;
  GLuint _gWorldLocation;
  GLuint _gScaleLocation;
  GLuint _gWVPLocation;
  PersProjInfo _gPersProjInfo;
  Camera* _pGameCamera;
  char pVSFileName[255];
  char pFSFileName[255];

//  static auto _createVertexBuffer;
//  void (*)() _createVertexBuffer;
  std::function<void (void)> _createVertexBuffer;
  std::function<void (void)> _createIndexBuffer;
  std::function<void (void)> _compileShaders;
  std::function<void (void)> _displayFunc;
  std::function<void (void)> _idleFunc;
  std::function<void (int, int, int)> _specialFunc;

  std::function<void (void)> makeCreateVertexBufferFunc(GLuint* vertexObjectBuffer);
  std::function<void (void)> makeCreateIndexBufferFunc(GLuint* indexObjectBuffer);
  std::function<void (void)> makeCompileShadersFunc();
  std::function<void (void)> makeDisplayFunc();
  std::function<void (void)> makeIdleFunc();
  std::function<void (int, int, int)> makeSpecialFunc();
//  void (*makeCreateVertexBufferFunc)(GLuint* vertexObjectBuffer);
};

#endif // TUTORIAL_H
