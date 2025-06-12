#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse; 

out vec4 finalColor;

void main() {
    vec4 texelColor = texture(texture0, fragTexCoord);
    
    vec3 lightDir = normalize(vec3(-1.5, 1.0, 0.0)); 
    float dotP = max(dot(normalize(fragNormal), lightDir), 0.0);

    finalColor = colDiffuse * fragColor * vec4(texelColor.rgb * dotP, 1.0f);
}