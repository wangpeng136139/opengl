#pragma once
#include <string>
class Application
{
public:
	static void Init();
    static void Run();
	static void Render();
	static void Update();
public:
	static  std::string app_data_;
	static  std::string streammingAssetPath;

};

