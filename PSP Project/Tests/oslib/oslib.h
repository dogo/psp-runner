// Minimal OSLib stub so the game logic compiles and runs on the host (see Tests/sim.cpp)
#ifndef OSLIB_STUB_H
#define OSLIB_STUB_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;
typedef u32 OSL_COLOR;
#define RGB(r, g, b)		((OSL_COLOR)(0xff000000 | ((b) << 16) | ((g) << 8) | (r)))
#define RGBA(r, g, b, a)	((OSL_COLOR)(((a) << 24) | ((b) << 16) | ((g) << 8) | (r)))

#define OSL_SCREEN_WIDTH	480
#define OSL_IN_RAM			0
#define OSL_SWIZZLED		0
#define OSL_PF_8888			0
#define OSL_FMT_STREAM		0
#define OSL_DIALOG_NONE		0
#define OSL_KEY_SQUARE		0
#define OSL_MB_OK			0

typedef struct {
	int sizeX, sizeY, frameSizeX, frameSizeY, stretchX, stretchY, x, y;
} OSL_IMAGE;
typedef struct { int dummy; } OSL_SOUND;

struct OSL_PAD_STUB { struct { int cross, start; } pressed, released; };
extern OSL_PAD_STUB osl_pad;

// The tests pick the random seed through the time the game seeds rand() with
extern u32 gSeed;
static inline u32 sceKernelGetSystemTimeLow() { return gSeed; }

// Reads the real size from the PNG header, so hitboxes match the game assets
static inline OSL_IMAGE *oslLoadImageFilePNG(const char *path, int, int)
{
	FILE *file = fopen(path + 1, "rb"); // "/Res/x.png" -> "Res/x.png" (run from "PSP Project")
	if (!file)
		return NULL;
	unsigned char h[24];
	size_t n = fread(h, 1, 24, file);
	fclose(file);
	if (n != 24)
		return NULL;
	OSL_IMAGE *img = (OSL_IMAGE *)calloc(1, sizeof(OSL_IMAGE));
	img->sizeX = img->frameSizeX = img->stretchX = (h[16] << 24) | (h[17] << 16) | (h[18] << 8) | h[19];
	img->sizeY = img->frameSizeY = img->stretchY = (h[20] << 24) | (h[21] << 16) | (h[22] << 8) | h[23];
	return img;
}
static inline void oslDeleteImage(OSL_IMAGE *img) { free(img); }
static inline void oslSetImageFrameSize(OSL_IMAGE *img, int w, int h) { img->frameSizeX = w; img->frameSizeY = h; }
static inline void oslSetImageFrame(OSL_IMAGE *, int) {}
static inline void oslDrawImageXY(OSL_IMAGE *, int, int) {}
static inline void oslSetTransparentColor(OSL_COLOR) {}
static inline void oslDisableTransparentColor() {}
static inline void oslFlushKey() {}
static inline void oslSetBkColor(OSL_COLOR) {}
static inline void oslSetTextColor(OSL_COLOR) {}
#define oslPrintf_xy(x, y, ...)	((void)0)
#define oslFatalError(...)		(fprintf(stderr, __VA_ARGS__), exit(1))

static OSL_SOUND gSound;
static inline OSL_SOUND *oslLoadSoundFileMP3(const char *, int) { return &gSound; }
static inline void oslSetSoundLoop(OSL_SOUND *, int) {}
static inline void oslPlaySound(OSL_SOUND *, int) {}
static inline int oslMake3Buttons(int, int, int, int, int, int) { return 0; }
static inline void oslMessageBox(const char *, const char *, int) {}

#endif
