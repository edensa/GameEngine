#include "ngpch.h"
#include "OrthographicCameraController.h"

#include "Events/KeyEvent.h"
#include "Input.h"
#include "KeyCodes.h"

namespace engine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation/* = false*/)
		: m_AspectRatio(aspectRatio)
		, m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
		, m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(ENGINE_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;

		else if (Input::IsKeyPressed(ENGINE_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(ENGINE_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;

		else if (Input::IsKeyPressed(ENGINE_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		if (m_Rotation)
		{
			if (engine::Input::IsKeyPressed(ENGINE_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			else if (engine::Input::IsKeyPressed(ENGINE_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		engine::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<engine::MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<engine::WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	OrthographicCamera& OrthographicCameraController::GetCamera()
	{
		return m_Camera;
	}

	const OrthographicCamera& OrthographicCameraController::GetCamera() const
	{
		return m_Camera;
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	
}
