/*

Obed Gonzalez A01382900
Victor Hugo Oyervides A01382836

*/



#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

using namespace std;

void keyMovement(GLFWwindow* window, int key, int scancode, int action, int mods);
void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

//Punto (0,0) en pantalla
GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
GLfloat halfScreenDepth = -500;

//Setea Rotacion en figura
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;


//Punto en forma inicial
GLfloat moveX = SCREEN_WIDTH / 2;
GLfloat moveY = SCREEN_HEIGHT / 2;
GLfloat moveZ = SCREEN_WIDTH / 2;
GLfloat edge_length = 10;
GLenum mode = GL_QUADS;
GLenum fill_mode = GL_FILL;

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snail", NULL, NULL);

    //Funcion que detecta cuando el teclado es presionado
    glfwSetKeyCallback(window, keyMovement);

    //??
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment

    //Acciones
    cout << "Arriba, abajo, izquierda y derecha: Rotate object\n";
    cout << "W, A, S, D: Mover objeto\n";
    cout << "N y M: Escala Objeto\n";
    cout << "X: Renderea puntos\n";
    cout << "C: Renderea lineas\n";
    cout << "V: Renderea triangulos\n";
    cout << "B: Renderea quads\n";
    cout << "Z: Cambia entre lineas y llenar\n";

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render OpenGL here
        glPopMatrix();

        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, halfScreenDepth);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-halfScreenWidth, -halfScreenHeight, -halfScreenDepth);
        // glScalef();

        DrawCube(halfScreenWidth, halfScreenHeight, halfScreenDepth, edge_length);
        glPopMatrix();


        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}



void keyMovement(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << key << std::endl;

    const GLfloat rotationSpeed = 10;
    const GLfloat moveSpeed = 10;

    // actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            rotationX -= rotationSpeed;
            break;
        case GLFW_KEY_DOWN:
            rotationX += rotationSpeed;
            break;
        case GLFW_KEY_RIGHT:
            rotationY += rotationSpeed;
            break;
        case GLFW_KEY_LEFT:
            rotationY -= rotationSpeed;
            break;
        case GLFW_KEY_W:
            halfScreenHeight = moveSpeed + halfScreenHeight;
            break;
        case GLFW_KEY_S:
            halfScreenHeight = halfScreenHeight - moveSpeed;
            break;
        case GLFW_KEY_D:
            halfScreenWidth = moveSpeed + halfScreenWidth;
            break;
        case GLFW_KEY_J:
            halfScreenDepth += moveSpeed;
            break;
        case GLFW_KEY_K:
            halfScreenDepth -= moveSpeed;
            break;
        case GLFW_KEY_A:
            halfScreenWidth = halfScreenWidth - moveSpeed;
            break;
        case GLFW_KEY_N:
            edge_length -= 1;
            break;
        case GLFW_KEY_M:
            edge_length += 1;
            break;
        case GLFW_KEY_X:
            mode = GL_POINTS;
            break;
        case GLFW_KEY_C:
            mode = GL_LINES;
            break;
        case GLFW_KEY_V:
            mode = GL_TRIANGLES;
            break;
        case GLFW_KEY_B:
            mode = GL_QUADS;
            break;
        case GLFW_KEY_Z:
            if (fill_mode == GL_FILL) {
                fill_mode = GL_LINE;
            }
            else {
                fill_mode = GL_FILL;
            }
            break;
        }


    }
}

