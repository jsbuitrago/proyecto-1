#include "huffman.h"

void main(int argc, char* argv[])
{
	HUFFMAN *Compresor;
	Compresor = new HUFFMAN();
	if(argc > 1)
		Compresor->Procesar(argv[1]);
	delete Compresor;
}
