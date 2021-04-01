// Copyright(c) 2021, #Momo
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
// 
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and /or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace VulkanAbstractionLayer
{
    const WindowSurface& CreateVulkanSurface(GLFWwindow* window, const VulkanContext& context);

    Window::Window(const WindowCreateOptions& options)
    {
        if (glfwInit() != GLFW_TRUE)
        {
            if (options.ErrorCallback) 
                options.ErrorCallback("glfw context initialization failed");
            return;
        }
        if (glfwVulkanSupported() != GLFW_TRUE)
        {
            if (options.ErrorCallback) 
                options.ErrorCallback("glfw context does not support Vulkan API");
            return;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_DECORATED, options.TileBar);
        glfwWindowHint(GLFW_RESIZABLE, options.Resizeable);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, options.TransparentFramebuffer);

        this->handle = glfwCreateWindow((int)options.Size.x, (int)options.Size.y, options.Title, nullptr, nullptr);
        if (this->handle == nullptr)
        {
            if(options.ErrorCallback) 
                options.ErrorCallback("glfw window creation failed");
            return;
        }

        glfwSetWindowPos(this->handle, (int)options.Position.x, (int)options.Position.y);
    }

    Window::Window(Window&& other) noexcept
    {
        this->handle = other.handle;
        other.handle = nullptr;
    }

    Window& Window::operator=(Window&& other) noexcept
    {
        this->handle = other.handle;
        other.handle = nullptr;
        
        return *this;
    }

    Window::~Window()
    {
        if (this->handle != nullptr)
        {
            glfwTerminate();
            this->handle = nullptr;
        }
    }

    Window::RequiredExtensions Window::GetRequiredExtensions() const
    {
        RequiredExtensions result;
        result.ExtensionNames = glfwGetRequiredInstanceExtensions(&result.ExtensionCount);
        return result;
    }

    void Window::PollEvents() const
    {
        glfwPollEvents();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(this->handle);
    }

    void Window::SetSize(const Vector2& size)
    {
        glfwSetWindowSize(this->handle, (int)size.x, (int)size.y);
    }

    void Window::SetPosition(const Vector3& position)
    {
        glfwSetWindowPos(this->handle, (int)position.x, (int)position.y);
    }

    const WindowSurface& Window::CreateWindowSurface(const VulkanContext& context)
    {
        return CreateVulkanSurface(this->handle, context);
    }
}