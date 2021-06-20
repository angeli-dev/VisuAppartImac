#include "../include/Program.hpp"
#include <stdexcept>
#include <iostream>

bool Program::link() {
	glLinkProgram(m_nGLId);
	GLint status;
	glGetProgramiv(m_nGLId, GL_LINK_STATUS, &status);
	return status == GL_TRUE;
}

const std::string Program::getInfoLog() const {
	GLint length;
	glGetProgramiv(m_nGLId, GL_INFO_LOG_LENGTH, &length);
	char* log = new char[length];
	glGetProgramInfoLog(m_nGLId, length, 0, log);
	std::string logString(log);
	delete [] log;
	return logString;
}

// Build a GLSL program from source code
Program buildProgram(const GLchar* vsSrc, const GLchar* fsSrc) {
	Shader vs(GL_VERTEX_SHADER);
	vs.setSource(vsSrc);

	if(!vs.compile()) {
		throw std::runtime_error("Compilation error for vertex shader: " + vs.getInfoLog());
	}

	Shader fs(GL_FRAGMENT_SHADER);
	fs.setSource(fsSrc);

	if(!fs.compile()) {
		throw std::runtime_error("Compilation error for fragment shader: " + fs.getInfoLog());
	}

	Program program;
	program.attachShader(vs);
	program.attachShader(fs);

	if(!program.link()) {
		throw std::runtime_error("Link error: " + program.getInfoLog());
	}

	return program;
}

// Load source code from files and build a GLSL program
Program loadProgram(const FilePath& vsFile, const FilePath& fsFile) {
	std::cerr<<"Démarage compile shader"<<std::endl;
	//std::cerr<<"Vx loading : "<<vsFile<<std::endl;
	Shader vs = loadShader(GL_VERTEX_SHADER, vsFile);
	//std::cerr<<"Fg loading"<<std::endl;
	Shader fs = loadShader(GL_FRAGMENT_SHADER, fsFile);

	std::cerr<<"Shaders chargés"<<std::endl;
	if(!vs.compile()) {
		throw std::runtime_error("Compilation error for vertex shader (from file " + std::string(vsFile) + "): " + vs.getInfoLog());
	}
	if(!fs.compile()) {
		throw std::runtime_error("Compilation error for fragment shader (from file " + std::string(fsFile) + "): " + fs.getInfoLog());
	}
	std::cerr<<"Shaders compilés"<<std::endl;

	Program program;
	program.attachShader(vs);
	program.attachShader(fs);

	if(!program.link()) {
        throw std::runtime_error("Link error (for files " + vsFile.str() + " and " + fsFile.str() + "): " + program.getInfoLog());
	}
	std::cerr<<"Progamme pret"<<std::endl;

	return program;
}
