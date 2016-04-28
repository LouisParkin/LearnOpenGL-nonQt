#include "Tutorial.h"

Tutorial::Tutorial(int tutorialId, int* argc, char* argv[]) : Tutorials(argc, argv)
{
  _tutorialID = tutorialId;
  sprintf(pVSFileName, "/home/lparkin/Projects/S3/LearnOpenGL-nonQt/Tutorial%d/shader.vs", _tutorialID);
  sprintf(pFSFileName, "/home/lparkin/Projects/S3/LearnOpenGL-nonQt/Tutorial%d/shader.fs", _tutorialID);
  _createVertexBuffer = makeCreateVertexBufferFunc(&_VBO);
  _createIndexBuffer = makeCreateIndexBufferFunc(&_IBO);
  _compileShaders = makeCompileShadersFunc();
  _displayFunc = makeDisplayFunc();
  _idleFunc = makeIdleFunc();
  _specialFunc = makeSpecialFunc();
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
    return [ = ]() {
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

      AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
      AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

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
    return [ = ]() {
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
      AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
      AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

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
    return [ = ]() {
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
      AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
      AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

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
    return [ = ]() {
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
      AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
      AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

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
    return [ = ]() {
      glClear(GL_COLOR_BUFFER_BIT);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, _VBO);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);

      glutSwapBuffers();
    };
  case 5:
    return [ = ]() {
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
    return [ = ]() {
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
    return [ = ]() {
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
    return [ = ]() {
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
    return [ = ]() {
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
    return [ = ]() {
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
    return [ = ]() {
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
    return [ = ]() {
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
    return [ = ]() {
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
    return [ = ]() {
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
    return makeDisplayFunc();
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
    return [=](int Key, int x, int y) {
      OGLDEV_KEY OgldevKey = GLUTKeyToOGLDEVKey(Key);
      _pGameCamera->OnKeyboard(OgldevKey);
    };
  }
}

std::function<void (void)> Tutorial::makeCreateIndexBufferFunc(GLuint* indexObjectBuffer)
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
    return [ = ]() {
      unsigned int Indices[] = { 0, 3, 1,
                                 1, 3, 2,
                                 2, 3, 0,
                                 0, 1, 2
                               };

      glGenBuffers(1, indexObjectBuffer);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexObjectBuffer);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    };

  }
}

std::function<void (void)> Tutorial::makeCreateVertexBufferFunc(GLuint* vertexObjectBuffer)
//auto Tutorial::makeCreateVertexBufferFunc(GLuint* vertexObjectBuffer) -> decltype( void(*)() )
{
  switch (_tutorialID) {
  case 1:
  case 2:
  case 3:
    return nullptr;
  case 4:
    return [ = ]() {
      Vector3f Vertices[3];
      Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
      Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
      Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

      glGenBuffers(1, vertexObjectBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, *vertexObjectBuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    };
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
    return [ = ]() {
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
      glGenBuffers(1, vertexObjectBuffer);

      /**
       * glBindBuffer attaches the buffer (vertexObjectBuffer) as a space to be used for Arrayed buffer storage.
       */
      glBindBuffer(GL_ARRAY_BUFFER, *vertexObjectBuffer);

      /**
       * glBufferData presents Vertices as the data location from where vertex data will be obtained.
       */
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    };
  case 10:
  case 11:
    return [ = ]() {
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
      glGenBuffers(1, vertexObjectBuffer);

      /**
       * glBindBuffer attaches the buffer (vertexObjectBuffer) as a space to be used for Arrayed buffer storage.
       */
      glBindBuffer(GL_ARRAY_BUFFER, *vertexObjectBuffer);

      /**
       * glBufferData presents Vertices as the data location from where vertex data will be obtained.
       */
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    };
  case 12:
  case 13:
  case 14:
    return [ = ]() {
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
      glGenBuffers(1, vertexObjectBuffer);

      /**
       * glBindBuffer attaches the buffer (vertexObjectBuffer) as a space to be used for Arrayed buffer storage.
       */
      glBindBuffer(GL_ARRAY_BUFFER, *vertexObjectBuffer);

      /**
       * glBufferData presents Vertices as the data location from where vertex data will be obtained.
       */
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    };
  }
}

void Tutorial::run()
{
  auto displayLeapFrog = [](){ _displayFunc(); };
  auto idleLeapFrog = [](){ _idleFunc(); };
  auto specialLeapFrog = [](int key, int x, int y){ _specialFunc(key,x,y); };

  initGlut(displayLeapFrog, idleLeapFrog, specialLeapFrog);
  initGlew();

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  char* version = (char*)glGetString(GL_VERSION);
  fprintf(stdout, "Version: '%s'\n", version);

  Tutorials::run();

  ///
  /// Setup the perspective projection information.
  ///
  _gPersProjInfo.FOV = 60.0f;
  _gPersProjInfo.Height = WINDOW_HEIGHT;
  _gPersProjInfo.Width = WINDOW_WIDTH;
  _gPersProjInfo.zNear = 1.0f;
  _gPersProjInfo.zFar = 100.0f;

  ///
  /// Start the rendering loop.
  ///
  glutMainLoop();
}

void Tutorial::createVertexBuffer()
{
  if(_createVertexBuffer != nullptr)
  {
    _createVertexBuffer();
  }
}

void Tutorial::compileShaders()
{
  if(_compileShaders != nullptr)
  {
    _compileShaders();
  }
}

void Tutorial::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{

}

void Tutorial::createIndexBuffer()
{
  if(_createIndexBuffer != nullptr)
  {
    _createIndexBuffer();
  }
}

void Tutorial::SpecialKeyboardCB(int Key, int x, int y)
{
  if(_specialFunc != nullptr)
  {
    _specialFunc();
  }
}

