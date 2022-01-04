#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dome.h"
#include "transform.c.inc"
#include "transform.h"


void TRANSFORM_allocate(WrenVM* vm) {
  size_t CLASS_SIZE = sizeof(DOME_Bitmap);
  DOME_Bitmap * bmp = wren->setSlotNewForeign(vm, 0, 0, CLASS_SIZE);
}

void TRANSFORM_finalize(void* data) {
  DOME_Bitmap* bmp = data;
  free(bmp);
}

void TRANSFORM_loadFromFile(WrenVM* vm) {
  DOME_Bitmap * bmp = wren->getSlotForeign(vm, 0);
  const char * path = wren->getSlotString(vm, 1);
  DOME_Context ctx = core->getContext(vm);

  DOME_Bitmap * src = bitmap->fromFile(ctx, path);
  *bmp = *src;
  free(src);
}

void TRANSFORM_draw(WrenVM* vm) {
  DOME_Context ctx = core->getContext(vm);
  DOME_Bitmap * bmp = wren->getSlotForeign(vm, 0);
  int x = wren->getSlotDouble(vm, 1);
  int y = wren->getSlotDouble(vm, 2);
  canvas->draw(ctx, bmp, x, y, 1);
}

void TRANSFORM_getWidth(WrenVM* vm) {
  DOME_Context ctx = core->getContext(vm);
  DOME_Bitmap * bmp = wren->getSlotForeign(vm,0);
  wren->setSlotDouble(vm, 0, bmp->width);
}
void TRANSFORM_getHeight(WrenVM* vm) {
  DOME_Context ctx = core->getContext(vm);
  DOME_Bitmap * bmp = wren->getSlotForeign(vm,0);
  wren->setSlotDouble(vm, 0, bmp->height);
}

void TRANSFORM_rdraw(WrenVM* vm) {
  wren->ensureSlots(vm, 4);
  DOME_Context ctx = core->getContext(vm);
  DOME_Bitmap * image = wren->getSlotForeign(vm, 0);
  int32_t x = wren->getSlotDouble(vm, 1);
  int32_t y = wren->getSlotDouble(vm, 2);
  int32_t angleDeg = 0;
  double scaleX = 1;
  double scaleY = 1;

  int srcX = 0;
  int srcY = 0;
  int srcW = image->width;
  int srcH = image->height;

  bool contains;
  //========SLOT 3 IS THE MAP=========

  wren->setSlotString(vm, 4, "angle");
  contains = wren->getMapContainsKey(vm, 3, 4);
  if (contains) {
    //getMapValue(WrenVM* vm, int mapSlot, int keySlot, int valueSlot);
    wren->getMapValue(vm, 3, 4, 4);
    angleDeg = wren->getSlotDouble(vm, 4);
  }

  wren->setSlotString(vm, 4, "scaleX");
  contains = wren->getMapContainsKey(vm, 3, 4);
  if (contains) {
    //getMapValue(WrenVM* vm, int mapSlot, int keySlot, int valueSlot);
    wren->getMapValue(vm, 3, 4, 4);
    scaleX = wren->getSlotDouble(vm, 4);
  }

  wren->setSlotString(vm, 4, "scaleY");
  contains = wren->getMapContainsKey(vm, 3, 4);
  if (contains) {
    //getMapValue(WrenVM* vm, int mapSlot, int keySlot, int valueSlot);
    wren->getMapValue(vm, 3, 4, 4);
    scaleY = wren->getSlotDouble(vm, 4);
  }

  wren->setSlotString(vm, 4, "srcX");
  contains = wren->getMapContainsKey(vm, 3, 4);
  if (contains) {
    wren->getMapValue(vm, 3, 4, 4);
    srcX = wren->getSlotDouble(vm, 4);
  }

  wren->setSlotString(vm, 4, "srcY");
  contains = wren->getMapContainsKey(vm, 3, 4);
  if (contains) {
    wren->getMapValue(vm, 3, 4, 4);
    srcY = wren->getSlotDouble(vm, 4);
  }

  wren->setSlotString(vm, 4, "srcW");
  contains = wren->getMapContainsKey(vm, 3, 4);
  if (contains) {
    wren->getMapValue(vm, 3, 4, 4);
    srcW = wren->getSlotDouble(vm, 4);
  }

  wren->setSlotString(vm, 4, "srcH");
  contains = wren->getMapContainsKey(vm, 3, 4);
  if (contains) {
    wren->getMapValue(vm, 3, 4, 4);
    srcH = wren->getSlotDouble(vm, 4);
  }

  angleDeg %= 360;
  angleDeg = abs(angleDeg);
  float angle = (M_PI/180) * angleDeg;

  bool flip = false;

  if (angleDeg < 90 || angleDeg > 270) {
    flip = true;
    angle += M_PI;
  }

  int cX = srcW/2;
  int cY = srcH/2;

  for (int u = 0; u < srcW; u++) {
    for (int v = 0; v < srcH; v++) {
      
      if (u > image->width || u < 0 || v > image->height || v < 0) {
        continue;
      }

      DOME_Color preColor = bitmap->pget(image, srcX + u, srcY + v);
      
      if (preColor.value == 0x00000000) {
        continue;
      }

      iVEC sheared;
      if (flip) {
        sheared = shear(angle, u - cX, v - cY);
      } else {
        sheared = shear(angle, srcW - u - cX, srcH - v - cY);
      }

      int destX = sheared.x;
      int destY = sheared.y;

      if (scaleX == 1 && scaleY == 1) {
        canvas->pset(ctx, x + destX, y + destY, preColor);
      } else {
        canvas->rectfill(ctx, x + (destX*scaleX), y + (destY*scaleY), ceil(scaleX), ceil(scaleY), preColor);
      }
    }
  }
}

