#include "GUIManager.h"

GUIManager* GUIManager::instance = nullptr;

bool GUIManager::init()
{
    if (!GUIManager::instance)
    {
        GUIManager::instance = new GUIManager();
        return true;
    }
    else
    {
        return false;
    }
}

GUIManager::GUIManager()
{
    this->currentGUIIndex = -1;
    this->registeredGUIs = (RegisteredGUI*)malloc(sizeof(RegisteredGUI) * GUI_MANAGER_CAPACITY);
    if (!this->registeredGUIs)
    {
        throw "GUIManager: malloc failed";
    }
    for (int i = 0; i < GUI_MANAGER_CAPACITY; i++)
    {
        this->registeredGUIs[i] = { nullptr, -1 };
    }
}

GUIManager::~GUIManager()
{
    if (this->registeredGUIs)
    {
        free(this->registeredGUIs);
    }
}

void GUIManager::render(TextureManager* textureManager)
{
    GUIObject* gui = this->getCurrentGUI();
    if (gui)
    {
        gui->render(textureManager);
    }
}

void GUIManager::preRender(float dtFrame)
{
    GUIObject* gui = this->getCurrentGUI();
    if (gui)
    {
        gui->preRender(dtFrame);
    }
}

void GUIManager::onMouseDown(float x, float y)
{
    GUIObject* gui = this->getCurrentGUI();
    if (gui)
    {
        gui->onMouseDown(x, y);
    }
}

void GUIManager::onMouseUp(float x, float y)
{
    GUIObject* gui = this->getCurrentGUI();
    if (gui)
    {
        gui->onMouseUp(x, y);
    }
}

void GUIManager::onMouseMove(float x, float y)
{
    GUIObject* gui = this->getCurrentGUI();
    if (gui)
    {
        gui->onMouseMove(x, y);
    }
}

GUIObject* GUIManager::getCurrentGUI()
{
    if (this->currentGUIIndex >= 0)
    {
        return this->registeredGUIs[currentGUIIndex].gui;
    }
    else
    {
        return nullptr;
    }
}

int GUIManager::registerGUI(GUIObject* gui, int id)
{
    for (int i = 0; i < GUI_MANAGER_CAPACITY; i++)
    {
        if (!this->registeredGUIs[i].gui)
        {
            this->registeredGUIs[i] = { gui, id };
            return i;
        }
    }
    return -1;
}

bool GUIManager::unregisterGUI(int index)
{
    if (index >= 0 && index < GUI_MANAGER_CAPACITY && this->registeredGUIs[index].gui)
    {
        this->registeredGUIs[index] = { nullptr, -1 };
        return true;
    }
    else
    {
        return false;
    }
}

bool GUIManager::switchToGUIWithIndex(int index)
{
    if (index >= 0 && index < GUI_MANAGER_CAPACITY && this->registeredGUIs[index].gui)
    {
        this->currentGUIIndex = index;
        return true;
    }
    else
    {
        return false;
    }
}

bool GUIManager::switchToGUIWithID(int id)
{
    for (int i = 0; i < GUI_MANAGER_CAPACITY; i++)
    {
        if (this->registeredGUIs[i].gui && this->registeredGUIs[i].id == id)
        {
            this->currentGUIIndex = i;
            return true;
        }
    }
    return false;
}
