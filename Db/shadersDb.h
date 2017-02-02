//
// Shader_GUI
//
const char* VSGUI =
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

const char* FSGUI =
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
//
// Shader_2 [JC - Diffuse + Specular] lighting
//
const char* VS2 =
"#version 330 \r\n"
""
"	in vec4 s_vPosition;"
"	in vec4 s_vNormal;"
""
"	uniform mat4 mP;"
"	uniform mat4 mV;"
"	uniform mat4 mM;"
"	uniform mat4 mRotations;"
""
"	uniform vec4 vLight;"
""
"	out vec3 fN;"
"	out vec3 fL;"
"	out vec3 fE;"
""
"	void main()"
"	{"
"		gl_Position = mP*mV*mM*s_vPosition;"
""
"		fN = (mRotations*s_vNormal).xyz;"
"		fL = (vLight).xyz;"
"		fE = (mV*mM*s_vPosition).xyz;"
"	}";

const char* FS2 =
"#version 330 \r\n"
""
"	in vec3 fN;"
"	in vec3 fL;"
"	in vec3 fE;"
""
"	out vec4 fColor;"
""
"	void main()	"
"	{"
"		vec3 N = normalize(fN);"
"		vec3 L = normalize(fL);"
""
"		vec3 E = normalize(-fE);"
"		vec3 H = normalize(L + E);"
""
"		float diffuse_intensity = max(dot(N, L), 0.0);"
"		vec4 diffuse_final = diffuse_intensity*vec4(0.4, 0.4, 0.4, 1.0);"
""
"		float spec_intensity = pow(max(dot(N, H), 0.0), 1600);"
"		vec4 spec_final = spec_intensity*vec4(0.5, 0.4, 0.6, 1.0);"
""
"		fColor = diffuse_final + spec_final;"
"	}";
//
// Shader_2 [JC - Diffuse + Specular] lighting
//
const char* VSSkyBox =
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

const char* FSSkyBox =
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