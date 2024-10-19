#ifndef COMMON_H_SENTRY
#define COMMON_H_SENTRY

/* Suppress warnings */
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4244)
#pragma warning(disable: 4996)
#pragma warning(disable: 26812)

/* For math defines from math.h/ Like M_PI etc.*/
#define _USE_MATH_DEFINES

/* C lib headers */
#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

/* SDL2 headers */
#include <SDL.h>
#if 0
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

/* Error macros */
#define	ERR_SDL_1(str)				fprintf(stderr, "[%s:%d] %s error: %s\n",\
										__FILE__, __LINE__, #str, SDL_GetError());

#define	ERR_SDL_2(str, is_fatal)		do { ERR_SDL_1(str) if(is_fatal) abort(); } while(0)

#define	GET_ARGS(A1, A2, A3, ...)	A3

#define	CHOOSE_ERR_MACRO(...)		GET_ARGS(__VA_ARGS__, ERR_SDL_2, ERR_SDL_1)
#define	ERR_SDL(...)				do { CHOOSE_ERR_MACRO(__VA_ARGS__)(__VA_ARGS__); } while(0)


#endif // !COMMON_H_SENTRY
