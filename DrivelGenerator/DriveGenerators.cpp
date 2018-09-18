#include "DrivelGenerators.h"

void generate_dict(const char *filename, SharedTextARC &text_arc) {
    std::sort(text_arc.strings.begin(), text_arc.strings.end(), [](const char *one, const char *other) {
        return strcmp(one, other) < 0;
    });

    write_file(filename, text_arc);
}

void generate_rhyme(const char *filename, SharedTextARC &text_arc) {
    std::sort(text_arc.strings.begin(), text_arc.strings.end(), [](const char *one, const char *other) {
        size_t one_len = strlen(one);
        size_t other_len = strlen(other);
        const char *rev_one = &one[one_len == 0 ? 0 : one_len - 1];
        const char *rev_other = &other[other_len == 0 ? 0 : other_len - 1];

        for (size_t i = 0;; --i) {
            auto a = &rev_one[i];
            if (rev_one[i] < rev_other[i]) {
                return true;
            } else if (rev_one[i] > rev_other[i]) {
                return false;
            };

            if (&rev_other[i] == other) {
                return false;
            }

            if (&rev_one[i] == one) {
                return true;
            }
        }
    });

    write_file(filename, text_arc);
}

void generate_origin(const char *filename, SharedTextARC &text_arc) {
    write_file(filename, text_arc);
}

