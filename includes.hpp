
/**
	RIGHT TO USE, DISTRIBUTE AND MODIFY
	===================================

	Copyright (C) 2015 Ganesh Prasad Sahoo - All Rights Reserved

	You may use, distribute and modify this code under the Terms 
	of GNU GPL V3 License. You should have received a copy of the
	GNU GPL v3 License with this file. If not please write to
		
		sir.gnsp@gmail.com

	or visit 
	
		http://www.gnu.org/licenses/gpl.txt


*****************************************************************************
*/


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

//#define _DEBUG

#ifdef _DEBUG
#define DEBUG(...) __VA_ARGS__
#else
#define DEBUG(...)
#endif

#endif
