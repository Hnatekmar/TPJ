#ifndef FILE_POS_H
#define FILE_POS_H

#include <string>

/**
 * Struktura reprezentující pozici ve streamu.
 */
struct FilePos
{
    unsigned long line = 1;
    unsigned long pos = 0;
    inline void accept(const char& c)
    {
        if(c == '\n')
		{
			line += 1;
            pos = 0;
        }
        else
        {
            pos++;
        }
	}
};

#endif
