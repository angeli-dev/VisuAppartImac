// Vertex Shader
#version 110

#define M_PI 3.1415926535897932384626433832795

varying vec4 pos_sommet; 
varying vec3 nml_sommet;
uniform mat4 view_matrix;
uniform vec3 light_world_position;

// A disposition :
// gl_ModelViewMatrix : matrice 4*4 
// gl_NormalMatrix : matrice 3*3 (équivalent de la modelview matrix pour les normales)
// view_matrix : matrix 4*4 qui est la view matrix
// pos_sommet : position du sommet (dans son repère propre)
// nml_sommet : normal à la surface au sommet (dans son repère propre)
/* Propriétés de lumière

*/

// Exemple de transformation d'un vec3 b en vec4 a
// vec4 a = vec4(b,1.0);
// vec4 a = vec4(b,0.0);

// Produit scalaire : dot
// Exemple :
// vec3 a = vec3(1.,0.,1.);
// vec3 b = vec3(1.,0.,1.);
// float resultat = dot(a,b);

void main() {
	// Modele de Lambert
	vec4 pos_light_cam = view_matrix * vec4(light_world_position/1.0,1.0);
	vec3 nml_cam = normalize(gl_NormalMatrix*nml_sommet);
	vec4 pos_sommet_cam = gl_ModelViewMatrix*pos_sommet;
	pos_sommet_cam.xyz = pos_sommet_cam.xyz/pos_sommet_cam.w;
	vec3 PL = pos_light_cam.xyz - pos_sommet_cam.xyz;
	float distance_carre = dot(PL,PL); 
	PL = normalize(PL);
	float d_power = dot(nml_cam,normalize(PL));
	if (d_power < 0.0) d_power = 0.0;
	vec3 light_intensity = (gl_FrontMaterial.diffuse.rgb*gl_LightSource[0].diffuse.rgb)/(1.0+distance_carre*M_PI);
	gl_FragColor = vec4(light_intensity*d_power,1.);

	// Ajout Modele de Blinn-Phong
	if(d_power>0.0) {
		vec3 view_direction = normalize(-pos_sommet_cam.xyz);
		vec3 half_direction = normalize(PL + view_direction);
		float s_angle = max(0.0,dot(nml_cam,half_direction));
		float s_power = pow(s_angle, gl_FrontMaterial.shininess); 
		vec3 spec_intensity = gl_LightSource[0].specular.rgb/(1.0+distance_carre*M_PI);
		gl_FragColor += vec4(spec_intensity*s_power,0.0);
	}
	
	/* AUTRE TESTS
	//gl_FragColor = light_intensity;
	//gl_FragColor = vec4(pos_light_cam.rgb,1.);
	*/

	// TEST visu normales
	vec3 normal = gl_NormalMatrix * normalize(nml_sommet);
	gl_FragColor = vec4(normalize(normal),1.0);
	//gl_FragColor = vec4(nml_sommet,1.0);
	// */

	//gl_FragColor = vec4(light_world_position/10.0,1.0);

	//gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}

