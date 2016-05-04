#include "Tutorial.h"

GLuint Tutorial::_VBO;
GLuint Tutorial::_IBO;

GLuint Tutorial::_gWorldLocation;
GLuint Tutorial::_gScaleLocation;
GLuint Tutorial::_gWVPLocation;

PersProjInfo Tutorial::_gPersProjInfo;
Camera* Tutorial::_pGameCamera;

char Tutorial::pVSFileName[255];
char Tutorial::pFSFileName[255];

int Tutorial::_width;
int Tutorial::_height;
int Tutorial::_startX;
int Tutorial::_startY;

std::set<int> Tutorial::_myWindows;
int Tutorial::_tutorialID;

GLuint   Tutorial::_gSampler;
Texture* Tutorial::_pTexture = NULL;

#ifdef __TUT_VERSION

#if __TUT_VERSION == 17

  Tutorial17* Tutorial::_tutorial;

  #elif __TUT_VERSION == 18

    Tutorial18* Tutorial::_tutorial;

  #elif __TUT_VERSION == 19

    Tutorial19* Tutorial::_tutorial;

  #elif __TUT_VERSION == 20

    Tutorial20* Tutorial::_tutorial;
#endif

#endif

std::function<void (void)> Tutorial::_createVertexBuffer;
std::function<void (void)> Tutorial::_createIndexBuffer;
std::function<void (void)> Tutorial::_compileShaders;
std::function<void (void)> Tutorial::_displayFunc;
std::function<void (void)> Tutorial::_idleFunc;
std::function<void (int, int, int)> Tutorial::_specialFunc;
std::function<void (GLuint, const char*, GLenum)> Tutorial::_addShaderFunc;
std::function<void (int, int, int)>               Tutorial::_keyboardFunc;
std::function<void (int, int)>                    Tutorial::_passiveMouseFunc;


Tutorial::Tutorial(int tutorialId, int* argc, char* argv[]) : Tutorials(argc, argv)
{
  _tutorialID = tutorialId;
  if (_tutorialID <= 16) {
    sprintf(pVSFileName, "/home/lparkin/Projects/S3/LearnOpenGL-nonQt/Shaders/Tutorial%d/shader.vs", _tutorialID);
    sprintf(pFSFileName, "/home/lparkin/Projects/S3/LearnOpenGL-nonQt/Shaders/Tutorial%d/shader.fs", _tutorialID);
//  sprintf(pVSFileName, "/home/louis/Projects/LearnOpenGL-nonQt/Shaders/Tutorial%d/shader.vs", _tutorialID);
//  sprintf(pFSFileName, "/home/louis/Projects/LearnOpenGL-nonQt/Shaders/Tutorial%d/shader.fs", _tutorialID);
    glutInit(argc, argv);
  }
  else if (_tutorialID >= 17) {

#ifdef __TUT_VERSION

#if __TUT_VERSION >= 17
    if (_tutorialID >= 17) {
      GLUTBackendInit(*argc, argv, false, false);
    sprintf(pVSFileName, "/home/lparkin/Projects/S3/LearnOpenGL-nonQt/Shaders/Tutorial%d/lighting.vs", _tutorialID);
    sprintf(pFSFileName, "/home/lparkin/Projects/S3/LearnOpenGL-nonQt/Shaders/Tutorial%d/lighting.fs", _tutorialID);
//  sprintf(pVSFileName, "/home/louis/Projects/S3/LearnOpenGL-nonQt/Shaders/Tutorial%d/lighting.vs", _tutorialID);
//  sprintf(pFSFileName, "/home/louis/Projects/S3/LearnOpenGL-nonQt/Shaders/Tutorial%d/lighting.fs", _tutorialID);
      return;
  }
#endif
#endif


  }

  _createVertexBuffer = makeCreateVertexBufferFunc(_VBO);
  _createIndexBuffer  = makeCreateIndexBufferFunc(_IBO);
  _addShaderFunc      = makeAddShaderFunc();
  _compileShaders     = makeCompileShadersFunc();
  _displayFunc        = makeDisplayFunc();
  _idleFunc           = makeIdleFunc();
  _specialFunc        = makeSpecialFunc();
  _keyboardFunc       = makeKeyboardFunc();
  _passiveMouseFunc   = makePassiveMouseFunc();
}

