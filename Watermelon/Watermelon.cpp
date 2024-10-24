// Watermelon.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "WatermelonGame.h"
#include "GUIManager.h"
#include "GUIObject.h"

#include "GUIGamePlay.h"
#include "GUITitle.h"

void cursorPosCallback(GLFWwindow* window, double x, double y);
bool gameInit();

WatermelonGame game;
bool previousMouseKeyStatus = false;
float mouseX = 0.0f;
float mouseY = 0.0f;
float previousTick = 0.0f;

GUIGamePlay guiGamePlay(&game);
GUITitle* guiTitle;

int WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
    if (!gameInit())
    {
        MessageBoxA(NULL, "Failed to initialize game", "Watermelon", MB_OK | MB_ICONERROR);
        return 1;
    }
    glfwSetCursorPosCallback(game.gameWindow, cursorPosCallback);

    guiTitle = new GUITitle(game.textureManager, game.borderTop, game.borderRight);

    GUIManager::instance->registerGUI(&guiGamePlay, GUI_ID_GAME_PLAY);
    GUIManager::instance->registerGUI(guiTitle, GUI_ID_TITLE);
    GUIManager::instance->switchToGUIWithID(GUI_ID_TITLE);

    previousTick = glfwGetTime();

    while (!game.gameShouldExit())
    {
        // Process pending events
        glfwPollEvents();
        bool currentMouseKeyStatus = glfwGetMouseButton(game.gameWindow, GLFW_MOUSE_BUTTON_LEFT);
        if (currentMouseKeyStatus != previousMouseKeyStatus)
        {
            if (currentMouseKeyStatus)
            {
                // Key down
                GUIManager::instance->onMouseDown(mouseX, mouseY);
            }
            else
            {
                // Key up
                GUIManager::instance->onMouseUp(mouseX, mouseY);
            }
        }
        previousMouseKeyStatus = currentMouseKeyStatus;

        // Tick game (physics...)
        game.tick();

        // Render
        float currentTick = glfwGetTime();
        float dt = currentTick - previousTick;
        previousTick = currentTick;
        GUIManager::instance->preRender(dt);
        GUIManager::instance->render(game.textureManager);
        glfwSwapBuffers(game.gameWindow);

        // Wait
        Sleep(10);
    }

    game.exit();
    return 0;
}

void cursorPosCallback(GLFWwindow* window, double x, double y)
{
    mouseX = x / game.windowWidth * (game.borderRight - game.borderLeft) + game.borderLeft;
    mouseY = -(y / game.windowHeight * (game.borderTop - game.borderBottom) + game.borderBottom);
    GUIManager::instance->onMouseMove(mouseX, mouseY);
}

bool gameInit()
{
    return GUIManager::init() && game.init();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
