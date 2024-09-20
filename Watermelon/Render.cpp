#include "Render.h"

#include <iostream>

#include "TextureManager.h"

// Global variables
unsigned int Render::glObject_FruitShaderProgram;
unsigned int Render::glObject_FruitVertexBuffer;
unsigned int Render::glObject_FruitVertexArray;
unsigned int Render::glObject_ScoreTextShaderProgram;
unsigned int Render::glObject_ScoreTextVertexBuffer;
unsigned int Render::glObject_ScoreTextVertexArray;
unsigned int Render::glObject_UICompShaderProgram;
unsigned int Render::glObject_UICompVertexBuffer;
unsigned int Render::glObject_UICompVertexArray;

unsigned int Render::glUniformLocation_FruitTrans;
unsigned int Render::glUniformLocation_FruitColor;
unsigned int Render::glUniformLocation_ScoreTextTrans;
unsigned int Render::glUniformLocation_ScoreTextNumberIndex;
unsigned int Render::glUniformLocation_UICompTrans;
unsigned int Render::glUniformLocation_UICompColor;

GLFWwindow* renderInit(int width, int height, const char* title)
{
    if (!initializeGlfw())
    {
        std::cerr << "Failed to initialize OpenGL\n";
        return NULL;
    }

    GLFWwindow* glWindow = glCreateWindow(width, height, title);

    if (!initializeGlad())
    {
        std::cerr << "Failed to initialize GLAD\n";
        return NULL;
    }

    if (height >= width)
    {
        // Vertical or square window
        glViewport((width - height) / 2, 0, height, height);
    }
    else
    {
        // Horizontal window
        glViewport(0, (height - width) / 2, width, width);
    }

    Render::initializeBuffers();
    Render::initializeShaders();
    Render::getUniformLocations();

    // Enable alpha blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return glWindow;
}

bool initializeGlfw()
{
    if (glfwInit() == GL_FALSE) return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}

bool initializeGlad()
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

GLFWwindow* glCreateWindow(int width, int height, const char* title)
{
    GLFWwindow* window = glfwCreateWindow(width, height, "Watermelon", NULL, NULL);
    if (window != NULL)
    {
        glfwMakeContextCurrent(window);
    }
    return window;
}

bool Render::loadShaderFromFile(unsigned int* shaderObject, GLenum type, const char* filename)
{
    FILE* file;
    if (fopen_s(&file, filename, "rb")) return false;
    if (file == NULL) return false;
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* shaderStr = (char*)malloc(fileSize + 1ui64);
    if (shaderStr == NULL) return false;
    fread_s(shaderStr, fileSize, sizeof(char), fileSize, file);
    shaderStr[fileSize] = '\0';

    unsigned int obj = glCreateShader(type);
    glShaderSource(obj, 1, &shaderStr, NULL);
    glCompileShader(obj);
    *shaderObject = obj;

    free(shaderStr);
    fclose(file);

    int shaderCompileStatus;
    glGetShaderiv(obj, GL_COMPILE_STATUS, &shaderCompileStatus);
    if (shaderCompileStatus == 0)
    {
        char message[512];
        glGetShaderInfoLog(obj, 512, NULL, message);
        printf("Failed to compile shader (%s): %s\n", filename, message);
        return false;
    }
    return true;
}

bool Render::loadShaderProgram(unsigned int* programObject, const char* vertexShaderFilename, const char* fragmentShaderFilename, const char* geometryShaderFilename)
{
    unsigned int vertexShaderObject;
    if (vertexShaderFilename == nullptr ||
        !Render::loadShaderFromFile(
        &vertexShaderObject,
        GL_VERTEX_SHADER,
        vertexShaderFilename))
    {
        return false;
    }

    unsigned int fragmentShaderObject;
    if (fragmentShaderFilename == nullptr ||
        !Render::loadShaderFromFile(
        &fragmentShaderObject,
        GL_FRAGMENT_SHADER,
        fragmentShaderFilename))
    {
        return false;
    }

    bool hasGeometryShader = geometryShaderFilename != nullptr;
    unsigned int geometryShaderObject;
    if (hasGeometryShader)
    {
        if (!Render::loadShaderFromFile(
            &geometryShaderObject,
            GL_GEOMETRY_SHADER,
            geometryShaderFilename))
        {
            return false;
        }
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderObject);
    glAttachShader(shaderProgram, fragmentShaderObject);
    if (hasGeometryShader) glAttachShader(shaderProgram, geometryShaderObject);
    glLinkProgram(shaderProgram);

    int linkStatus;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus)
    {
        char msg[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, msg);
        printf("Failed to link shaders: %s\n", msg);
    }

    glDeleteShader(vertexShaderObject);
    glDeleteShader(fragmentShaderObject);
    if (hasGeometryShader)glDeleteShader(geometryShaderObject);

    *programObject = shaderProgram;
    return linkStatus != 0;
}