Tutorial::~Tutorial()
{

}

std::function<void (void)> Tutorial::makeCompileShadersFunc()
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
    return nullptr;
  case 4:
    return [ & ]() {
      GLuint ShaderProgram = glCreateProgram();

      if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
      }

      std::string vs, fs;

      if (!ReadFile(pVSFileName, vs)) {
        exit(1);
      };

      if (!ReadFile(pFSFileName, fs)) {
        exit(1);
      };

      aAddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
      aAddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

      GLint Success = 0;
      GLchar ErrorLog[1024] = { 0 };

      glLinkProgram(ShaderProgram);
      glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
      if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      glValidateProgram(ShaderProgram);
      glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
      if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      glUseProgram(ShaderProgram);
    };
  case 5:
    return [ & ]() {
      /**
       * Create a new shader program.
       */
      GLuint ShaderProgram = glCreateProgram();


      /// Make sure the shader program creation succeeded.
      if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
      }

      /// Make strings for reading the GLSL source from file.
      std::string vs, fs;

      /// Read the vertex shader source from file.
      if (!ReadFile(pVSFileName, vs)) {
        exit(1);
      };

      /// Read the fragment shader source from file.
      if (!ReadFile(pFSFileName, fs)) {
        exit(1);
      };

      /// Add the shaders to the shader program.
      aAddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
      aAddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

      GLint Success = 0;
      GLchar ErrorLog[1024] = { 0 };

      glLinkProgram(ShaderProgram); ///< Link the shader program, assuming to the GL Context.
      glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success); ///< Get shader link status.

      /// Handle error if linking failed.
      if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      /// A shader program that links is not by definition valid, so validate it.
      glValidateProgram(ShaderProgram);

      /// Retrieve the validation status.
      glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);

      /// Handle the error if validation failed.
      if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      /// Assign a program for OpenGL to use.
      glUseProgram(ShaderProgram);

      /// This tutorial is about the use of Uniform shader attributes, retrieve and store it.
      _gScaleLocation = glGetUniformLocation(ShaderProgram, "gScale");

      /// Ensure it succeeded, handle the possible failure.
      assert(_gScaleLocation != 0xFFFFFFFF);
    };
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
    return [ & ]() {
      /**
       * Create a new shader program.
       */
      GLuint ShaderProgram = glCreateProgram();


      /// Make sure the shader program creation succeeded.
      if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
      }

      /// Make strings for reading the GLSL source from file.
      std::string vs, fs;

      /// Read the vertex shader source from file.
      if (!ReadFile(pVSFileName, vs)) {
        exit(1);
      };

      /// Read the fragment shader source from file.
      if (!ReadFile(pFSFileName, fs)) {
        exit(1);
      };

      /// Add the shaders to the shader program.
      aAddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
      aAddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

      GLint Success = 0;
      GLchar ErrorLog[1024] = { 0 };

      glLinkProgram(ShaderProgram); ///< Link the shader program, assuming to the GL Context.
      glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success); ///< Get shader link status.

      /// Handle error if linking failed.
      if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      /// A shader program that links is not by definition valid, so validate it.
      glValidateProgram(ShaderProgram);

      /// Retrieve the validation status.
      glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);

      /// Handle the error if validation failed.
      if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      /// Assign a program for OpenGL to use.
      glUseProgram(ShaderProgram);

      /// This tutorial is about the use of Uniform shader attributes (matrices) to transform vertices, retrieve and store it.
      _gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");

      /// Ensure it succeeded, handle the possible failure.
      assert(_gWorldLocation != 0xFFFFFFFF);
    };
  case 13:
  case 14:
  case 15:
    return [ & ]() {
      /**
       * Create a new shader program.
       */
      GLuint ShaderProgram = glCreateProgram();


      /// Make sure the shader program creation succeeded.
      if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
      }

      /// Make strings for reading the GLSL source from file.
      std::string vs, fs;

      /// Read the vertex shader source from file.
      if (!ReadFile(pVSFileName, vs)) {
        exit(1);
      };

      /// Read the fragment shader source from file.
      if (!ReadFile(pFSFileName, fs)) {
        exit(1);
      };

      /// Add the shaders to the shader program.
      aAddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
      aAddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

      GLint Success = 0;
      GLchar ErrorLog[1024] = { 0 };

      glLinkProgram(ShaderProgram); ///< Link the shader program, assuming to the GL Context.
      glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success); ///< Get shader link status.

      /// Handle error if linking failed.
      if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      /// A shader program that links is not by definition valid, so validate it.
      glValidateProgram(ShaderProgram);

      /// Retrieve the validation status.
      glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);

      /// Handle the error if validation failed.
      if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      /// Assign a program for OpenGL to use.
      glUseProgram(ShaderProgram);

      /// This tutorial is about the use of Uniform shader attributes (matrices) to transform vertices, retrieve and store it.
      _gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");

      /// Ensure it succeeded, handle the possible failure.
      assert(_gWVPLocation != 0xFFFFFFFF);
    };
  case 16:
    return [ & ]() {
      /**
       * Create a new shader program.
       */
      GLuint shaderProgram = glCreateProgram();


      /// Make sure the shader program creation succeeded.
      if (shaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
      }

      /// Make strings for reading the GLSL source from file.
      std::string vs, fs;

      /// Read the vertex shader source from file.
      if (!ReadFile(pVSFileName, vs)) {
        exit(1);
      };

      /// Read the fragment shader source from file.
      if (!ReadFile(pFSFileName, fs)) {
        exit(1);
      };

      /// Add the shaders to the shader program.
      aAddShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);
      aAddShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

      GLint Success = 0;
      GLchar ErrorLog[1024] = { 0 };

      glLinkProgram(shaderProgram); ///< Link the shader program, assuming to the GL Context.
      glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Success); ///< Get shader link status.

      /// Handle error if linking failed.
      if (Success == 0) {
        glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      /// A shader program that links is not by definition valid, so validate it.
      glValidateProgram(shaderProgram);

      /// Retrieve the validation status.
      glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &Success);

      /// Handle the error if validation failed.
      if (!Success) {
        glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
      }

      /// Assign a program for OpenGL to use.
      glUseProgram(shaderProgram);

      /// This tutorial is about the use of Uniform shader attributes (matrices) to transform vertices, retrieve and store it.
      _gWVPLocation = glGetUniformLocation(shaderProgram, "gWVP");

      /// Ensure it succeeded, handle the possible failure.
      assert(_gWVPLocation != 0xFFFFFFFF);
      _gSampler = glGetUniformLocation(shaderProgram, "gSampler");
      assert(_gSampler != 0xFFFFFFFF);
    };
  }
}

