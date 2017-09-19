//
// VERTEX SHADER
//
const char* VSDepthMapFBO =
"    #version 330 \r\n"
""
"    in vec3 position;"
""
"	 uniform mat4 lightSpaceMatrix;"
"    uniform mat4 transformationMatrix;"
""
"	 void main()"
"	 {"
"       gl_Position = lightSpaceMatrix * transformationMatrix * vec4(position, 1.0);"
"    }";
//
// FRAGMENT SHADER
//
const char* FSDepthMapFBO =
"    #version 330 \r\n"
""
"    void main()"
"{}";
