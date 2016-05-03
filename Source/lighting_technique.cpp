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

#include "lighting_technique.h"


LightingTechnique::LightingTechnique()
{
}

bool LightingTechnique::Init(char* pVSFileName, char* pFSFileName)
{
  if (!Technique::Init(pVSFileName, pFSFileName)) {
    return false;
  }

  if (!AddShader(GL_VERTEX_SHADER, pVSFileName)) {
    return false;
  }

  if (!AddShader(GL_FRAGMENT_SHADER, pFSFileName)) {
    return false;
  }

  if (!Finalize()) {
    return false;
  }

  m_WVPLocation = GetUniformLocation("gWVP");


#if __TUT_VERSION == 18
  m_WorldMatrixLocation = GetUniformLocation("gWorld");
#endif

  m_samplerLocation = GetUniformLocation("gSampler");

#if __TUT_VERSION == 17
  m_dirLightColorLocation = GetUniformLocation("gDirectionalLight.Color");
  m_dirLightAmbientIntensityLocation = GetUniformLocation("gDirectionalLight.AmbientIntensity");

  if (m_dirLightAmbientIntensityLocation == 0xFFFFFFFF ||
      m_WVPLocation == 0xFFFFFFFF ||
      m_samplerLocation == 0xFFFFFFFF ||
      m_dirLightColorLocation == 0xFFFFFFFF) {
    return false;
  }

  return true;
#endif

#if __TUT_VERSION == 18
  m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Color");
  m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.AmbientIntensity");
  m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
  m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.DiffuseIntensity");

  if (m_dirLightLocation.AmbientIntensity == 0xFFFFFFFF ||
      m_WVPLocation == 0xFFFFFFFF ||
      m_WorldMatrixLocation == 0xFFFFFFFF ||
      m_samplerLocation == 0xFFFFFFFF ||
      m_dirLightLocation.Color == 0xFFFFFFFF ||
      m_dirLightLocation.DiffuseIntensity == 0xFFFFFFFF ||
      m_dirLightLocation.Direction == 0xFFFFFFFF) {
    return false;
  }

  return true;
#endif
}

void LightingTechnique::SetWVP(const Matrix4f& WVP)
{
  glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

#if __TUT_VERSION == 18

void LightingTechnique::SetWorldMatrix(const Matrix4f& WorldInverse)
{
  glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}

#endif


void LightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
  glUniform1i(m_samplerLocation, TextureUnit);
}


void LightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
#if __TUT_VERSION == 17
  glUniform3f(m_dirLightColorLocation, Light.Color.x, Light.Color.y, Light.Color.z);
  glUniform1f(m_dirLightAmbientIntensityLocation, Light.AmbientIntensity);
#elif __TUT_VERSION == 18
  glUniform3f(m_dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
  glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
  Vector3f Direction = Light.Direction;
  Direction.Normalize();
  glUniform3f(m_dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
  glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
#endif

}