std::function<void ()> Tutorial::makeDisplayFunc()
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
    return nullptr;
  case 4:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
    };
  case 5:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.001f;

      /// glUniform1f provides a value for the Uniform attribute of the shader.
      /// In this example, sin(scale).
      ///
      /// Internally, the shader uses the value of scale to adjust the Position (x,y) of the vertices.
      ///
      glUniform1f(_gScaleLocation, sinf(scale));

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
    };
  case 6:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.001f;

      Matrix4f world;

      world.m[0][0] = 1.0f;
      world.m[0][1] = 0.0f;
      world.m[0][2] = 0.0f;
      world.m[0][3] = sinf(scale);
      world.m[1][0] = 0.0f;
      world.m[1][1] = 1.0f;
      world.m[1][2] = 0.0f;
      world.m[1][3] = 0.0f;
      world.m[2][0] = 0.0f;
      world.m[2][1] = 0.0f;
      world.m[2][2] = 1.0f;
      world.m[2][3] = 0.0f;
      world.m[3][0] = 0.0f;
      world.m[3][1] = 0.0f;
      world.m[3][2] = 0.0f;
      world.m[3][3] = 1.0f;

      glUniformMatrix4fv(_gWorldLocation, 1, GL_TRUE, &world.m[0][0]);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
    };
  case 7:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.001f;

      Matrix4f world;

      world.m[0][0] = cosf(scale);
      world.m[0][1] = -sinf(scale);
      world.m[0][2] = 0.0f;
      world.m[0][3] = 0.0f;
      world.m[1][0] = sinf(scale);
      world.m[1][1] =  cosf(scale);
      world.m[1][2] = 0.0f;
      world.m[1][3] = 0.0f;
      world.m[2][0] = 0.0f;
      world.m[2][1] = 0.0f;
      world.m[2][2] = 1.0f;
      world.m[2][3] = 0.0f;
      world.m[3][0] = 0.0f;
      world.m[3][1] = 0.0f;
      world.m[3][2] = 0.0f;
      world.m[3][3] = 1.0f;

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWorldLocation, 1, GL_TRUE, &world.m[0][0]);

      /// Load the desired size into the shader.
      glUniform1f(_gScaleLocation, 0.5);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
    };
  case 8:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.001f;

      Matrix4f world;

      world.m[0][0] = sinf(scale);
      world.m[0][1] = 0.0f;
      world.m[0][2] = 0.0f;
      world.m[0][3] = 0.0f;
      world.m[1][0] = 0.0f;
      world.m[1][1] = sinf(scale);
      world.m[1][2] = 0.0f;
      world.m[1][3] = 0.0f;
      world.m[2][0] = 0.0f;
      world.m[2][1] = 0.0f;
      world.m[2][2] = sinf(scale);
      world.m[2][3] = 0.0f;
      world.m[3][0] = 0.0f;
      world.m[3][1] = 0.0f;
      world.m[3][2] = 0.0f;
      world.m[3][3] = 1.0f;

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWorldLocation, 1, GL_TRUE, &world.m[0][0]);

      /// Load the desired size into the shader.
      glUniform1f(_gScaleLocation, 0.5);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
    };
  case 9:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.001f;

      Matrix4f world;

      ///

      world.m[0][0] = sinf(scale);
      world.m[0][1] = 0.0f;
      world.m[0][2] = 0.0f;
      world.m[0][3] = 0.0f;
      world.m[1][0] = 0.0f;
      world.m[1][1] = sinf(scale);
      world.m[1][2] = 0.0f;
      world.m[1][3] = 0.0f;
      world.m[2][0] = 0.0f;
      world.m[2][1] = 0.0f;
      world.m[2][2] = sinf(scale);
      world.m[2][3] = 0.0f;
      world.m[3][0] = 0.0f;
      world.m[3][1] = 0.0f;
      world.m[3][2] = 0.0f;
      world.m[3][3] = 1.0f;

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWorldLocation, 1, GL_TRUE, &world.m[0][0]);

      /// Load the desired size into the shader.
      //  glUniform1f(_gScaleLocation, 0.5);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
    };
  case 10:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.001f;

      Matrix4f world;

      ///

      world.m[0][0] = cosf(scale);
      world.m[0][1] = 0.0f;
      world.m[0][2] = -sinf(scale);
      world.m[0][3] = 0.0f;
      world.m[1][0] = 0.0f;
      world.m[1][1] = 1.0f;
      world.m[1][2] = 0.0f;
      world.m[1][3] = 0.0f;
      world.m[2][0] = sinf(scale);
      world.m[2][1] = 0.0f;
      world.m[2][2] = cosf(scale);
      world.m[2][3] = 0.0f;
      world.m[3][0] = 0.0f;
      world.m[3][1] = 0.0f;
      world.m[3][2] = 0.0f;
      world.m[3][3] = 1.0f;

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWorldLocation, 1, GL_TRUE, &world.m[0][0]);

      /// Load the desired size into the shader.
      //  glUniform1f(_gScaleLocation, 0.9);

      glEnableVertexAttribArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

      //  glDrawArrays(GL_TRIANGLES, 0, 3);
      glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
    };
  case 11:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.001f;

      Pipeline pipeLine;
      pipeLine.Scale(sinf(scale * 0.1f), sinf(scale * 0.1f), sinf(scale * 0.1f));
      pipeLine.WorldPos(sinf(scale), 0.0f, 0.0f);
      pipeLine.Rotate(sinf(scale) * 90.0f, sinf(scale) * 90.0f, sinf(scale) * 90.0f);

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWorldLocation, 1, GL_TRUE, (const GLfloat*)pipeLine.GetWorldTrans());

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

      glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
    };
  case 12:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.01f;

      Pipeline pipeLine;
      pipeLine.Rotate(0.0f, scale, 0.0f);
      pipeLine.WorldPos(0.0f, 0.0f, 5.0f);
      pipeLine.SetPerspectiveProj(_gPersProjInfo);

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWorldLocation, 1, GL_TRUE, (const GLfloat*)pipeLine.GetWPTrans());

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

      glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
      //  QThread::msleep(1);
    };
  case 13:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.01f;

      Pipeline pipeLine;
      pipeLine.Rotate(0.0f, scale, 0.0f);
      pipeLine.WorldPos(0.0f, 0.0f, 3.0f);

      Vector3f CameraPos(0.0f, 0.0f, -3.0f);
      Vector3f CameraTarget(0.0f, 0.0f, 2.0f);
      Vector3f CameraUp(0.0f, 1.0f, 0.0f);
      pipeLine.SetCamera(CameraPos, CameraTarget, CameraUp);
      pipeLine.SetPerspectiveProj(_gPersProjInfo);

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWVPLocation, 1, GL_TRUE, (const GLfloat*)pipeLine.GetWVPTrans());

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

      glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
      //  QThread::msleep(1);
    };
  case 14:
    return [ & ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.01f;

      Pipeline pipeLine;
      pipeLine.Rotate(0.0f, scale, 0.0f);
      pipeLine.WorldPos(0.0f, 0.0f, 3.0f);
      pipeLine.SetCamera(*_pGameCamera);
      pipeLine.SetPerspectiveProj(_gPersProjInfo);

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWVPLocation, 1, GL_TRUE, (const GLfloat*)pipeLine.GetWVPTrans());

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

      glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
      //  QThread::msleep(1);};
    };
  case 15:
    return [ & ]() {
      _pGameCamera->OnRender();

      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.01f;

      Pipeline pipeLine;
      pipeLine.Rotate(0.0f, scale, 0.0f);
      pipeLine.WorldPos(0.0f, 0.0f, 3.0f);
      pipeLine.SetCamera(*_pGameCamera);
      pipeLine.SetPerspectiveProj(_gPersProjInfo);

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWVPLocation, 1, GL_TRUE, (const GLfloat*)pipeLine.GetWVPTrans());

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

      glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
      //  QThread::msleep(1);};
    };
  case 16:
    return [ & ]() {
      _pGameCamera->OnRender();

      glClear(GL_COLOR_BUFFER_BIT);

      /// allocate a static variable scale
      static float scale = 0.0f;

      /// increment scale by 0.001.
      scale += 0.01f;

      Pipeline pipeLine;
      pipeLine.Rotate(0.0f, scale, 0.0f);
      pipeLine.WorldPos(0.0f, 0.0f, 3.0f);
      pipeLine.SetCamera(*_pGameCamera);
      pipeLine.SetPerspectiveProj(_gPersProjInfo);

      /// Load the matrix into the shader.
      glUniformMatrix4fv(_gWVPLocation, 1, GL_TRUE, (const GLfloat*)pipeLine.GetWVPTrans());

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
      _pTexture->Bind(GL_TEXTURE0);
      glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);

      glutSwapBuffers();
      //  QThread::msleep(1);};
    };
  }
}

