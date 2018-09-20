#include <iostream>
#include "DrivelGenerators.h"

void generate_dict(const char *filename, SharedTextARC text_arc) {
    std::sort(text_arc.strings.begin(), text_arc.strings.end(), [](const String &one, const String &other) {
        return strcmp(one.date, other.date) < 0;
    });

    write_file(filename, text_arc);
}

bool pass_sym(const char *str, long long *ind) {
    if (!isalpha(str[*ind]) && str[*ind] != 0) {
        --*ind;
        return true;
    };
    return false;
}

void generate_rhyme(const char *filename, SharedTextARC text_arc) {
    std::sort(text_arc.strings.begin(), text_arc.strings.end(), [](const String &one, const String &other) {
        const char *rev_one = one.date + one.size;
        const char *rev_other = other.date + other.size;

        if (rev_other == other.date) {
            return false;
        };
        if (rev_one == one.date) {
            return true;
        }

        for (long long i = 0, k = 0;;) {
            if (pass_sym(rev_other, &k)) {
                if (&rev_other[k] == other.date) {
                    return false;
                }
                continue;
            }
            if (pass_sym(rev_one, &i)) {
                if (&rev_one[i] == one.date) {
                    return true;
                }
                continue;
            }

            if (rev_one[i] < rev_other[k]) {
                return true;
            } else if (rev_one[i] > rev_other[k]) {
                return false;
            };

            if (&rev_one[i] == one.date) {
                return true;
            }
            if (&rev_other[k] == other.date) {
                return false;
            }
            --i, --k;
        }
    });

    write_file(filename, text_arc);
}

void generate_origin(const char *filename, SharedTextARC text_arc) {
    write_file(filename, text_arc);
}