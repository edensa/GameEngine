#include "ngpch.h"
#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace engine
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top))
		, m_ViewMatrix(1.0f)
		, m_Position(0.0f)
		, m_Rotation(0.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 iden{ 1.0f };
		glm::vec3 posz{ 0, 0, 1 };
		glm::mat4 transform = glm::translate(iden, m_Position) * glm::rotate(iden, glm::radians(m_Rotation), posz);
		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
