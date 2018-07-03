void INPUT_is_key_down(WrenVM* vm) {
  const char* keyName = wrenGetSlotString(vm, 1); 
  SDL_Keycode keycode =  SDL_GetKeyFromName(keyName);
  bool result = ENGINE_getKeyState(&engine, keycode).isPressed;
  wrenSetSlotBool(vm, 0, result); 
}

void GRAPHICS_pset(WrenVM* vm) 
{ 
  int16_t x = floor(wrenGetSlotDouble(vm, 1)); 
  int16_t y = floor(wrenGetSlotDouble(vm, 2)); 
  uint32_t c = floor(wrenGetSlotDouble(vm, 3)); 
  ENGINE_pset(&engine, x,y,c);
}

WrenForeignMethodFn WREN_bind_foreign_method( 
    WrenVM* vm, 
    const char* module, 
    const char* className, 
    bool isStatic, 
    const char* signature) {

  if (strcmp(module, "graphics") == 0) { 
    if (strcmp(className, "Graphics") == 0) {
      if (isStatic && strcmp(signature, "pset(_,_,_)") == 0) {
        return GRAPHICS_pset; // C function for Math.add(_,_).
      } 
      // Other foreign methods on Math...
    } 
    // Other classes in main...
  } else if (strcmp(module, "input") == 0) { 
    if (strcmp(className, "Keyboard") == 0) {
      if (isStatic && strcmp(signature, "isKeyDown(_)") == 0) {
        return INPUT_is_key_down;
      } 
      // Other foreign methods on Math...
    } 
    // Other classes in main...
  } 
  // Other modules...

  return NULL;
}

char* WREN_load_module(WrenVM* vm, const char* name) {
  char* base = "src/engine/";
  char* extension = ".wren";

  char* path;
  path = malloc(strlen(base)+strlen(name)+strlen(extension)+1); /* make space for the new string (should check the return value ...) */
  strcpy(path, base); /* copy name into the new var */
  strcat(path, name); /* add the extension */
  strcat(path, extension); /* add the extension */

  return readEntireFile(path);
}

// Debug output for VM
void WREN_write(WrenVM* vm, const char* text) {
  printf("%s", text);
}

void WREN_error( 
    WrenVM* vm,
    WrenErrorType type, 
    const char* module, 
    int line, 
    const char* message) {
  if (type == WREN_ERROR_COMPILE) {
    printf("%s:%d: %s\n", module, line, message);
  } else if (type == WREN_ERROR_RUNTIME) {
    printf("Runtime error: %s\n", message);
  } else if (type == WREN_ERROR_STACK_TRACE) {
    printf("  %d: %s\n", line, module);
  } 
}

WrenVM* WREN_create(void) {
  WrenConfiguration config; 
  wrenInitConfiguration(&config);
  config.writeFn = WREN_write; 
  config.errorFn = WREN_error; 
  config.bindForeignMethodFn = WREN_bind_foreign_method; 
  config.loadModuleFn = WREN_load_module; 

  return wrenNewVM(&config);
}

void WREN_free(WrenVM* vm) {
  if (vm != NULL) {
    wrenFreeVM(vm);
  }
}
