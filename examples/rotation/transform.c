#include <stddef.h>
#include <string.h>
#include <stdio.h>
// You'll need to include the DOME header
#include "dome.h"
#include "transform.c.inc"

static DOME_API_v0* core;
static WREN_API_v0* wren;
static CANVAS_API_v0* canvas;
static BITMAP_API_v0* bitmap;
static IO_API_v0* io;

void TRANSFORM_allocate(WrenVM* vm) {
  size_t CLASS_SIZE = 0; // This should be the size of your object's data
  void* obj = wren->setSlotNewForeign(vm, 0, 0, CLASS_SIZE);
}

void TRANSFORM_draw(WrenVM* vm) {
  wren->ensureSlots(vm, 5);
  DOME_Context ctx = core->getContext(vm);
  DOME_Bitmap* texture = wren->getSlotForeign(vm, 1);

  printf("%i\n", texture->width);
  DOME_Color* c;

  //canvas->draw(ctx, texture, 0, 0, DOME_DRAWMODE_BLEND);
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

  core->registerClass(ctx, "transform", "Transform", TRANSFORM_allocate, NULL);
  core->registerFn(ctx, "transform", "static Transform.draw(_,_,_)", TRANSFORM_draw);

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

