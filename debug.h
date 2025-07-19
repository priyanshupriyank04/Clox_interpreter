#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset); //helps disassemble one line at a time, returns integer offset of next instruction in bytecode stored in chunk 

#endif