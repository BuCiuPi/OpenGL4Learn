#include "Shader.h"
std::string ShaderUtility::GetShader(const char* path)
{
	std::string shaderCode = "";
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(path);

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderCode = shaderStream.str();
	}
	catch (const std::exception&)
	{
		printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
	}

	return shaderCode;
}
