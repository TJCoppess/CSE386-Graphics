/****************************************************
 * 2016-2025 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include "light.h"
#include "io.h"
#include "ishape.h"

 /**
  * @fn	color ambientColor(const color& mat, const color& lightColor)
  * @brief	Computes the ambient color produced by a single light at a single point.
  * @param	mat  	Ambient material property.
  * @param	lightColor	Light's color.
  * @return	Ambient color.
   */

color ambientColor(const color& mat, const color& lightColor) {
	/* CSE 386 - todo  */
	return glm::clamp(mat * lightColor, 0.0, 1.0);
	// return mat;
}

/**
 * @fn	color diffuseColor(const color &mat, const color &lightColor, const dvec3 &l, const dvec3 &n)
 * @brief	Computes diffuse color produce by a single light at a single point.
 * @param	mat		 	Material.
 * @param	lightColor	 	The light's color.
 * @param	l		 	Light vector.
 * @param	n		 	Normal vector.
 * @return	Diffuse color.
 */

color diffuseColor(const color& mat, const color& lightColor,
	const dvec3& l, const dvec3& n) {
	/* CSE 386 - todo  */
	return glm::clamp((mat * lightColor * glm::max(0.0, glm::dot(l,n))), 0.0, 1.0);
	// return mat;
}

/**
 * @fn	color specularColor(const color &mat, const color &lightColor, double shininess,
 *							const dvec3 &r, const dvec3 &v)
 * @brief	Computes specular color produce by a single light at a single point.
 * @param	mat		 	Material.
 * @param	lightColor	 	The light's color.
 * @param	shininess	Material shininess.
 * @param	r		 	Reflection vector.
 * @param	v		 	Viewing vector.
 * @return	Specular color.
 */

color specularColor(const color& mat, const color& lightColor,
	double shininess,
	const dvec3& r, const dvec3& v) {
	/* CSE 386 - todo  */

	return glm::clamp(mat * lightColor * glm::max(0.0, glm::pow(glm::clamp(glm::dot(r,v), 0.0, 1.0), shininess)), 0.0, 1.0);

	return mat;
}

/**
 * @fn	color totalColor(const Material &mat, const color &lightColor,
 *						const dvec3 &viewingDir, const dvec3 &normal,
 *						const dvec3 &lightPos, const dvec3 &intersectionPt,
 *						bool attenuationOn, const LightAttenuationParameters &ATparams)
 * @brief	Color produced by a single light at a single point. This includes the summation
 * of the ambient, diffuse, and specular components. Attenuation is also applied, if applicable.
 * @param	mat			  	Material.
 * @param	lightColor	  	The light's color.
 * @param	v	  			The v vector.
 * @param	n   		  	Normal vector.
 * @param	lightPos	  	Light position.
 * @param	intersectionPt	(x,y,z) of intersection point.
 * @param	attenuationOn 	true if attenuation is on.
 * @param	ATparams	  	Attenuation parameters.
 * @return	Color produced by a single light at a single point. This includes the summation
 * of the ambient, diffuse, and specular components. Attenuation is also applied, if applicable.
 */

color totalColor(const Material& mat, const color& lightColor,
	const dvec3& v, const dvec3& n,
	const dvec3& lightPos, const dvec3& intersectionPt,
	bool attenuationOn,
	const LightATParams& ATparams) {
	/* CSE 386 - todo  */
	dvec3 l = glm::normalize(lightPos - intersectionPt);
	dvec3 r = 2 * glm::clamp(glm::dot(l, n), 0.0, 1.0) * n - l;
	double AT = 1.0;
	color total;
	// Call the 3 functions above
	color A = ambientColor(mat.ambient, lightColor);
	color D = diffuseColor(mat.diffuse, lightColor, l, n);
	color S = specularColor(mat.specular, lightColor, mat.shininess, r, v);
	
	if (attenuationOn) {
		double distance = glm::distance(lightPos, intersectionPt);
		AT = 1.0 / (ATparams.constant + ATparams.linear * distance + ATparams.quadratic * glm::pow(distance, 2.0));
	}
	total = A + AT * (D + S);

	return glm::clamp(total, 0.0, 1.0);


	// return mat.diffuse;
}

/**
 * @fn	color PositionalLight::illuminate(const dvec3 &interceptWorldCoords,
 *										const dvec3 &normal, const Material &material,
 *										const dvec3& viewerPos, bool inShadow) const
 * @brief	Computes the color this light produces in RAYTRACING applications.
 * @param	interceptWorldCoords	(x, y, z) at the intercept point.
 * @param	normal				The normal vector.
 * @param	material			The object's material properties.
 * @param	viewerPos			Location of camera/viewer.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 */

