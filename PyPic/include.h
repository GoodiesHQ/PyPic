#pragma once
#ifdef _DEBUG
#define YES_DEBUG
#undef _DEBUG
#endif
#include <Python.h>
#pragma comment(lib, "python27.lib")
#ifdef YES_DEBUG
#define _DEBUG 1
#endif
#pragma comment(lib, "FreeImage.lib")

//#include <FreeImage.h>
//#include <FreeImageIO.h>

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <map>
#include <unordered_map>

/*
	Simple python extension to get the most common color in an image.
	I don't work with photos hardly ever, so simplicity is key, here.
*/

#define MODULE_NAME "pypic"
#define PP_RED "red"
#define PP_GREEN "green"
#define PP_BLUE "blue"
#define PP_DARK "dark "
#define PP_LIGHT "light "
typedef std::pair<std::string, size_t> colormask;
static PyDictObject *extensions;