std::function<void ()> Tutorial::makeIdleFunc()
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
  case 4:
    return nullptr;
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
  case 16:
    return makeDisplayFunc();
  }
}

std::function<void (GLuint, const char*, GLenum)> Tutorial::makeAddShaderFunc()
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
    return nullptr;
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
  case 16:
    return [&](GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType) {
      /// Create a new shader object
      GLuint ShaderObj = glCreateShader(ShaderType);

      /// Make sure it was created.
      if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(1);
      }

      const GLchar* p[1];
      p[0] = pShaderText; ///< Implicit transfer of shader text from char* to GLchar*
      GLint Lengths[1];
      Lengths[0] = strlen(pShaderText); ///< Store the length of the null terminated string.

      glShaderSource(ShaderObj, 1, p, Lengths);  ///< Link the shader source to the shader object
      glCompileShader(ShaderObj); ///< compile the shader.

      GLint success;
      glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success); ///< Check the compile status to ensure it succeeded.

      /// Handle the error if the shader did not compile successfully.
      if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
      }

      /// Attach the shader to the shader program.
      glAttachShader(ShaderProgram, ShaderObj);
    };
  }
}

std::function<void (int, int, int)> Tutorial::makeSpecialFunc()
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
    return nullptr;
  case 14:
  case 15:
  case 16:
    return [ & ](int Key, int x, int y) {
      OGLDEV_KEY OgldevKey = GLUTKeyToOGLDEVKey(Key);
      _pGameCamera->OnKeyboard(OgldevKey);
    };
  }
}

