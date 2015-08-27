uniform mat4 u_MvpMatrix;

attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_TextureCoordinates;

varying vec4 v_Color;
varying vec2 v_TextureCoordinates;

void main()
{
    gl_Position = u_MvpMatrix * a_Position;
    v_Color = a_Color;
    v_TextureCoordinates = vec2(a_TextureCoordinates.x, 1.0 - a_TextureCoordinates.y);
}