void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength)
{
    // Plataforma
    GLfloat platformWidthLength = edgeLength * 5.0f; // y
    GLfloat platformHeightLength = edgeLength * 40.0f; // x

    GLfloat platformSideWidthLength = edgeLength * 5.0f; // y
    GLfloat platformSideHeightLength = edgeLength * 20.0f; // z

    // Pipas
    GLfloat pipeLengthWidthLength = platformHeightLength * 0.4f; // x
    GLfloat pipeHeight = edgeLength * 10.0f; // y
    GLfloat pipeLength = platformSideHeightLength - edgeLength; // z

    // Bloque
    GLfloat blockWidth = platformHeightLength * 0.2f; // x
    GLfloat blockHeight = edgeLength * 10.0f; // y
    GLfloat blockDepth = platformSideHeightLength - (edgeLength * 3.0f) - 50; // z






    GLfloat vertices[] = {
        /*
        
            Plataforma
        
        */

        // front face
        centerPosX - platformHeightLength, centerPosY + platformWidthLength, centerPosZ + platformSideHeightLength, // top left
        centerPosX + platformHeightLength, centerPosY + platformWidthLength, centerPosZ + platformSideHeightLength, // top right
        centerPosX + platformHeightLength, centerPosY - platformWidthLength, centerPosZ + platformSideHeightLength, // bottom right
        centerPosX - platformHeightLength, centerPosY - platformWidthLength, centerPosZ + platformSideHeightLength, // bottom left
        /*
        
            Backdrop

        */
        centerPosX - platformHeightLength, centerPosY + platformWidthLength + 300, centerPosZ - platformSideHeightLength, // top left
        centerPosX + platformHeightLength, centerPosY + platformWidthLength + 300, centerPosZ - platformSideHeightLength, // top right
        centerPosX + platformHeightLength, centerPosY - platformWidthLength, centerPosZ - platformSideHeightLength, // bottom right
        centerPosX - platformHeightLength, centerPosY - platformWidthLength, centerPosZ - platformSideHeightLength, // bottom left

        /*
        
            Lateral Plataforma
        
        */
        // left face
        centerPosX - platformHeightLength, centerPosY + platformSideWidthLength, centerPosZ + platformSideHeightLength, // top left
        centerPosX - platformHeightLength, centerPosY + platformSideWidthLength, centerPosZ - platformSideHeightLength, // top right
        centerPosX - platformHeightLength, centerPosY - platformSideWidthLength, centerPosZ - platformSideHeightLength, // bottom right
        centerPosX - platformHeightLength, centerPosY - platformSideWidthLength, centerPosZ + platformSideHeightLength, // bottom left

        // right face
        centerPosX + platformHeightLength, centerPosY + platformSideWidthLength, centerPosZ + platformSideHeightLength, // top left
        centerPosX + platformHeightLength, centerPosY + platformSideWidthLength, centerPosZ - platformSideHeightLength, // top right
        centerPosX + platformHeightLength, centerPosY - platformSideWidthLength, centerPosZ - platformSideHeightLength, // bottom right
        centerPosX + platformHeightLength, centerPosY - platformSideWidthLength, centerPosZ + platformSideHeightLength, // bottom left

        // top face
        centerPosX - platformHeightLength, centerPosY + platformSideWidthLength, centerPosZ + platformSideHeightLength, // top left
        centerPosX - platformHeightLength, centerPosY + platformSideWidthLength, centerPosZ - platformSideHeightLength, // top right
        centerPosX + platformHeightLength, centerPosY + platformSideWidthLength, centerPosZ - platformSideHeightLength, // bottom right
        centerPosX + platformHeightLength, centerPosY + platformSideWidthLength, centerPosZ + platformSideHeightLength, // bottom left

        // bottom face
        centerPosX - platformHeightLength, centerPosY - platformSideWidthLength, centerPosZ + platformSideHeightLength, // top left
        centerPosX - platformHeightLength, centerPosY - platformSideWidthLength, centerPosZ - platformSideHeightLength, // top right
        centerPosX + platformHeightLength, centerPosY - platformSideWidthLength, centerPosZ - platformSideHeightLength, // bottom right
        centerPosX + platformHeightLength, centerPosY - platformSideWidthLength, centerPosZ + platformSideHeightLength,  // bottom left

        /*
        
            Pipas
        
        */
        // Left //
        // front face
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength, // top left
        centerPosX - pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength, // top right
        centerPosX - pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength, // bottom right
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength, // bottom left

        // back face
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top left
        centerPosX - pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top right
        centerPosX - pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // bottom right
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // bottom left

        // top face
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength, // top left
        centerPosX - pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength, // top right
        centerPosX - pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top right
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top left

        // bottom face
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength, // top left
        centerPosX - pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength, // top right
        centerPosX - pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // top right
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // top left

        // right side
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength, // top left
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength, // bottom left
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // bottom left
        centerPosX - pipeLengthWidthLength - (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top left

        // left side
        centerPosX - pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength, // top right
        centerPosX - pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength, // bottom right
        centerPosX - pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // bottom right
        centerPosX - pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top right


        // Right //
        // front face
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength, // top left
        centerPosX + pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength, // top right
        centerPosX + pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength, // bottom right
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength, // bottom left

        // back face
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top left
        centerPosX + pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top right
        centerPosX + pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // bottom right
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // bottom left

        // top face
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength, // top left
        centerPosX + pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength, // top right
        centerPosX + pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top right
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top left

        // bottom face
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength, // top left
        centerPosX + pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength, // top right
        centerPosX + pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // top right
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // top left

        // right side
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength, // top left
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength, // bottom left
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // bottom left
        centerPosX + pipeLengthWidthLength + (platformHeightLength * 0.2f), centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top left

        // Left side
        centerPosX + pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength, // top right
        centerPosX + pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength, // bottom right
        centerPosX + pipeLengthWidthLength, centerPosY + platformWidthLength, centerPosZ + pipeLength - edgeLength, // bottom right
        centerPosX + pipeLengthWidthLength, centerPosY + pipeHeight, centerPosZ + pipeLength - edgeLength, // top right


        /*
        
            Bloques
        
        */
        // Left //
        // front face
        centerPosX - (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top left
        centerPosX - blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top right
        centerPosX - blockWidth, centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // bottom right
        centerPosX - (blockWidth * 4.0f), centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // bottom left

        // back face
        centerPosX - (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // top left
        centerPosX - blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // top right
        centerPosX - blockWidth, centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom right
        centerPosX - (blockWidth * 4.0f), centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom left

        // top face
        centerPosX - (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top left
        centerPosX - blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top right
        centerPosX - blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // bottom right
        centerPosX - (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // bottom left

        // bottom face
        centerPosX - (blockWidth * 4.0f), centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // top left
        centerPosX - blockWidth, centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // top right
        centerPosX - blockWidth, centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom right
        centerPosX - (blockWidth * 4.0f), centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom left

        // left face
        centerPosX - (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top left
        centerPosX - (blockWidth * 4.0f), centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // bottom left
        centerPosX - (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top right
        centerPosX - (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // bottom left

        //right face
        centerPosX - blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top right
        centerPosX - blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // bottom right
        centerPosX - blockWidth, centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom right
        centerPosX - blockWidth, centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // top right

        // Right //
        // front face
        centerPosX + (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top left
        centerPosX + blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top right
        centerPosX + blockWidth, centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // bottom right
        centerPosX + (blockWidth * 4.0f), centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // bottom left

        // back face
        centerPosX + (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // top left
        centerPosX + blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // top right
        centerPosX + blockWidth, centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom right
        centerPosX + (blockWidth * 4.0f), centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom left

        // top face
        centerPosX + (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top left
        centerPosX + blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top right
        centerPosX + blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // bottom right
        centerPosX + (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // bottom left

        // bottom face
        centerPosX + (blockWidth * 4.0f), centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // top left
        centerPosX + blockWidth, centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // top right
        centerPosX + blockWidth, centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom right
        centerPosX + (blockWidth * 4.0f), centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom left

        // left face
        centerPosX + (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), (centerPosZ + platformSideHeightLength + 0.1f) - 300, // top left
        centerPosX + (blockWidth * 4.0f), centerPosY + blockHeight, (centerPosZ + platformSideHeightLength + 0.1f) - 300, // bottom left
        centerPosX + (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), (centerPosZ + platformSideHeightLength + 0.1f) - 300, // top left
        centerPosX + (blockWidth * 4.0f), centerPosY + (blockHeight * 2.0f), (centerPosZ + blockDepth + 0.1f) - 300, // bottom left

        //right face
        centerPosX + blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + platformSideHeightLength - 300, // top right
        centerPosX + blockWidth, centerPosY + (blockHeight * 2.0f), centerPosZ + blockDepth - 300, // bottom right
        centerPosX + blockWidth, centerPosY + blockHeight, centerPosZ + blockDepth - 300, // bottom right
        centerPosX + blockWidth, centerPosY + blockHeight, centerPosZ + platformSideHeightLength - 300, // top right

    };

    //Se obtienen los valores RGB que se quieren usar, se dividen entre 255 y se repiten los valores 3 veces para pintar una cara (12 en total)
    GLfloat color[] = {

        //Frente plataforma
        .6, 0.2862745098, 0, .6, 0.2862745098, 0, .6, 0.2862745098, 0, .6, 0.2862745098, 0,
        
        //Backdrop
        0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1,

        // body
        .4, .2, 0, .4, .2, 0, .4, .2, 0, .4, .2, 0,  // back face
        .4, .2, 0, .4, .2, 0, .4, .2, 0, .4, .2, 0,  // back face
        .4, .2, 0, .4, .2, 0, .4, .2, 0, .4, .2, 0,  // back face
        .4, .2, 0, .4, .2, 0, .4, .2, 0, .4, .2, 0,  // back face

        //Pipas
        // left
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, // front face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // back face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // top face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // bottom face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // bottom face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // bottom face
        // right
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, // front face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // back face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // top face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // bottom face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // bottom face
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // bottom face
        
        //Bloques
        // left
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // front face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // back face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // top face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // bottom face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // bottom face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // bottom face
        // right
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // front face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // back face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // top face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // bottom face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // bottom face
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, // bottom face

    };


    glPolygonMode(GL_FRONT_AND_BACK, fill_mode);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, color);
    glDrawArrays(mode, 0, 156);
    glDisableClientState(GL_DEPTH_TEST);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