std::function<void (int, int, int)> Tutorial::makeKeyboardFunc()
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
    return nullptr;
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
  case 16:
    return [ & ](int Key, int x, int y) {
      switch (Key) {
      case 'q':
        glutLeaveMainLoop();
        break;
      }
    };
  }
}

std::function<void (int, int)> Tutorial::makePassiveMouseFunc()
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
    return nullptr;
  case 15:
  case 16:
    return [ & ](int x, int y) {
      _pGameCamera->OnMouse(x, y);
    };
  }
}

std::function<void (void)> Tutorial::makeCreateIndexBufferFunc(GLuint& indexObjectBuffer)
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
    return nullptr;
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
  case 16:
    return [ & ]() {
      unsigned int Indices[] = { 0, 3, 1,
                                 1, 3, 2,
                                 2, 3, 0,
                                 0, 1, 2
                               };

      GLuint* ref = const_cast<GLuint*>(&indexObjectBuffer);
      glGenBuffers(1, ref);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexObjectBuffer);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    };

  }
}

std::function<void (void)> Tutorial::makeCreateVertexBufferFunc(GLuint& vertexObjectBuffer)
//auto Tutorial::makeCreateVertexBufferFunc(GLuint* vertexObjectBuffer) -> decltype( void(*)() )
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
    return nullptr;
  case 4:
    return [ & ]() {
      Vector3f Vertices[3];
      Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
      Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
      Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

      GLuint* ref = const_cast<GLuint*>(&vertexObjectBuffer);
      glGenBuffers(1, ref);
      glBindBuffer(GL_ARRAY_BUFFER, vertexObjectBuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    };
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
    return [ & ]() {
      /**
         * Vector3f is a composite data type that consists of an x, y, and z coordinate.
         * Vertices is an array of three coordinates.
         */
      Vector3f Vertices[3];
      Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
      Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
      Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

      /**
       * vertexObjectBuffer is a member GLuint that points to the vertex shader buffer (VBO = vertex buffer object)
       * glGenBuffers makes the space available fort allocating to vertexObjectBuffer
       */
      glGenBuffers(1, &vertexObjectBuffer);

      /**
       * glBindBuffer attaches the buffer (vertexObjectBuffer) as a space to be used for Arrayed buffer storage.
       */
      glBindBuffer(GL_ARRAY_BUFFER, vertexObjectBuffer);

      /**
       * glBufferData presents Vertices as the data location from where vertex data will be obtained.
       */
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    };
  case 10:
  case 11:
    return [ & ]() {
      /**
         * Vector3f is a composite data type that consists of an x, y, and z coordinate.
         * Vertices is an array of three coordinates.
         */
      Vector3f Vertices[4];
      Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
      Vertices[1] = Vector3f(0.0f, -1.0f, 1.0f);
      Vertices[2] = Vector3f(1.0f, -1.0f, 0.0f);
      Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);

      /**
       * vertexObjectBuffer is a member GLuint that points to the vertex shader buffer (VBO = vertex buffer object)
       * glGenBuffers makes the space available fort allocating to vertexObjectBuffer
       */
      glGenBuffers(1, &vertexObjectBuffer);

      /**
       * glBindBuffer attaches the buffer (vertexObjectBuffer) as a space to be used for Arrayed buffer storage.
       */
      glBindBuffer(GL_ARRAY_BUFFER, vertexObjectBuffer);

      /**
       * glBufferData presents Vertices as the data location from where vertex data will be obtained.
       */
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    };
  case 12:
  case 13:
  case 14:
  case 15:
    return [ & ]() {
      /**
         * Vector3f is a composite data type that consists of an x, y, and z coordinate.
         * Vertices is an array of three coordinates.
         */
      Vector3f Vertices[4];
      Vertices[0] = Vector3f(-1.0f, -1.0f, 0.5773f);
      Vertices[1] = Vector3f(0.0f, -1.0f, -1.15475f);
      Vertices[2] = Vector3f(1.0f, -1.0f, 0.5773f);
      Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);

      /**
       * vertexObjectBuffer is a member GLuint that points to the vertex shader buffer (VBO = vertex buffer object)
       * glGenBuffers makes the space available fort allocating to vertexObjectBuffer
       */
      glGenBuffers(1, &vertexObjectBuffer);

      /**
       * glBindBuffer attaches the buffer (vertexObjectBuffer) as a space to be used for Arrayed buffer storage.
       */
      glBindBuffer(GL_ARRAY_BUFFER, vertexObjectBuffer);

      /**
       * glBufferData presents Vertices as the data location from where vertex data will be obtained.
       */
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    };
  case 16:
    return [ & ]() {
      /**
         * Vector3f is a composite data type that consists of an x, y, and z coordinate.
         * Vertices is an array of three coordinates.
         */
      Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
                             Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
                             Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
                             Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f))
                           };

      /**
       * vertexObjectBuffer is a member GLuint that points to the vertex shader buffer (VBO = vertex buffer object)
       * glGenBuffers makes the space available fort allocating to vertexObjectBuffer
       */
      glGenBuffers(1, &vertexObjectBuffer);

      /**
       * glBindBuffer attaches the buffer (vertexObjectBuffer) as a space to be used for Arrayed buffer storage.
       */
      glBindBuffer(GL_ARRAY_BUFFER, vertexObjectBuffer);

      /**
       * glBufferData presents Vertices as the data location from where vertex data will be obtained.
       */
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    };
  }
}

