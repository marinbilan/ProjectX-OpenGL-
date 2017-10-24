//
// ----==== Shader_GUI ====----
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
//
// ----==== WATER SHADER ====----
//
const char* VS_Water_Tile =
"#version 330 \r\n"
""
"	in vec2 position;"
""
""  // UNIFORMs
"	uniform mat4 projectionMatrix;"
"	uniform mat4 viewMatrix;"
"	uniform mat4 modelMatrix;"
""
"	uniform vec3 cameraPosition;"
"	uniform vec3 lightPosition;"
"" // OUTs
"	out vec4 clipSpace;"
"	out vec2 textureCoords;"
"	out vec3 toCameraVector;" // NEW
"	out vec3 fromLightVector;"
"" // VARIABLEs
"	const float tiling = 6.0;"
"	void main()"
"	{	"
"		vec4 worldPosition = modelMatrix * vec4(position.x, position.y, 0.0, 1.0);"
"		clipSpace = projectionMatrix * viewMatrix * worldPosition;"
"		gl_Position = clipSpace;" 
"		textureCoords = vec2(position.x/2.0 + 0.5, position.y/2.0 + 0.5) * tiling;"
"		toCameraVector = cameraPosition - worldPosition.xyz;"
"		fromLightVector = worldPosition.xyz - lightPosition;"
"	}";

const char* FS_Water_Tile =
"#version 330 \r\n"
""
"	in vec4 clipSpace;"
"	in vec2 textureCoords;"
"	in vec3 toCameraVector;"
"	in vec3 fromLightVector;"
""  // UNIFORMs
"	uniform sampler2D reflectionTexture;"
"	uniform sampler2D refractionTexture;"
"	uniform sampler2D dudvMap;"
"	uniform sampler2D normalMap;"
""
"	uniform vec3 lightColour;"
"	uniform float moveFactor;" // TODO: Add moving factor in render method
"" // OUTs
"	out vec4 out_Color;"
"" // VARIABLEs
"	const float waveStrength = 0.02;"
"	const float shineDamper = 20.0;"
"	const float reflectivity = 0.6;"
""
"	void main()"
"	{"
"		vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;" // Screen space coordinates
"		vec2 refractTexCoords = vec2(ndc.x, ndc.y);"
"		vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);"
""
"		vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 0.1;"
"		distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y + moveFactor);"
"		vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;"
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
"		float refractiveFactor = dot(viewVector, vec3(0.0, 1.0, 0.0));" // normala prema gore!
"		refractiveFactor = pow(refractiveFactor, 0.5);" // FAKTOR REFLEKSIJE. KOD VELIKIH FAKTORA > 10, dno se vidi samo ako se gleda okomito dolje
""
//"		out_Color = vec4(0.0, 0.0, 1.0, 1.0);"
"		vec4 normalMapColour = texture(normalMap, distortedTexCoords);"
"		vec3 normal = vec3(normalMapColour.r * 2.0 - 1.0, normalMapColour.b, normalMapColour.g * 2.0 - 1.0);"
"		normal = normalize(normal);" // Surface normals
"" // NEW:
"		vec3 reflectedLight = reflect(normalize(fromLightVector), normal);"
"		float specular = max(dot(reflectedLight, viewVector), 0.0);"
"		specular = pow(specular, shineDamper);"
"		vec3 specularHighlights = lightColour * specular * reflectivity;"
"" // END NEW
""
"		out_Color = mix(reflectColour, refractColour, refractiveFactor);" // refractiveFactor - mixing factor
"		out_Color = mix(out_Color, vec4(0.0, 0.3, 0.5, 1.0), 0.2) + vec4(specularHighlights, 0.0);" // MOZE SE DODATI MALO BOJE U VODU (NPR PLAVE) - Dodana komponenta + vec4(specularHighlights, 0.0)
"	}";
//
// ----==== DEPTHMAP SHADER ====----
//
/*
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

char* FSDepthMapFBO =
"    #version 330 \r\n"
""
"    void main()"
"{}";
*/
const char* VSDepthMapFBO =
"    #version 330 \r\n"
""
"    in vec3 in_position;"
""
"	 uniform mat4 mvpMatrix;"
""
"	 void main()"
"	 {"
"       gl_Position = mvpMatrix * vec4(in_position, 1.0);"
"    }";

