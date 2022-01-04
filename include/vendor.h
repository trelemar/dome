#include <tinydir.h>
#include <utf8.h>
#include <optparse.h>

#include <microtar/microtar.h>
#include <json/pdjson.h>
#include <mkdirp/mkdirp.h>

#ifndef __EMSCRIPTEN__
#include <whereami/whereami.h>
#endif

// Set up STB_IMAGE
#define STBI_FAILURE_USERMSG
#define STBI_NO_STDIO
#define STBI_ONLY_JPEG
#define STBI_ONLY_BMP
#define STBI_ONLY_PNG
#include <stb_image.h>

// Setup STB_VORBIS
#define STB_VORBIS_NO_PUSHDATA_API
#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>

#include <stb_image_write.h>
#include <stb_truetype.h>

#include <ABC_fifo.h>

#include <SDL_gpu/SDL_gpu.h>