void Tutorial::initGlew()
{
  /// Initialize Glew
  GLenum res = glewInit();
  assert(res == GLEW_OK);
}

void Tutorial::setWindowSize(int width, int height)
{
  _width = width;
  _height = height;
  glutInitWindowSize(_width, _height);
}

void Tutorial::setWindowLocation(int topLeftX, int topLeftY)
{
  _startX = topLeftX;
  _startY = topLeftY;
  glutInitWindowPosition(_startX, _startY);
}

int Tutorial::createWindow(int tutorialID)
{
  char title[40];

  sprintf(&title[0], "Tutorial %d", tutorialID);
  int newGlutWindow = glutCreateWindow(title);
  _myWindows.insert(newGlutWindow);

  return newGlutWindow;
}

void Tutorial::renderFunction()
{
  if (_displayFunc != nullptr) {
    _displayFunc();
  }
}

void Tutorial::idleFunction()
{
  if (_idleFunc != nullptr) {
    _idleFunc();
  }
}

void Tutorial::initGlut()
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
    _pGameCamera = nullptr;
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
    setWindowSize(WINDOW_WIDTH_1_14, WINDOW_HEIGHT_1_14);
    _pGameCamera = new Camera(WINDOW_WIDTH_1_14, WINDOW_HEIGHT_1_14);
    break;
  case 15:
    setWindowSize(WINDOW_WIDTH_15_17, WINDOW_HEIGHT_15_17);
    _pGameCamera = new Camera(WINDOW_WIDTH_15_17, WINDOW_HEIGHT_15_17);
    break;
  case 16:
    setWindowSize(WINDOW_WIDTH_16, WINDOW_HEIGHT_16);
    _pGameCamera = new Camera(WINDOW_WIDTH_16, WINDOW_HEIGHT_16);
    break;
  case 17:
  case 18:
  case 19:
  case 20:
      return;
  default:
    setWindowSize(WINDOW_WIDTH_1_14, WINDOW_HEIGHT_1_14);
    _pGameCamera = new Camera(WINDOW_WIDTH_1_14, WINDOW_HEIGHT_1_14);
    break;
  }

  setWindowLocation();
  createWindow(_tutorialID);


  glutDisplayFunc(renderFunction);
  glutIdleFunc(idleFunction);
  glutSpecialFunc(specialKeyboardCB);
  glutKeyboardFunc(keyboardCB);
  glutPassiveMotionFunc(passiveMouseCB);

  if (_tutorialID == 15 || _tutorialID == 17) {
    glutGameModeString("1920x1080@24");
    glutEnterGameMode();
  }
  else if (_tutorialID == 16) {
    glutGameModeString("1280x1024@24");
  }
}