char* FSDepthMapFBO =
"    #version 330 \r\n"
""
"	out vec4 out_colour;"
""
"	uniform sampler2D modelTexture;"
""
"   void main()"
"{"
"	out_colour = vec4(1.0);"
"}";
//
// ----==== NORMAL MAP SHADER ====----
//
//
// VERTEX SHADER
//
const char* VS7 =
"#version 330 \r\n"
""
"in vec3 position;"
"in vec3 normal;"
"in vec2 textureCoordinates;"
"in vec3 tangent;"
""
"out vec2 pass_textureCoordinates;"
"out vec3 toLightVector;" // MULTIPLE
"out vec3 toCameraVector;"
"out float visibility;"
""
"uniform mat4 transformationMatrix;"
"uniform mat4 projectionMatrix;"
"uniform mat4 viewMatrix;"
""
"uniform vec3 lightPositionEyeSpace;" // MULTIPLE
""
"const float density = 0;"
"const float gradient = 5.001;"
""
// "uniform vec4 plane;"
""
"void main(void) {"
""
"	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
// "	gl_ClipDistance[0] = dot(worldPosition, plane);"
"	mat4 modelViewMatrix = viewMatrix * transformationMatrix;"
"	vec4 positionRelativeToCam = modelViewMatrix * vec4(position, 1.0);"
"	gl_Position = projectionMatrix * positionRelativeToCam;"
""
"	pass_textureCoordinates = textureCoordinates;"
""
"	vec3 surfaceNormal = (modelViewMatrix * vec4(normal, 0.0)).xyz;"
""
"	vec3 norm = normalize(surfaceNormal);"
"	vec3 tang = normalize((modelViewMatrix * vec4(tangent, 0.0)).xyz);"
"	vec3 bitang = normalize(cross(norm, tang));"
""
"	mat3 toTangentSpace = mat3("
"		tang.x, bitang.x, norm.x,"
"		tang.y, bitang.y, norm.y,"
"		tang.z, bitang.z, norm.z"
"		);"
""
"	toLightVector = toTangentSpace * ( (viewMatrix * vec4(lightPositionEyeSpace, 1.0)).xyz - positionRelativeToCam.xyz);"
"	toCameraVector = toTangentSpace * (-positionRelativeToCam.xyz);"
""
"	float distance = length(positionRelativeToCam.xyz);"
"	visibility = exp(-pow((distance*density), gradient));"
"	visibility = clamp(visibility, 0.0, 1.0);"
""
"}";
//
// FRAGMENT SHADER
//
const char* FS7 =
"#version 330 \r\n"
""
"in vec2 pass_textureCoordinates;"
"in vec3 toLightVector;" // MULTIPLE
"in vec3 toCameraVector;"
"in float visibility;"
""
"out vec4 out_Color;"
""
"uniform sampler2D modelTexture;"
"uniform sampler2D normalMap;"
""
"uniform vec3 lightColour;" // MULTIPLE
// "uniform vec3 attenuation;" // MULTIPLE
"uniform float shineDamper;"
"uniform float reflectivity;"
// "uniform vec3 skyColour;"
""
"void main(void) {"
""
"	vec4 normalMapValue = 2.0 * texture(normalMap, pass_textureCoordinates, -1.0) - 1.0;"
""
"	vec3 unitNormal = normalize(normalMapValue.rgb);"
"	vec3 unitVectorToCamera = normalize(toCameraVector);"
""
"	vec3 totalDiffuse = vec3(0.0);"
"	vec3 totalSpecular = vec3(0.0);"
""
"		float distance = length(toLightVector);"
"		vec3 attenuation = vec3(0.001);"
"		float attFactor = attenuation.x + (attenuation.y * distance) + (attenuation.z * distance * distance);"
"		vec3 unitLightVector = normalize(toLightVector);"
"		float nDotl = dot(unitNormal, unitLightVector);"
"		float brightness = max(nDotl, 0.0);"
"		vec3 lightDirection = -unitLightVector;"
"		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);"
"		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);"
"		specularFactor = max(specularFactor, 0.0);"
"		float dampedFactor = pow(specularFactor, shineDamper);"
"		totalDiffuse = totalDiffuse + (brightness * lightColour) / attFactor;"
"		totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColour) / attFactor;"
""
"	totalDiffuse = max(totalDiffuse, 0.1);"
""
"	vec4 textureColour = texture(modelTexture, pass_textureCoordinates, -1.0);"
"	if (textureColour.a<0.5) {"
"		discard;"
"	}"
""
"	out_Color = vec4(totalDiffuse, 1.0) * textureColour + vec4(totalSpecular, 1.0);"
//"	out_Color = mix(vec4(skyColour, 1.0), out_Color, visibility);"
""
"}";
//
// ----==== DEPTH MAP SHADER ====----
//
//
// VERTEX SHADER
//
const char* DepthMapVertexShader =
"#version 330 \r\n"
""
"in vec3 aPos;"
"in vec2 aTexCoords;"
"in vec3 aNormal;"
""
//"out vec2 TexCoords;" // NEW
""
"out VS_OUT {"
"vec3 FragPos;"
"vec3 Normal;"
"vec2 TexCoords;"
"vec4 FragPosLightSpace;" // NEW
"} vs_out;"
""
"uniform mat4 projection;"
"uniform mat4 view;"
"uniform mat4 model;" // NEW
"uniform mat4 lightSpaceMatrix;" // NEW
"uniform mat3 invMat3Model;" // MY NEW
""
"void main()"
"{"
"	vs_out.FragPos = vec3(model * vec4(aPos, 1.0));"
"	vs_out.Normal = transpose(invMat3Model) * aNormal;"
"	vs_out.TexCoords = aTexCoords;"
"	vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);" // NEW
"	gl_Position = projection * view * model * vec4(aPos, 1.0);"
"}";
//
// FRAGMENT SHADER
//
const char* DepthMapFragmentShader =
"#version 330 \r\n"
""
"out vec4 FragColor;"
""
"in VS_OUT {"
"vec3 FragPos;"
"vec3 Normal;"
"vec2 TexCoords;"
"vec4 FragPosLightSpace;" // NEW
"} fs_in;"
""
"uniform sampler2D diffuseTexture;"
"uniform sampler2D shadowMap;" // NEW
""
"uniform vec3 lightPos;"
"uniform vec3 viewPos;"
""
"float ShadowCalculation(vec4 fragPosLightSpace)"
"{"
""
"	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;"
""
"	projCoords = projCoords * 0.5 + 0.5;"
""
"	float closestDepth = texture(shadowMap, projCoords.xy).r;"
""
"	float currentDepth = projCoords.z;"
""
"	float shadow = currentDepth > closestDepth ? 1.0 : 0.0;"
""
"	return shadow;"
"}"
""
"void main()"
"{"
"	vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;"
"	vec3 normal = normalize(fs_in.Normal);"
"	vec3 lightColor = vec3(0.3);"
""
"	vec3 ambient = 0.3 * color;"
""
"	vec3 lightDir = normalize(lightPos - fs_in.FragPos);"
"	float diff = max(dot(lightDir, normal), 0.0);"
"	vec3 diffuse = diff * lightColor;"
""
"	vec3 viewDir = normalize(viewPos - fs_in.FragPos);"
"	vec3 reflectDir = reflect(-lightDir, normal);"
"	float spec = 0.0;"
"	vec3 halfwayDir = normalize(lightDir + viewDir);"
"	spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);"
"	vec3 specular = spec * lightColor;"
""
"	float shadow = ShadowCalculation(fs_in.FragPosLightSpace);"
"	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;"
""
"	FragColor = vec4(lighting, 1.0);"
"}";

