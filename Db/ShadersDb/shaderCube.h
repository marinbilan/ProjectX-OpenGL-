//
// VERTEX SHADER
//
const char* VScube =
"#version 330 \r\n"
""
"in vec4 s_vPosition;"
"in vec4 s_vNormal;"
"in vec2 s_vTexCoord;"
""
"uniform mat4 mP;"
"uniform mat4 mV;"
"uniform mat4 mM;"
"uniform mat4 mRotations;"
"uniform vec4 vLight;"
""
"out vec2 texCoord;"
"out vec3 fN;"
"out vec3 fL;"
"out vec3 fE;"
""
"void main() {"
""
"	gl_Position = mP*mV*mM*s_vPosition;"
""
"	texCoord = s_vTexCoord;"
""
"	fN = (mRotations*s_vNormal).xyz;"
"	fL = (vLight).xyz;"
"	fE = (mV*mM*s_vPosition).xyz;"	
"}";
//
// FRAGMENT SHADER
//
const char* FScube =
"#version 330 \r\n"
""
"in vec3 fN;"
"in vec3 fL;"
"in vec3 fE;"
"in vec2 texCoord;"
""
"uniform sampler2D texture;"
""
"out vec4 fColor;"
""
"void main() {"
"	vec3 N = normalize(fN);"
"	vec3 L = normalize(fL);"
"	vec3 E = normalize(-fE);"
"	vec3 H = normalize(L + E);"
""
"	float diffuse_intensity = max(dot(N, L), 0.0);"
"	vec4 diffuse_final = diffuse_intensity*texture2D(texture, texCoord);"
""
""
"	float spec_intensity = pow(max(dot(N, H), 0.0), 3000);"
"	vec4 spec_final = spec_intensity * vec4(1.0, 0.0, 0.0, 1.0);"
""
"	fColor = diffuse_final + spec_final;"
"}";




