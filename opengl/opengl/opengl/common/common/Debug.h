#pragma once
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"

/// ����ļ���
#define DEBUG_LOG_INFO SPDLOG_INFO
#define DEBUG_LOG_WARN SPDLOG_WARN   
#define DEBUG_LOG_ERROR SPDLOG_ERROR

#define __CHECK_GL_ERROR__ { \
        auto gl_error_code=glGetError();\
        if(gl_error_code!=GL_NO_ERROR){\
            DEBUG_LOG_ERROR("gl_error_code: {}",gl_error_code);\
        }\
    }

#include <string>
class Debug
{
public:
	static void Log(std::string str);
	static void logError(std::string str);

};

