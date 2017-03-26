//
// VERTEX SHADER
//
const char* VS_Water =
"#version 330 \r\n"
""  // ATTRIBs
"	in vec2 position;"
""  // UNIFORMs
"	uniform mat4 projectionMatrix;"
"	uniform mat4 viewMatrix;"
"	uniform mat4 modelMatrix;"
"	uniform vec3 cameraPosition;"
""  // OUTs
"	out vec4 clipSpace;"
"	out vec2 textureCoords;"
"	out vec3 toCameraVector;"
""  // VARIABLEs
"	const float tiling = 6.0;"
""
"	void main(void) {"
""
"		vec4 worldPosition = modelMatrix * vec4(position.x, 0.0, position.y, 1.0);"
"		clipSpace = projectionMatrix * viewMatrix * worldPosition;"
"		gl_Position = clipSpace;"
"		textureCoords = vec2(position.x / 2.0 + 0.5, position.y / 2.0 + 0.5) * tiling;"
"		toCameraVector = cameraPosition - worldPosition.xyz;"
"}";
//
// FRAGMENT SHADER
//
const char* FS_Water =
"#version 330 \r\n"
""  // ATTRIBs
"	in vec4 clipSpace;"
"	in vec2 textureCoords;"
"	in vec3 toCameraVector;"
""  // UNIFORMs
"	uniform sampler2D reflectionTexture;"
"	uniform sampler2D refractionTexture;"
"	uniform sampler2D dudvMap;"
""
"	uniform float moveFactor;"
""  // OUTs
"	out vec4 out_Color;"
""  // VARIABLEs
"	const float waveStrength = 0.02;"
""
"	void main(void) {"
""
"		vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;"
"		vec2 refractTexCoords = vec2(ndc.x, ndc.y);"
"		vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);"
""
"		vec2 distortion1 = (texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 2.0 - 1.0) * waveStrength;" // TO DO: Make this changing in time
"		vec2 distortion2 = (texture(dudvMap, vec2(-textureCoords.x + moveFactor, textureCoords.y + moveFactor)).rg * 2.0 - 1.0) * waveStrength;" // TO DO: Make this changing in time
""
"		vec2 totalDistortion = distortion1 + distortion2;"
""
"		refractTexCoords += totalDistortion;"
"		refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);"
""
"		reflectTexCoords += totalDistortion;"
"		reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);"
"		reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);"
""
"		vec4 reflectColour = texture(reflectionTexture, reflectTexCoords);"
"		vec4 refractColour = texture(refractionTexture, refractTexCoords);"
""
"		vec3 viewVector = normalize(toCameraVector);"
"		float refractiveFactor = dot(viewVector, vec3(0.0, 1.0, 0.0));"
"		refractiveFactor = pow(refractiveFactor, 10.0);"
""
"		out_Color = mix(reflectColour, refractColour, refractiveFactor);"
"		out_Color = mix(out_Color, vec4(0.0, 0.3, 0.5, 1.0), 0.2);" // Just add a little bit blue color in water
"}";