void Tutorial::Run()
{
#ifdef __TUT_VERSION

#if __TUT_VERSION >= 17
  if (_tutorialID >= 17) {
    char windowName[255];
    sprintf(&windowName[0], "Tutorial %d", _tutorialID);
    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, windowName)) {
      return;
    }
#if __TUT_VERSION == 17
    _tutorial = new Tutorial17();
#elif __TUT_VERSION == 18
    _tutorial = new Tutorial18();
#elif __TUT_VERSION == 19
    _tutorial = new Tutorial19();
#elif __TUT_VERSION == 20
    _tutorial = new Tutorial20();
#endif

    if (!_tutorial->Init(pVSFileName, pFSFileName)) {
      return;
    }

    char* version = (char*)glGetString(GL_VERSION);
    fprintf(stdout, "Version: '%s'\n", version);
    _tutorial->Run();
    delete _tutorial;
    return;
  }
#endif

#endif



  initGlut();
  initGlew();

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  if (_tutorialID == 16) {
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
  }

  char* version = (char*)glGetString(GL_VERSION);
  fprintf(stdout, "Version: '%s'\n", version);

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

  if (_tutorialID == 16) {
    glUniform1i(_gSampler, 0);

    _pTexture = new Texture(GL_TEXTURE_2D, "../Content/test.png");

    if (!_pTexture->Load()) {
      exit(1);
    }
  }

  ///
  /// Setup the perspective projection information.
  ///
  _gPersProjInfo.FOV = 60.0f;
  _gPersProjInfo.Height = WINDOW_HEIGHT_1_14;
  _gPersProjInfo.Width = WINDOW_WIDTH_1_14;
  _gPersProjInfo.zNear = 1.0f;
  _gPersProjInfo.zFar = 100.0f;

  ///
  /// Start the rendering loop.
  ///
  glutMainLoop();
}

void Tutorial::createVertexBuffer()
{
  if (_createVertexBuffer != nullptr) {
    _createVertexBuffer();
  }
}

void Tutorial::compileShaders()
{
  if (_compileShaders != nullptr) {
    _compileShaders();
  }
}

void Tutorial::aAddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
  if (_addShaderFunc != nullptr) {
    _addShaderFunc(ShaderProgram, pShaderText, ShaderType);
  }
}

void Tutorial::createIndexBuffer()
{
  if (_createIndexBuffer != nullptr) {
    _createIndexBuffer();
  }
}

void Tutorial::specialKeyboardCB(int Key, int x, int y)
{
  if (_specialFunc != nullptr) {
    _specialFunc(Key, x, y);
  }
}

void Tutorial::keyboardCB(unsigned char Key, int x, int y)
{
  if (_keyboardFunc != nullptr) {
    _keyboardFunc(Key, x, y);
  }
}

void Tutorial::passiveMouseCB(int x, int y)
{
  if (_passiveMouseFunc != nullptr) {
    _passiveMouseFunc(x, y);
  }
}

