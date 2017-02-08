//
// Shader_2 [JC - Diffuse + Specular] lighting
//
const char* VS3 =
"#version 330 \r\n"
""
"	in vec3 position;"
""
"	uniform mat4 projectionMatrix;"
"	uniform mat4 viewMatrix;"
""
"	out vec3 textureCoords;"
""
"	void main()"
"	{"
"		gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);"
""
"		textureCoords = position;"
"	}";

const char* FS3 =
"#version 330 \r\n"
""
"	in vec3 textureCoords;"
"	out vec4 out_Color;"
""
"	uniform samplerCube cubeMap;"
""
"	void main()	"
"	{"
"		out_Color = texture(cubeMap, textureCoords);"
"	}";