#include "Transform.h"

using namespace AEON_ENGINE;

Transform::Transform() {};
Transform::~Transform() {};

void Transform::updateModelMatrix()
{
	if (transformHasChanged) {
		modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		transformHasChanged = false;
	}
}

void Transform::translateBy(float x_, float y_, float z_)
{
	translationMatrix = glm::translate(translationMatrix, glm::vec3(x_, y_, z_));
	position += glm::vec3(x_, y_, z_);

	transformHasChanged = true;
}

void Transform::translateBy(glm::vec3 pos_)
{
	translationMatrix = glm::translate(translationMatrix, pos_);
	position += pos_;

	transformHasChanged = true;
}

void Transform::rotateBy(float angle_, float x_, float y_, float z_)
{
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle_), glm::vec3(x_, y_, z_));
	rotation += glm::vec3(x_, y_, z_);

	transformHasChanged = true;
}

void Transform::rotateBy(glm::vec4 rot_)
{
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rot_[0]), glm::vec3(rot_[1], rot_[2], rot_[3]));
	rotation += glm::vec3(rot_[1], rot_[2], rot_[3]);

	transformHasChanged = true;
}

void Transform::scaleBy(float x_, float y_, float z_)
{
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(x_, y_, z_));
	scale += glm::vec3(x_, y_, z_);

	transformHasChanged = true;
}

void Transform::scaleBy(glm::vec3 scale_)
{
	scaleMatrix = glm::scale(scaleMatrix, scale_);
	scale += scale_;

	transformHasChanged = true;
}

void Transform::setPosition(float x_, float y_, float z_)
{
	position = glm::vec3(x_, y_, z_);
	translationMatrix = glm::mat4();
	translationMatrix = glm::translate(translationMatrix, position);

	transformHasChanged = true;
}

void Transform::setPosition(glm::vec3 pos_)
{
	position = pos_;
	translationMatrix = glm::mat4();
	translationMatrix = glm::translate(translationMatrix, position);

	transformHasChanged = true;
}