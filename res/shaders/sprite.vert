#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

// vertix position calculation
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// texture coordination calculation
uniform float u_NumberOfRows;
uniform float u_NumberOfCols;
uniform vec2 u_TextureOffset;

void main()
{
    
    if (u_NumberOfRows == 1.0 && u_NumberOfCols == 1.0)
        TexCoords = vertex.zw;
    else
        TexCoords = vec2(vertex.z / u_NumberOfRows + u_TextureOffset.x, vertex.w / u_NumberOfCols + u_TextureOffset.y);

    gl_Position = u_Projection * u_View * u_Model * vec4(vertex.xy, 0.0, 1.0);
}
