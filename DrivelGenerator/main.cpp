#include <iostream>
#include <assert.h>
#include "SharedText.h"
#include "FileTools.h"
#include "DrivelGenerators.h"

//-----------------------------------------------------------------------------------
//! DrivelGenerator
//! generate sorted files with alphabet order, -alphabet order, and original order
//!
//! @param [in] .input - input file
//!
//! @return .dict - alphabet order,
//! @return .rhyme - alphabet order,
//! @return .origin - original order
//!
// ---------------------------------------------------------------------------------

int main() {
    size_t size;
    char *buffer = read_file(".input", &size);
    auto text_arc = SharedText::BuildSharedText(buffer, size, false);

    generate_dict(".dict", text_arc);
    generate_rhyme(".rhyme", text_arc);
    generate_origin(".origin", text_arc);

    free(buffer);
    return 0;
}