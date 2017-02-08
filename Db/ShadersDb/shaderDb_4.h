//
// VERTEX SHADER
//
const char* VS4 =
"	#version 330 core \r\n"
""
"	in vec3 position;"
"	in vec3 normal;"
"	in vec2 textureCoords;"
""
"	uniform mat4 projectionMatrix;"
"	uniform mat4 viewMatrix;"
"	uniform mat4 viewMatrixInv;"
"	uniform mat4 transformationMatrix;"
""
"	uniform vec3 lightPosition;"
"	uniform float useFakeLighting;"
""
"	out vec2 pass_textureCoords;"
""
"	out vec3 surfaceNormal;"
"	out vec3 toLightVector;"
"	out vec3 toCameraVector;"
""
"	out float visibility;"
""
"	const float density = 0.007;"
"	const float gradient = 1.5;"
""
"	void main() {"
""
"		vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
"		vec4 positionRelativeToCam = viewMatrix * worldPosition;"
""
"		gl_Position =  projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);"	
""	
"		pass_textureCoords = textureCoords;"
""	
"		vec3 actualNormal = normal;"
"		if(useFakeLighting > 0.5) {"
""	
"		actualNormal = vec3(0.0, 1.0, 0.0);"
"		}"

"		surfaceNormal = (transformationMatrix * vec4(actualNormal, 0.0)).xyz;"
"		toLightVector = lightPosition - worldPosition.xyz;"
"		toCameraVector =  (viewMatrixInv * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;"
""
"		// FOG \r\n"
"		float distance = length(positionRelativeToCam.xyz);"
""	
"		visibility = exp( -pow( (distance*density), gradient) );"
"		visibility = clamp(visibility, 0.0, 1.0);"
"	}";
//
// FRAGMENT SHADER
//
const char* FS4 =
"	#version 330 core \r\n"
""
"	in vec2 pass_textureCoords;"
"	in vec3 surfaceNormal;"
"	in vec3 toLightVector;"
"	in vec3 toCameraVector;"
""
"	in float visibility;"
""
"	out vec4 out_Color;"
""
"	uniform sampler2D textureSampler;"
"	uniform vec3 lightColor;"
"	uniform float shineDamper;"
"	uniform float reflectivity;"
"	uniform vec3 skyColor;"
""
"	void main () {"
""
"		vec3 unitNormal = normalize(surfaceNormal);"
"		vec3 unitLightVector = normalize(toLightVector);"
""
"		float nDot1 = dot(unitNormal, unitLightVector);"
"		float brightness = max(nDot1, 0.1);"                                                    
"		vec3 diffuse = brightness * lightColor;"
""
"		vec3 unitVectorToCamera = normalize(toCameraVector);"
"		vec3 lightDirection = - unitLightVector;"
"		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);"
""
"		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);"
"		specularFactor = max(specularFactor, 0.0);"
"		float dampedFactor = pow(specularFactor, shineDamper);"
"		vec3 finalSpecular = dampedFactor * reflectivity * lightColor;"
""
"		vec4 textureColor = texture(textureSampler, pass_textureCoords);"
""
"		if(textureColor.a < 0.5) {"
"			discard;"
"		}"
""
"		out_Color = vec4(diffuse, 1.0) * textureColor + vec4(finalSpecular, 1.0);"
"		out_Color = mix(vec4(skyColor, 1.0), out_Color, visibility);"
"	}";



