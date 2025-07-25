#version 330                       
in vec3 vertexPosition;            
in vec2 vertexTexCoord;    
in vec3 vertexNormal;        
in vec4 vertexColor;               
out vec2 fragTexCoord;             
out vec4 fragColor;     
out vec3 fragNormal;

uniform mat4 mvp;                 
void main()                        
{                                  
    fragTexCoord = vertexTexCoord; 
    fragColor = vertexColor; 
    fragNormal = vertexNormal;
    gl_Position = mvp*vec4(vertexPosition, 1.0);
}    