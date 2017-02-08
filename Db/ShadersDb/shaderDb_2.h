//
// Shader_GUI
//
const char* VS2 =
"#version 330 \r\n"
""
"	in vec2 position;"
""
"	uniform mat4 transformationMatrix;"
""
"	out vec2 textureCoords;"
""
"	void main()"
"	{	"
"		gl_Position = transformationMatrix * vec4(position, 0.0, 1.0);"
"		textureCoords = vec2((position.x+1.0)/2.0, 1 - (position.y+1.0)/2.0);"
"	}";

const char* FS2 =
"#version 330 \r\n"
""
"	in vec2 textureCoords;"
""
"	uniform sampler2D guiTexture;"
""
"	out vec4 out_Color;"
""
"	void main()"
"	{"
"		out_Color = texture(guiTexture,textureCoords);"
"	}";