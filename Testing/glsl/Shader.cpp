#include <gtest/gtest.h>
#include "Shader.hpp"

#include <string>
const std::string VALID_SHADER = \
"#version 130\n"\
"void main()\n"\
"{\n"\
"	gl_Position = vec4(0, 0, 0, 0);\n"\
"}";

const std::string INVALID_SHADER = \
"#version 130"\
"void main()"\
"{"\
"	gl_Position = vec4(0, 0, 0, 0);"\
"}";

#include "Platform.hpp"
using namespace midnight::glsl;
TEST(Shader, StateMachineInitialization)
{
	char* argv = new char[1];
	int one = 1;
	glutInit(&one, &argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("");
	glewInit();
}

TEST(Shader, ValidShader)
{
	ASSERT_NO_THROW(std::move<VertexShader>(VertexShader(VALID_SHADER)));
}

TEST(Shader, InvalidShader)
{
	ASSERT_THROW(std::move<VertexShader>(VertexShader(INVALID_SHADER)), CompilationError);
}