//
// ----==== PTNDepth SHADER ====----
//
// VERTEX SHADER
const char* VSPTNDepth0 =
"#version 330 \r\n"
""
"	in vec3 position;"
""
"	uniform mat4 projectionMatrix;"
"	uniform mat4 viewMatrix;"
"	uniform mat4 transformationMatrix;"
""
"	void main(void) {"
"		gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);"
"}";
// FRAGMENT SHADER
const char* FSPTNDepth0 =
"#version 330 \r\n"
""
"	void main(void) {"
//"		gl_FragColor = vec4(gl_FragCoord.z);"
"}";

//// VERTEX SHADER
//const char* VSPTNDepth =
//"#version 330 \r\n"
//""
//"	in vec3 position;"
//"	in vec2 textureCoordinates;"
//"	in vec3 normal;"
//""
//"	uniform mat4 projectionMatrix;"
//"	uniform mat4 viewMatrix;"
//"	uniform mat4 viewMatrixInv;"
//"	uniform mat4 transformationMatrix;"
//""
//"	uniform mat4 toShadowMapSpace;" // NEW
//""
//"	uniform vec3 lightPosition;"
//"	uniform vec4 plane;"
//""
//"	out vec2 pass_textureCoordinates;"
//"	out vec3 surfaceNormal;"
//"	out vec3 toLightVector;"
//"	out vec3 toCameraVector;"
//""
//"	out vec4 shadowCoords;" // NEW
//""
//"	void main(void) {"
//""
//"		vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
//"		mat4 toShadowMapSpace2 = -0.5 + 0.5 * toShadowMapSpace;" // NEW // Here we get info about display coords in texture sampling
//"		shadowCoords = toShadowMapSpace2 * worldPosition;"       // NEW // (x, y) for texture coordinates and z component for depth in (x, y) chord
//""
//"		gl_ClipDistance[0] = dot(worldPosition, plane);"
//"		gl_Position = projectionMatrix * viewMatrix * worldPosition;"
//"		pass_textureCoordinates = textureCoordinates;"
//""
//"		surfaceNormal = ( transformationMatrix * vec4(normal, 0.0) ).xyz;"
//"		toLightVector = lightPosition - worldPosition.xyz;"
//"		toCameraVector = (viewMatrixInv * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;"
//"}";
//// FRAGMENT SHADER
//const char* FSPTNDepth =
//"#version 330 \r\n"
//""
//"	in vec2 pass_textureCoordinates;"
//"	in vec3 surfaceNormal;"
//"	in vec3 toLightVector;"
//"	in vec3 toCameraVector;"
//""
//"	in vec4 shadowCoords;" // NEW
//""
//"	uniform vec3 lightColour;"
//"	uniform float shineDamper;"
//"	uniform float reflectivity;"
//""
//"	uniform sampler2D modelTexture;"
//"	uniform sampler2D shadowMap;" // NEW
//""
//"	out vec4 out_Color;"
//""
//"	void main(void) {"
//""
//"		float objectNearestLight = texture(shadowMap, shadowCoords.xy).r;" // NEW r component (Depth info)
//"		float lightFactor = 1.0f;" // NEW
//"		if(shadowCoords.z > objectNearestLight) {" // NEW
//"			lightFactor = 0.1;" // NEW
//"		}" // NEW
//""
//"		vec3 unitNormal = normalize(surfaceNormal);"
//"		vec3 unitLightVector = normalize(toLightVector);"
//""
//"		float nDot1 = dot(unitNormal, unitLightVector);"
//"		float brightness = max(nDot1, 0.2);"
//"		vec3 diffuse = brightness * lightColour;"
//""
//"		vec3 unitVectorToCamera = normalize(toCameraVector);"
//"		vec3 lightDirection = -unitLightVector;"
//"		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal); "
//""
//"		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera); "
//"		specularFactor = max(specularFactor, 0.0); "
//""
//"		float dampedFactor = pow(specularFactor, shineDamper); "
//""
//"		vec3 finalSpecular = dampedFactor * reflectivity * lightColour;"
//""
//"		out_Color = vec4(diffuse * lightFactor, 1.0) * texture(modelTexture, pass_textureCoordinates) + vec4(finalSpecular, 1.0);" // NEW lightFactor
//"}";

