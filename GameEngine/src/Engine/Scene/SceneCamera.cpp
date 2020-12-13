#include "ngpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographicSize(float size)
	{
		m_OrthographicSize = size;
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographicNearClip(float nearClip)
	{
		m_OrthographicNear = nearClip;
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographicFarClip(float farClip)
	{
		m_OrthographicFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float verticalFov, float nearClip, float farClip)
	{
		m_ProjectionjectionType = ProjectionType::Perspective;
		m_PerspectiveFOV = verticalFov;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::SetPerspectiveVerticalFOV(float verticalFov)
	{
		m_PerspectiveFOV = verticalFov;
		RecalculateProjection();
	}

	void SceneCamera::SetPerspectiveNearClip(float nearClip)
	{
		m_PerspectiveNear = nearClip;
		RecalculateProjection();
	}

	void SceneCamera::SetPerspectiveFarClip(float farClip)
	{
		m_PerspectiveFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetProjectionType(ProjectionType type)
	{
		m_ProjectionjectionType = type;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_ProjectionjectionType == ProjectionType::Perspective)
		{
			m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
		else /* m_ProjectionjectionType == ProjectionType::Orthographic */
		{
			float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoBottom = -m_OrthographicSize * 0.5f;
			float orthoTop = m_OrthographicSize * 0.5f;

			m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
		}
	}
}
