#ifndef FILE_POS_H
#define FILE_POS_H

/**
 * Struktura reprezentující pozici ve streamu.
 */
struct FilePos
{
	unsigned long line = 0;
	unsigned long pos = 0;
	bool crLf = false; // Flag, který kontroluje, zda nebyla nastavena 
	void accept(const char c)
	{
		if(!crLf)
		{
			if(c == '\r') // Ošetřuje newline na windows
			{
				crLf = true;
			}
			else
			{
				pos++;
			}
		}
		if(c == '\n')
		{
			line += 1;
			pos = 0;
			crLf = false;
		}
	}
};

#endif
