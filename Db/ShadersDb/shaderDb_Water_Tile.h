//
// Shader_GUI
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