bool Render::initializeBuffers()
{
    // ################
    // Fruit
    // ################
    glGenBuffers(1, &Render::glObject_FruitVertexBuffer);
    glGenVertexArrays(1, &Render::glObject_FruitVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, Render::glObject_FruitVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(Render::VertexData::vertexData_Fruit),
        Render::VertexData::vertexData_Fruit,
        GL_STATIC_DRAW);

    glBindVertexArray(Render::glObject_FruitVertexArray);
    
    // Location 0: VertexData
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // ################
    // Score Text
    // ################
    glGenBuffers(1, &Render::glObject_ScoreTextVertexBuffer);
    glGenVertexArrays(1, &Render::glObject_ScoreTextVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, Render::glObject_ScoreTextVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(Render::VertexData::vertexData_ScoreText),
        Render::VertexData::vertexData_ScoreText,
        GL_STATIC_DRAW);

    glBindVertexArray(Render::glObject_ScoreTextVertexArray);

    // Location 0: VertexData
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // ################
    // UI Component
    // ################
    glGenBuffers(1, &Render::glObject_UICompVertexBuffer);
    glGenVertexArrays(1, &Render::glObject_UICompVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, Render::glObject_UICompVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(Render::VertexData::vertexData_UIComp),
        Render::VertexData::vertexData_UIComp,
        GL_STATIC_DRAW);

    glBindVertexArray(Render::glObject_UICompVertexArray);

    // Location 0: VertexData
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // END
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;
}

bool Render::initializeShaders()
{
    return Render::loadShaderProgram(
            &Render::glObject_FruitShaderProgram,
            "./FruitVertexShader.glsl",
            "./FruitFragmentShader.glsl",
            nullptr)
        && Render::loadShaderProgram(
            &Render::glObject_ScoreTextShaderProgram,
            "./ScoreTextVertexShader.glsl",
            "./ScoreTextFragmentShader.glsl",
            nullptr)
        && Render::loadShaderProgram(
            &Render::glObject_UICompShaderProgram,
            "./UIComponentVertexShader.glsl",
            "./UIComponentFragmentShader.glsl",
            nullptr);
}

void Render::getUniformLocations()
{
    // Fruit Shader Program
    Render::glUniformLocation_FruitTrans = glGetUniformLocation(
        Render::glObject_FruitShaderProgram,
        "Uniform_Trans");
    Render::glUniformLocation_FruitColor = glGetUniformLocation(
        Render::glObject_FruitShaderProgram,
        "Uniform_Color"
    );

    // Score Text Shader Program
    Render::glUniformLocation_ScoreTextTrans = glGetUniformLocation(
        Render::glObject_ScoreTextShaderProgram,
        "Uniform_Trans"
    );
    Render::glUniformLocation_ScoreTextNumberIndex = glGetUniformLocation(
        Render::glObject_ScoreTextShaderProgram,
        "Uniform_NumberIndex"
    );

    // UI Compnent Shader Program
    Render::glUniformLocation_UICompTrans = glGetUniformLocation(
        Render::glObject_UICompShaderProgram,
        "Uniform_Trans"
    );
    Render::glUniformLocation_UICompColor = glGetUniformLocation(
        Render::glObject_UICompShaderProgram,
        "Uniform_Color"
    );
}

void Render::clearBackground()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Render::renderFruitObject(TextureManager* textureManager, FruitObject* fruit)
{
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(fruit->position, 0.0f));
    trans = glm::rotate(trans, fruit->rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(fruit->getRadius()));

    glUseProgram(Render::glObject_FruitShaderProgram);

    //glActiveTexture(GL_TEXTURE0);
    textureManager->bindTexture(fruit->getLevel() - 1);

    float gameoverIndicator = fruit->gameoverTimer / GameConfig::GameoverTimerMax;
    if (gameoverIndicator > 1.0f) gameoverIndicator = 1.0f;

    float color[] = { 1.0f, 1.0f - gameoverIndicator, 1.0f - gameoverIndicator, 1.0f };
    if (fruit->isDummy) color[3] = 0.6f;
    glUniformMatrix4fv(Render::glUniformLocation_FruitTrans, 1, GL_FALSE, glm::value_ptr(trans));
    glUniform4fv(Render::glUniformLocation_FruitColor, 1, color);

    glBindVertexArray(Render::glObject_FruitVertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Render::renderScoreText(TextureManager* textureManager, float x, float y, float textSize, int score)
{
    if (score > 999999) score = 999999;
    if (score < 0) score = 0;
    glUseProgram(Render::glObject_ScoreTextShaderProgram);
    textureManager->bindTexture(TEXTURE_ID_SCORE_TEXT);

    int base = 100000;
    bool digitValid = score / base > 0;
    while (base > 0)
    {
        int digit = score / base;
        score %= base;
        if (digitValid)
        {
            renderScoreTextDigit(x, y, textSize, digit);
            x += textSize;
        }
        else
        {
            digitValid = base > 1 && score / (base / 10) > 0;
        }
        base /= 10;
    }

    if (!digitValid)
    {
        renderScoreTextDigit(x, y, textSize, 0);
    }
}

void Render::renderScoreTextDigit(float x, float y, float textSize, int digit)
{
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
    trans = glm::scale(trans, glm::vec3(textSize));

    glUniformMatrix4fv(Render::glUniformLocation_ScoreTextTrans, 1, GL_FALSE, glm::value_ptr(trans));
    glUniform1i(Render::glUniformLocation_ScoreTextNumberIndex, digit);
    glBindVertexArray(Render::glObject_ScoreTextVertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
