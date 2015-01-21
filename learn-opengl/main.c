#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>

void PrintKey(int scancode, bool down)
{
    if (down)
        printf("%i\n", scancode);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    int w = 800;
    int h = 600;

    SDL_Window *window = SDL_CreateWindow("OpenGL", 100, 100, w, h, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    SDL_Event event;

    while (true)
    {
        if (SDL_PollEvent(&event))
        {
            uint32_t t = event.type;
            switch (t)
            {
                case SDL_QUIT:
                    return 0;

                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        default:
                            PrintKey((int)event.key.keysym.sym, t == SDL_KEYDOWN);
                            break;
                    }
            }
        }
        
        float verts[] =
        {
            0.0f,  0.5f,
            0.5f, -0.5f,
            -0.5f, -0.5f
        };
        
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.5, 0.7, 0);

        SDL_GL_SwapWindow(window);
    }
    
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}
