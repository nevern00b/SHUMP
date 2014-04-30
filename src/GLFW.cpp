#include "GLFW.h"

#include <time.h>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include "Common.h"
#include "Globals.h"
#include "UIManager.h"
#include "Game/StateMachine.h"

void glfwErrorCallback(int error, const char* description)
{
	fputs(description, stderr);
}

void glfwKeyEvent(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
	Globals::m_uiManager->keyEvent(key, action, modifiers);
}

void glfwMouseEvent(GLFWwindow* window, int button, int action, int modifiers)
{
	Globals::m_uiManager->mouseEvent(button, action, modifiers);
}

void glfwMouseMove(GLFWwindow* window, double x, double y)
{
	Globals::m_uiManager->mouseMove((int)glm::floor(x), (int)glm::floor(y));
}

void glfwResizeWindow(GLFWwindow* window, int width, int height)
{
	Globals::m_uiManager->resizeWindow(width, height);
}

void glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
	char debSource[32], debType[32], debSev[32];
	if (source == GL_DEBUG_SOURCE_API_ARB)
		strcpy(debSource, "OpenGL");
	else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
		strcpy(debSource, "Windows");
	else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
		strcpy(debSource, "Shader Compiler");
	else if (source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
		strcpy(debSource, "Third Party");
	else if (source == GL_DEBUG_SOURCE_APPLICATION_ARB)
		strcpy(debSource, "Application");
	else if (source == GL_DEBUG_SOURCE_OTHER_ARB)
		strcpy(debSource, "Other");

	if (type == GL_DEBUG_TYPE_ERROR_ARB)
		strcpy(debType, "error");
	else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)
		strcpy(debType, "deprecated behavior");
	else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)
		strcpy(debType, "undefined behavior");
	else if (type == GL_DEBUG_TYPE_PORTABILITY_ARB)
		strcpy(debType, "portability");
	else if (type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
		strcpy(debType, "performance");
	else if (type == GL_DEBUG_TYPE_OTHER_ARB)
		strcpy(debType, "message");

	if (severity == GL_DEBUG_SEVERITY_HIGH_ARB)
		strcpy(debSev, "high");
	else if (severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
		strcpy(debSev, "medium");
	else if (severity == GL_DEBUG_SEVERITY_LOW_ARB)
		strcpy(debSev, "low");

	fprintf(stderr, "%s: %s(%s) %d: %s\n", debSource, debType, debSev, id, message);
}

GLFW::GLFW()
{
	// Set variables
	std::string applicationName("SHUMP");
	glm::uvec2 windowSize(1280, 720);
	glm::uvec2 openGLVersion(3, 3);
	glm::uvec4 colorBits(8, 8, 8, 0); // We only use alpha on custom FBOs (default value is 8 bits)
	glm::uvec2 depthStencilBits(24, 0);
	bool vsync = false;
	bool showDebugOutput = false;
	bool resizable = true;
	srand((uint)time(NULL));

	glfwSetErrorCallback(glfwErrorCallback);

	// Initialize glfw 
	glfwInit();

	// Window hints must be set before creating a new window
	glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE); // GL_FALSE = window initially minimized
	glfwWindowHint(GLFW_DECORATED, GL_TRUE); // GL_FALSE = window has no title bar and close button
	glfwWindowHint(GLFW_RED_BITS, colorBits.r);
	glfwWindowHint(GLFW_GREEN_BITS, colorBits.g);
	glfwWindowHint(GLFW_BLUE_BITS, colorBits.b);
	glfwWindowHint(GLFW_ALPHA_BITS, colorBits.a);
	glfwWindowHint(GLFW_DEPTH_BITS, depthStencilBits.x);
	glfwWindowHint(GLFW_STENCIL_BITS, depthStencilBits.y);
	glfwWindowHint(GLFW_SAMPLES, 0); // Number of samples for multisampling
	glfwWindowHint(GLFW_STEREO, GL_FALSE); // Stereoscopic rendering
	glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGLVersion.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGLVersion.y);
	glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS); // Has to do with making OpenGL calls safe. We disable this.
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Removes deprecated OpenGL features
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, showDebugOutput ? GL_TRUE : GL_FALSE); // Allow debug output
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Set window properties
	GLFWwindow* window = glfwCreateWindow(windowSize.x, windowSize.y, applicationName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(vsync ? 1 : 0);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetTime(0.0);

	// gl3w is initialized after glfw because it needs an active OpenGL context to work
	gl3wInit();


	// Debug output
	if (showDebugOutput && glfwExtensionSupported("GL_ARB_debug_output"))
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		glDebugMessageCallbackARB((GLDEBUGPROCARB)&glDebugOutput, NULL);
	}


	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Put this here for cross-platform purposes
	Globals::init(0.0, windowSize.x, windowSize.y);

	// Set glfw window callbacks to UIManager
	glfwSetKeyCallback(window, glfwKeyEvent);
	glfwSetMouseButtonCallback(window, glfwMouseEvent);
	glfwSetCursorPosCallback(window, glfwMouseMove);
	glfwSetWindowSizeCallback(window, glfwResizeWindow);


	const uint fpsDelay = 20; // Spit out fps every 20 frames
	uint fpsFrames = 0;
	float fpsAvg = 0;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		float time = (float)glfwGetTime();
        Globals::render();
		Globals::update(time);
		glfwSwapBuffers(window);

		// FPS
		float fps = 1.0f / Globals::m_uiManager->m_frameTime;
		fpsFrames++;
		fpsAvg += fps;
		if (fpsFrames == fpsDelay)
		{
			fpsFrames = 0;
			fpsAvg /= fpsDelay;
			fpsAvg = glm::round(fpsAvg);
			std::stringstream iss;
			iss << "FPS: ";
			iss << fpsAvg;
			iss << " Score: ";
			iss << Globals::m_stateMachine->p_score;
			glfwSetWindowTitle(window, iss.str().c_str());
			fpsAvg = 0.0f;
		}
	}

	Globals::destroy();

	glfwDestroyWindow(window);
	glfwTerminate();

}

GLFW::~GLFW()
{

}