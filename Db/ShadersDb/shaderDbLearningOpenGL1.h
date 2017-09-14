//
// VERTEX SHADER
//
const char* VSLearningOpenGL1 =
"	#version 330 \r\n"
""
"	in vec3 position;"
""
"	uniform mat4 projection;"
"	uniform mat4 view;"
"	uniform mat4 model;"
""
"	void main()" 
"	{"
"		gl_Position = projection * view * model * vec4(position, 1.0f);"
"}";
//
// FRAGMENT SHADER
//
const char* FSLearningOpenGL1 =
"#version 330 \r\n"
""
"	out vec4 color;"
""
"	uniform vec3 objectColor;"
"	uniform vec3 lightColor;"
""
"	void main()"
"	{"
"		color = vec4(lightColor * objectColor, 1.0f);"
"	}";
