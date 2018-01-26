#include "Framebuffer.h"

using namespace AEON_ENGINE;

Framebuffer::Framebuffer(Window* window_)
{
	setFramebuffer(window_);
}

Framebuffer::~Framebuffer()
{
	//Empty
}

void Framebuffer::render(Shader* shader_)
{
	shader_->setInt("screenTexture", 0);

	//Bind to the default framebuffer and draw a plane with the attached framebuffer colour texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, m_texColourBuffer);

	m_mesh->render(shader_);

	glBindFramebuffer(GL_FRAMEBUFFER, 0); //Unbind the framebuffer as a precaution
}

void Framebuffer::setFramebuffer(Window* window_) {
	//Framebuffer
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	//Generate texture for framebuffer (For colour testing buffer)
	glGenTextures(1, &m_texColourBuffer);
	glBindTexture(GL_TEXTURE_2D, m_texColourBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window_->getScreenWidth(), window_->getScreenHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texColourBuffer, 0);

	//Renderbuffer object (similar to a texture, but much more efficient for when you don't need to sample from specific buffers) (For depth and stencil testing buffers)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window_->getScreenWidth(), window_->getScreenHeight());

	//Attack it to the currently bound framebuffer object
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	//Error checking and then unbinding the framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_screenWidth = window_->getScreenWidth();
	m_screenHeight = window_->getScreenHeight();

	loadMesh();
}

bool Framebuffer::loadMesh()
{
	m_mesh = new Mesh(Mesh::PrimitiveType::PLANE);

	return true;
}

void Framebuffer::updateFramebufferSize(Window* window_)
{
	if (m_screenWidth != window_->getScreenWidth() || m_screenHeight != window_->getScreenHeight()) {
		setFramebuffer(window_);
	
		//Set the class variables to the new screen width and height for next comparison
		m_screenWidth = window_->getScreenWidth();
		m_screenHeight = window_->getScreenHeight();
	}
}

void Framebuffer::bindBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}

void Framebuffer::unbindBuffer()
{
	//Bind back to the default framebuffer and draw a plane with the attached framebuffer colour texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}