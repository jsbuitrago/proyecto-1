#ifndef __HUFFMAN_H
#define __HUFFMAN_H

#include <stdio.h>
#include <string.h>

struct CODIGO
{
	unsigned char *Cod;
	unsigned int Tam;
};

class CABECERA
{
	unsigned char Buf[322];
	unsigned int nIndice;
public:
	CABECERA(){nIndice=0;}
	bool Bit();
	void Bit(bool);
	unsigned char Byte();
	void Byte(unsigned char);
	unsigned int Tamano(){return nIndice;}
	unsigned char *Buffer(){return Buf;}
	void Reset(){nIndice=0;}
	void Adelante(unsigned int nBits){nIndice+=nBits;}
	void Atras(unsigned int nBits){nIndice-=nBits;}
};

class ARCH_IN
{
	FILE *Arch;
	unsigned char indice;
	unsigned char byte;
public:
	ARCH_IN(unsigned char*,unsigned char*);
	~ARCH_IN();
	bool Fallo(){return !Arch;}
	unsigned int Bit();
	unsigned int Byte();
	FILE *Base(){return Arch;}
};

class ARCH_OUT
{
	FILE *Arch;
	unsigned char indice;
	unsigned char byte;
public:
	ARCH_OUT(unsigned char*,unsigned char*);
	~ARCH_OUT();
	bool Fallo(){return !Arch;}
	void Bit(unsigned int);
	void Buffer(unsigned char*,unsigned int);
};

class HOJA_DESC
{
	class HOJA_DESC* pHDer;
	class HOJA_DESC* pHIzq;
	bool EsNodo;
	unsigned int Cod;
public:
	HOJA_DESC(class ARCH_IN*);
	~HOJA_DESC();
	unsigned int Descomprimir(class ARCH_IN*,FILE*, unsigned int);
};

class HOJA
{
	unsigned int cCod;
	class HOJA *HojaIzquierda;
	class HOJA *HojaDerecha;
	class HOJA *pNIzq;
	class HOJA *pNDer;
	unsigned int lFrec;
	bool EsNodo;
public:
	HOJA(unsigned int Codigo){pNIzq=NULL;pNDer=NULL;HojaIzquierda=NULL;HojaDerecha=NULL;lFrec=0;cCod=Codigo;EsNodo=false;}
	HOJA(HOJA *Izquierda, HOJA *Derecha);
	~HOJA();
	unsigned int Frecuencia(){return lFrec;}
	void Frecuencia(unsigned int Cuanto){lFrec=Cuanto;}
	class HOJA *HojaDer(){return HojaDerecha;}
	void HojaDer(HOJA *Cual){HojaDerecha=Cual;}
	class HOJA *HojaIzq(){return HojaIzquierda;}
	void HojaIzq(HOJA *Cual){HojaIzquierda=Cual;}
	unsigned char Codigo(){return cCod;}
	bool MoverADer();
	bool MoverAIzq();
	void CrearCodigo(class CABECERA*,struct CODIGO*);
	void CrearCabecera(class ARCH_OUT*);
};

class HUFFMAN
{
	unsigned int lFrec[257];
	HOJA *pUltima;
	CODIGO Caracter[257];
	void UnoMas(unsigned char Cual){lFrec[Cual]++;}
	void CrearHojas();
	void OrdenarHojas();
	void CrearArbol();
	void CrearCodigos();
public:
	HUFFMAN();
	~HUFFMAN();
	bool Comprimir(char*);
	bool Descomprimir(char*);
	unsigned int Procesar(char*);
};

#endif