// VERTEX SHADER
const char* VSPTNDepth =
"#version 330 \r\n"
""
"	in vec3 position;"
"	in vec2 textureCoordinates;"
"	in vec3 normal;"
""
"	uniform mat4 projectionMatrix;"
"	uniform mat4 viewMatrix;"
"	uniform mat4 viewMatrixInv;"
"	uniform mat4 transformationMatrix;"
""
"	uniform vec3 lightPosition;"
"	uniform vec4 plane;"
""
"	out vec2 pass_textureCoordinates;"
"	out vec3 surfaceNormal;"
"	out vec3 toLightVector;"
"	out vec3 toCameraVector;"
""
"	uniform mat4 lightSpaceMatrix;" // NEW
""
"	out vec4 FragPosLightSpace;" // NEW
""
"	void main(void) {"
""
"		vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
""
"		gl_ClipDistance[0] = dot(worldPosition, plane);"
"		gl_Position = projectionMatrix * viewMatrix * worldPosition;"
"		pass_textureCoordinates = textureCoordinates;"
""
//"	    FragPosLightSpace = lightSpaceMatrix * vec4(vec3(transformationMatrix * vec4(position, 1.0)), 1.0);" // NEW
"	    FragPosLightSpace = lightSpaceMatrix * transformationMatrix * vec4(position, 1.0);" // NEW Shadow coord
""
"		surfaceNormal = ( transformationMatrix * vec4(normal, 0.0) ).xyz;"
"		toLightVector = lightPosition - worldPosition.xyz;"
"		toCameraVector = (viewMatrixInv * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;"
"}";
// FRAGMENT SHADER
const char* FSPTNDepth =
"#version 330 \r\n"
""
"	in vec2 pass_textureCoordinates;"
"	in vec3 surfaceNormal;"
"	in vec3 toLightVector;"
"	in vec3 toCameraVector;"
""
//"	in vec3 FragPos;" // NEW
"	in vec4 FragPosLightSpace;" // NEW
""
"	uniform vec3 lightColour;"
"	uniform float shineDamper;"
"	uniform float reflectivity;"
""
"	uniform sampler2D modelTexture;"
"	uniform sampler2D shadowMap;" // NEW
""
"	out vec4 out_Color;"
""
"	float ShadowCalculation(vec4 fragPosLightSpace)" // NEW FUNCTION
"	{"
"		vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;"
"		projCoords = projCoords * 0.5 + 0.5;"
"		float closestDepth = texture(shadowMap, projCoords.xy).r;"
"		float currentDepth = projCoords.z;"
"		float shadow = currentDepth > closestDepth ? 1.0 : 0.0;"
"		return shadow;"
"	}"
""
"	void main(void) {"
""
"		vec3 unitNormal = normalize(surfaceNormal);"
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
"		float shadow = ShadowCalculation(FragPosLightSpace);" // NEW
""
//"		vec4 shadowCoordinateWdivide = FragPosLightSpace / FragPosLightSpace.w ;"
//"		shadowCoordinateWdivide.z += 0.0005;"
//"		float distanceFromLight = texture2D(shadowMap, shadowCoordinateWdivide.st).z;"
//"		float shadow2 = 1.0;"
//"		if (FragPosLightSpace.w > 0.0) shadow2 = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0;"
"		out_Color = vec4(diffuse, 1.0) * texture(modelTexture, pass_textureCoordinates) * (1.3 - shadow) + vec4(finalSpecular, 1.0);" // NEW lightFactor
"}";