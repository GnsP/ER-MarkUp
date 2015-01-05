#ifndef ER_MARKUP_INCLUDES_HPP_
#define ER_MARKUP_INCLUDES_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "sstream.hpp"

extern int line_no;
extern int col_no;
extern int nodeCounter;

extern void error(const char *msg);

#define _DEBUG

#ifdef _DEBUG
#define DEBUG(...) __VA_ARGS__
#else
#define DEBUG(...)
#endif

#endif
