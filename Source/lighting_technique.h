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

#ifndef LIGHTING_TECHNIQUE_H
#define LIGHTING_TECHNIQUE_H

#include "technique.h"
#include "ogldev_math_3d.h"

#if __TUT_VERSION == 17
#include "ogldev_lights_common.h"
#elif __TUT_VERSION >= 18  && __TUT_VERSION <= 19
struct DirectionalLight {
  Vector3f Color;
  float AmbientIntensity;
  Vector3f Direction;
  float DiffuseIntensity;
};
#elif __TUT_VERSION == 19

#endif


class LightingTechnique : public Technique
{
public:

  LightingTechnique();

  virtual bool Init(char* pVSFileName, char* pFSFileName);

  void SetWVP(const Matrix4f& WVP);

#if __TUT_VERSION >= 18 && __TUT_VERSION <= 19
  void SetWorldMatrix(const Matrix4f& WVP);
#endif

  void SetTextureUnit(unsigned int TextureUnit);
  void SetDirectionalLight(const DirectionalLight& Light);

#if __TUT_VERSION >= 19
  void SetEyeWorldPos(const Vector3f& EyeWorldPos);
  void SetMatSpecularIntensity(float Intensity);
  void SetMatSpecularPower(float Power);
#endif

private:

  GLuint m_WVPLocation;
#if __TUT_VERSION >= 18 && __TUT_VERSION <= 19
  GLuint m_WorldMatrixLocation;
#endif

  GLuint m_samplerLocation;

#if __TUT_VERSION >= 19
  GLuint m_eyeWorldPosLocation;
  GLuint m_matSpecularIntensityLocation;
  GLuint m_matSpecularPowerLocation;
#endif

#if __TUT_VERSION == 17
  GLuint m_dirLightColorLocation;
  GLuint m_dirLightAmbientIntensityLocation;
#elif __TUT_VERSION >= 18  && __TUT_VERSION <= 19
  struct {
    GLuint Color;
    GLuint AmbientIntensity;
    GLuint Direction;
    GLuint DiffuseIntensity;
  } m_dirLightLocation;
#endif
};


#endif  /* LIGHTING_TECHNIQUE_H */
