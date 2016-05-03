/*

  Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIGHTING_TECHNIQUE_H // #1
#define LIGHTING_TECHNIQUE_H

#include "technique.h"
#include "ogldev_math_3d.h"

#if __TUT_VERSION == 17 // #2
#include "ogldev_lights_common.h"
#elif __TUT_VERSION >= 18  && __TUT_VERSION <= 19 // #2
struct DirectionalLight {
  Vector3f Color;
  float AmbientIntensity;
  Vector3f Direction;
  float DiffuseIntensity;
};

#endif // #2


class LightingTechnique : public Technique
{
public:

  LightingTechnique();

  virtual bool Init(char* pVSFileName, char* pFSFileName);

  void SetWVP(const Matrix4f& WVP);

#if __TUT_VERSION >= 18 && __TUT_VERSION <= 20 // #4
  void SetWorldMatrix(const Matrix4f& WVP);
#endif // #4

  void SetTextureUnit(unsigned int TextureUnit);
  void SetDirectionalLight(const DirectionalLight& Light);

private:

  GLuint m_WVPLocation;
#if __TUT_VERSION >= 18 && __TUT_VERSION <= 20 // #6
  GLuint m_WorldMatrixLocation;
#endif // #6
  GLuint m_samplerLocation;
#if __TUT_VERSION == 17
  GLuint m_dirLightColorLocation;
  GLuint m_dirLightAmbientIntensityLocation;
#elif __TUT_VERSION >= 18  && __TUT_VERSION <= 20 // #9
  struct {
    GLuint Color;
    GLuint AmbientIntensity;
    GLuint Direction;
    GLuint DiffuseIntensity;
  } m_dirLightLocation;
#endif // #9
};


#endif  /* LIGHTING_TECHNIQUE_H */ // #1
