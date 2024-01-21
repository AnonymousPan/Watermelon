#pragma once

// Vertex data arrays
namespace Render
{
    namespace VertexData
    {
        const float vertexData_Fruit[] = {
            // Vertex position [2]; Texture coord [2]
            // Triangle 1
            -1.0f, +1.0f, 0.0f, 1.0f, // LT
            +1.0f, +1.0f, 1.0f, 1.0f, // RT
            -1.0f, -1.0f, 0.0f, 0.0f, // LB
            // Triangle 2
            +1.0f, +1.0f, 1.0f, 1.0f, // RT
            -1.0f, -1.0f, 0.0f, 0.0f, // LB
            +1.0f, -1.0f, 1.0f, 0.0f, // RB
        };
    }
}
