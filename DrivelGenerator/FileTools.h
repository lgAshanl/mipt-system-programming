#include <fstream>
#include "assert.h"
#include "cstring"

#ifndef DRIVELGENERATOR_FILETOOLS_H
#define DRIVELGENERATOR_FILETOOLS_H
#endif //DRIVELGENERATOR_FILETOOLS_H

#ifndef DRIVELGENERATOR_SHAREDTEXT_H
#define DRIVELGENERATOR_SHAREDTEXT_H

#include "SharedText.h"

#endif //DRIVELGENERATOR_SHAREDTEXT_H

char *read_file(const char *filename, size_t *size);

void write_file(const char *filename, SharedTextARC &text_arc);