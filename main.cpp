#include <iostream>
#include <iterator>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include "HGL/include/Window.hpp"
#include "HGL/include/VertexBuffer.hpp"
#include "HGL/include/Shader.hpp"
#include "HGL/include/IndexBuffer.hpp"
#include "HGL/include/Texture.hpp"
#include <print>
#include <string>
#include "HGL/include/VertexBufferLayout.hpp"
#include "HGL/include/VertexArray.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec4 vertices[] = 
{
    glm::vec4(0.5f, 0.5f, 1.0f, 1.0f), // top right
    glm::vec4(0.5f, -0.5f, 1.0f, 0.0f), // bottom right
    glm::vec4(-0.5f, -0.5f, 0.0f, 0.0f), // bottom left
    glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f) // top left
};
uint32_t indices[] = {0, 1, 3, 1, 2, 3};
int main(void)
{
    HGL::WindowProperties windowProperties;
    windowProperties.Width = 800;
    windowProperties.Height = 800;
    HGL::WindowError err;
    HGL::Window window(windowProperties, err);
    if(err != HGL::WindowError::NONE)
    {
        std::println("window done fuked up");
    }
    glClearColor(0.3f, 0.7f , 0.5f, 1.0f);
    HGL::VertexArray VAO;
    VAO.Bind();

    HGL::VertexBuffer vb(vertices, sizeof(vertices), HGL::VertexBuffer::Usage::STATIC_DRAW);
    vb.Bind();

    HGL::VertexBufferLayout vbl;
    vbl.AddElements<float, 2>(); // vertex pos
    vbl.AddElements<float, 2>();   //tex cords
    
    VAO.SetVertexBufferLayout(vbl);
    

    HGL::IndexBuffer ib(indices, 6, HGL::IndexBuffer::Usage::STATIC_DRAW);
    HGL::Shader shader("vertex.glsl", "fragment.glsl");
    if(shader.GetStatus().ErrorCode != HGL::ShaderError::ERROR_NONE)
    {
        std::println("Shader Error: {}", shader.GetStatus().ErrorMessage);
    }

    glm::mat4 transform(1.0f);
    

    shader.Bind();

    HGL::Texture2D tex("brick.jpg");
    tex.Bind(0);
    shader.SetUniform<int>(std::string_view("u_TexSlot"), 0);
    
    float delta = 0;
    while(!window.ShouldClose()) 
    {
        double begin = glfwGetTime();

        transform = glm::rotate(transform, glm::radians(30.0f * delta), glm::vec3(1.0, 0.1, 1.0));
        shader.SetUniformMat<float, 4>(std::string_view("u_Transform"), glm::value_ptr(transform), 1, false);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(uint32_t), GL_UNSIGNED_INT, nullptr);
        window.SwapBuffers();
        window.PollEvents();
        double end = glfwGetTime();
        //std::println("FPS: {}", 1.0 / (end - begin));
        delta = begin - end;
    }
}