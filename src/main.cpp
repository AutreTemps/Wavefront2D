#include <log.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>

#define WF2_GL_CALL(func, ...)                                          \
    if (func)                                                           \
        func(__VA_ARGS__);                                              \
    else                                                                \
        throw(std::runtime_error("GL function does not exist"))

int main(int argc, char* argv[])
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Wavefront 2D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        Log::Error("Failed to initialize OpenGL context");
        return -1;
    }

    Log::Info("OpenGL version {}.{}", GLVersion.major, GLVersion.minor);

    while (!glfwWindowShouldClose(window))
    {
        WF2_GL_CALL(glClearColor, 0, 255, 0, 255);

        WF2_GL_CALL(glClear, GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
