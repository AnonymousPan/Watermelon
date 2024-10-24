#include "GameTitleImage.h"

GameTitleImage::GameTitleImage(float borderTop, float borderRight) : UIComponent()
{
    this->position = glm::vec2(0.0f, borderTop * 0.6f);
    this->scale = glm::vec2(0.3f, 0.1f);
}

int GameTitleImage::getTextureIndex()
{
    return TEXTURE_ID_GAME_TITLE;
}

void GameTitleImage::autoSize(TextureManager* textureManager, float width)
{
    unsigned short imgW, imgH;
    if (textureManager->getTextureSize(TEXTURE_ID_GAME_TITLE, &imgW, &imgH))
    {
        float height = width / imgW * imgH;
        this->scale = glm::vec2(width, height);
    }
}