color PositionalLight::illuminate(const dvec3& interceptWorldCoords,
	const dvec3& normal,
	const Material& material,
	const dvec3& viewerPos,
	bool inShadow) const {
	/* CSE 386 - todo  */

	if (!this->isOn) {
		return black;
	}
	if (inShadow) {
		return ambientColor(material.ambient, this->lightColor);
	}
	dvec3 l = glm::normalize(this->pos - interceptWorldCoords);
	dvec3 r = 2 * glm::clamp(glm::dot(l, normal), 0.0, 1.0) * normal - l;
	dvec3 v = glm::normalize(viewerPos - interceptWorldCoords);
	double AT = 1.0;
	color total;
	color A = ambientColor(material.ambient, this->lightColor);
	color D = diffuseColor(material.diffuse, this->lightColor, l, normal);
	color S = specularColor(material.specular, this->lightColor, material.shininess, r, v);

	if (this->attenuationIsTurnedOn) {
		double distance = glm::distance(this->pos, interceptWorldCoords);
		AT = 1.0 / (this->atParams.constant + this->atParams.linear * distance + this->atParams.quadratic * glm::pow(distance, 2.0));
	}
	total = A + AT * (D + S);

	return glm::clamp(total, 0.0, 1.0);

	// return material.diffuse;
}

/**
* @fn	bool PositionalLight::pointIsInAShadow(const dvec3& intercept, const dvec3& normal, const vector<VisibleIShapePtr>& objects, const dvec3& viewerPos) const
* @brief	Determines if an intercept point falls in a shadow.
* @param	intercept	the position of the intercept.
* @param	normal		the normal vector at the intercept point
* @param	objects		the collection of opaque objects in the scene
*/

bool PositionalLight::pointIsInAShadow(const dvec3& intercept,
	const dvec3& normal,
	const vector<VisibleIShapePtr>& objects) const {
	/* CSE 386 - todo  */
	// we must check if the shadow feeler hits an object and
	// if it is before the light or after the light
	for (VisibleIShapePtr object : objects) {
		OpaqueHitRecord hit;
		object->findClosestIntersection(getShadowFeeler(intercept, normal), hit);
		if (hit.t != FLT_MAX) {
			if (glm::distance(intercept, hit.interceptPt) < glm::distance(intercept, this->pos)) {
				return true;
			}
		}
	}
	return false;
}

/**
* @fn	Ray PositionalLight::getShadowFeeler(const dvec3& interceptWorldCoords, const dvec3& normal, const Frame &eyeFrame) const
* @brief	Returns the shadow feeler for this light.
* @param	interceptWorldCoords	the position of the intercept.
* @param	normal		The normal vector at the intercept point
*/

Ray PositionalLight::getShadowFeeler(const dvec3& interceptWorldCoords,
	const dvec3& normal) const {
	/* 386 - todo */
	dvec3 origin = interceptWorldCoords + EPSILON * normal; // offset ray origin = i + en
	dvec3 dir = this->pos - interceptWorldCoords; // = light Source - Object intersection
	Ray shadowFeeler(origin, dir);
	return shadowFeeler;
}

/**
 * @fn	color SpotLight::illuminate(const dvec3 &interceptWorldCoords,
 *									const dvec3 &normal, const Material &material,
 *									const Frame &eyeFrame, bool inShadow) const
 * @brief	Computes the color this light produces in raytracing applications.
 * @param	interceptWorldCoords				The surface properties of the intercept point.
 * @param	normal					The normal vector.
 * @param	material			The object's material properties.
 * @param	viewerPos			Location of camera/viewer.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 */

color SpotLight::illuminate(const dvec3& interceptWorldCoords,
	const dvec3& normal,
	const Material& material,
	const dvec3& viewerPos,
	bool inShadow) const {
	/* CSE 386 - todo  */

	if (SpotLight::isInSpotlightCone(this->pos, 
		this->spotDir, this->fov, interceptWorldCoords)) {
		return PositionalLight::illuminate(interceptWorldCoords,
			normal, material, viewerPos, inShadow);
	}
	else {
		return black;
	}

	return material.diffuse;
}

/**
* @fn	void SpotLight::setDir (double dx, double dy, double dz)
* @brief	Sets the direction of the spotlight.
* @param	dx		x component of the direction
* @param	dy		y component of the direction
* @param	dz		z component of the direction
*/

void SpotLight::setDir(double dx, double dy, double dz) {
	spotDir = glm::normalize(dvec3(dx, dy, dz));
}

/**
* @fn	SpotLight::isInSpotlightCone(const dvec3& spotPos, const dvec3& spotDir, double spotFOV, const dvec3& intercept)
* @brief	Determines if an intercept point falls within a spotlight's cone.
* @param	spotPos		where the spotlight is positioned
* @param	spotDir		normalized direction of spotlight's pointing direction
* @param	spotFOV		spotlight's field of view, which is 2X of the angle from the viewing axis
* @param	intercept	the position of the intercept.
*/

bool SpotLight::isInSpotlightCone(const dvec3& spotPos,
	const dvec3& spotDir,
	double spotFOV,
	const dvec3& intercept) {
	/* CSE 386 - todo  */

	dvec3 l = intercept - spotPos;
	double spotCosine = glm::dot(-l, spotDir);
	double cutoffangle = glm::cos(glm::length(spotDir) / glm::length(l));
	if (spotCosine > glm::cos(cutoffangle)) {
		return true;
	}

	return false;
}
