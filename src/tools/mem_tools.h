#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>

typedef void* (*interface_t)(const char* Name_, int Ret_);
typedef void* abstract_interface;

class MemTools
{
public:
	static abstract_interface get_interface(const char* _module, const char* _interface);
	static std::uint8_t* pattern_scaner(const char* module_name, const char* signature) noexcept;
};