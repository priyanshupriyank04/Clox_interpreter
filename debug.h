#ifndef clox_debug.h
#define clox_debug.h

#include "chunk.h"

void dsassembleChunk(Chunk* chunk, const char* name);
int disassembleChunk(Chunk* chunk, int offset); //helps disassemble one line at a time, returns integer offset of next instruction in bytecode stored in chunk 

#endif