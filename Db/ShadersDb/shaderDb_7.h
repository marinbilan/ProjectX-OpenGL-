//
// VERTEX SHADER
//
const char* VS7 =
"#version 330 \r\n"
""
"	in vec3 position;"
"	in vec3 normal;"
"	in vec2 textureCoordinates;"
"   vec3 tangent;"
""
"	uniform mat4 projectionMatrix;"
"	uniform mat4 transformationMatrix;"
"	uniform mat4 viewMatrix;"
"	uniform mat4 viewMatrixInv;"
""
"	uniform vec3 lightPosition;"
""
"	out vec2 pass_textureCoordinates;"
"	out vec3 toLightVector;"
"	out vec3 toCameraVector;"
""
"	void main(void) {"
""
"		vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
"		gl_Position = projectionMatrix * viewMatrix * worldPosition;"
"		vec4 modelViewMatrix =  viewMatrix * worldPosition;"
"		pass_textureCoordinates = textureCoordinates;"
""
"		vec3 surfaceNormal = ( transformationMatrix * vec4(normal, 0.0) ).xyz;"
""
"		vec3 norm = normalize(surfaceNormal);"
"		tangent = vec3(1.0, 1.0, 1.0);" // TO DO TEST 
"		vec3 tang = normalize((modelViewMatrix * vec4(tangent, 0.0)).xyz);"
"		vec3 bitang = normalize(cross(norm, tang));"
""
"		mat3 toTangentSpace = mat3("
"			tang.x, bitang.x, norm.x,"
"			tang.y, bitang.y, norm.y,"
"			tang.z, bitang.z, norm.z);"
""
"		toLightVector = toTangentSpace * (lightPosition - worldPosition.xyz);"
"		toCameraVector = toTangentSpace * ((viewMatrixInv * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz);"
"}";
//
// FRAGMENT SHADER
//
const char* FS7 =
"#version 330 \r\n"
""
"	in vec2 pass_textureCoordinates;"
"	in vec3 toLightVector;"
"	in vec3 toCameraVector;"
""
"	uniform sampler2D modelTexture;"
"	uniform sampler2D normalMap;"
""
"	uniform vec3 lightColour;"
"	uniform float shineDamper;"
"	uniform float reflectivity;"
""
"	out vec4 out_Color;"
""
"	void main(void) {"
""
"		vec4 normalMapValue = 2.0 * texture(normalMap, pass_textureCoordinates) - 1.0;"
""
"		vec3 unitNormal = normalize(normalMapValue.rgb);"
"		vec3 unitLightVector = normalize(toLightVector);"
""
"		float nDot1 = dot(unitNormal, unitLightVector);"
"		float brightness = max(nDot1, 0.2);"
"		vec3 diffuse = brightness * lightColour;"
""
"		vec3 unitVectorToCamera = normalize(toCameraVector);"
"		vec3 lightDirection = -unitLightVector;"
"		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal); "
""
"		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera); "
"		specularFactor = max(specularFactor, 0.0); "
""
"		float dampedFactor = pow(specularFactor, shineDamper); "
""
"		vec3 finalSpecular = dampedFactor * reflectivity * lightColour;"
""
"		out_Color = vec4(diffuse, 1.0) * texture(modelTexture, pass_textureCoordinates) + vec4(finalSpecular, 1.0);"
"}";
