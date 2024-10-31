#include "UIComponent.h"

#include "Render.h"

UIComponent::UIComponent()
{
    this->color = COLOR_SOLID_WHITE;
    this->position = glm::vec2();
    this->scale = glm::vec2();
}

void UIComponent::render(TextureManager* textureManager)
{
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(this->position, 0.0f));
    trans = glm::scale(trans, glm::vec3(this->scale, 1.0f));

    glUseProgram(Render::glObject_UICompShaderProgram);

    textureManager->bindTexture(this->getTextureIndex());

    glUniformMatrix4fv(Render::glUniformLocation_UICompTrans, 1, GL_FALSE, glm::value_ptr(trans));
    glUniform4fv(Render::glUniformLocation_UICompColor, 1, (float*)&this->color);

    glBindVertexArray(Render::glObject_UICompVertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