DOME_EXPORT DOME_Result PLUGIN_onInit(DOME_getAPIFunction DOME_getAPI,
    DOME_Context ctx) {

  // Fetch the latest Core API and save it for later use.
  core = DOME_getAPI(API_DOME, DOME_API_VERSION);
  io = DOME_getAPI(API_IO, IO_API_VERSION);
  canvas = DOME_getAPI(API_CANVAS, CANVAS_API_VERSION);
  bitmap = DOME_getAPI(API_BITMAP, BITMAP_API_VERSION);
  wren = DOME_getAPI(API_WREN, WREN_API_VERSION);
  //vm = core->getVM(ctx);

  core->log(ctx, "Initialising external module\n");

  // Register a module with it's associated source.
  // Avoid giving the module a common name.
  core->registerModule(ctx, "transform", TRANS_WREN_source);

  core->registerClass(ctx, "transform", "Transform", TRANSFORM_allocate, TRANSFORM_finalize);
  core->registerFn(ctx, "transform", "Transform.f_loadFromFile(_)", TRANSFORM_loadFromFile);
  core->registerFn(ctx, "transform", "Transform.width", TRANSFORM_getWidth);
  core->registerFn(ctx, "transform", "Transform.height", TRANSFORM_getHeight);
  core->registerFn(ctx, "transform", "Transform.draw(_,_)", TRANSFORM_draw);
  //core->registerFn(ctx, "transform", "Transform.sdraw(_,_,_,_,_,_)", TRANSFORM_rdraw);
  core->registerFn(ctx, "transform", "Transform.rdraw(_,_,_)", TRANSFORM_rdraw);

  // Returning anything other than SUCCESS here will result in the current fiber
  // aborting. Use this to indicate if your plugin initialised successfully.
  return DOME_RESULT_SUCCESS;
}

DOME_EXPORT DOME_Result PLUGIN_preUpdate(DOME_Context ctx) {
  return DOME_RESULT_SUCCESS;
}

DOME_EXPORT DOME_Result PLUGIN_postUpdate(DOME_Context ctx) {
  return DOME_RESULT_SUCCESS;
}
DOME_EXPORT DOME_Result PLUGIN_preDraw(DOME_Context ctx) {
  return DOME_RESULT_SUCCESS;
}
DOME_EXPORT DOME_Result PLUGIN_postDraw(DOME_Context ctx) {
  return DOME_RESULT_SUCCESS;
}

DOME_EXPORT DOME_Result PLUGIN_onShutdown(DOME_Context ctx) {
  return DOME_RESULT_SUCCESS;
}

