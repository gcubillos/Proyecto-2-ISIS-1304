// ISIS-1304 - FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - PROYECTO 2 - 201910
// EL PROYECTO DEBE SER DESARROLLADO EN GRUPOS DE A 3 PERSONAS MAXIMO
//
// DESARROLLADO POR:

#define _CRT_SECURE_NO_DEPRECATE 
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

// La representacion de la imagen
typedef struct img
{
	int ancho;
	int alto;
	unsigned char* informacion;
} Imagen;


// Función que carga el bmp en la estructura Imagen
void cargarBMP24(Imagen* imagen, char* nomArchivoEntrada);

// Función que guarda el contenido de la estructura imagen en un archivo binario
void guardarBMP24(Imagen* imagen, char* nomArchivoSalida);

//Función que inserta un mensaje en la imagen usando n bits por Byte
void insertarMensaje(Imagen* img, unsigned char mensaje[], int n);

//Función que lee un mensaje de una imagen dando la longitud del mensaje y el numero de bits por byte usados
void leerMensaje(Imagen* img, unsigned char msg[], int l, int n);

//Función que saca n bits de una secuencia de caracteres a partir de una posición dada
unsigned char sacarNbits(unsigned char secuencia[], int bitpos, int n);

// Programa principal
// NO MODIFICAR
int main(int argc, char* argv[]) {

	Imagen* img = (Imagen*)malloc(sizeof(Imagen));
	char msg[10000] = "";
	char op, temp;
	int num, l, n;
	char nomArch[256] = "";

	printf("\nISIS-1304 - FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - PROYECTO 2\n");

	if (argc != 5)
	{
		printf("Se ingreso un numero incorrecto de argumentos (%d) o se ingresaron de forma erronea... :(\n", argc);
		system("pause");
		return -1;
	}

	strcat(nomArch, argv[1]); //Se concatena el nombre del archivo en su variable respectiva
	op = argv[2][0]; //Se extrae la opción a realizar
	sscanf(argv[3], "%d", &num); //Se formatea el número de bits por Byte para leer o insertar

	if (op == 'w') {
		strcat(msg, argv[4]); //Se concatena la cadena a escribir en su variable, si se insertará un mensaje
	}
	else if (op == 'r') {
		sscanf(argv[4], "%d", &l); //Se formatea en l la longitud a leer de caracteres, si se leerá un mensaje
	}
	else {
		printf("Se ingreso una opcion invalida para el programa... :(\n");
		system("pause");
		return -1;
	}

	printf("Se ingresaron los %d argumentos correctamente!\n", argc);

	// Cargar los datos
	cargarBMP24(img, nomArch);

	if (op == 'w') {
		printf("\nMODO INSERTAR MENSAJE\n\n");
		printf(" - Longitud mensaje: %d bytes\n", strlen(msg));
		//msg[strlen(msg)] = '\0';

		printf(" - Insertando mensaje . . .\n");
		insertarMensaje(img, msg, num);
		printf(" - Insertado correctamente!\n");

		strcat(nomArch, "generado.bmp");
		guardarBMP24(img, nomArch);

		printf(" - Mensaje insertado y guardado exitosamente en el archivo/ruta '%s'! :D\n\n", nomArch);
	}
	else if (op == 'r') {
		printf("\nMODO LEER MENSAJE\n\n");

		for (int i = 0; i < l; i++) {
			msg[i] = 0;
		}
		msg[l] = 0;

		leerMensaje(img, msg, l, num);

		printf(" - Mensaje obtenido exitosamente! El mensaje es:\n\n\t%s\n\n", msg);
	}

	system("pause");
	return 0;
}

/**
* Inserta un mensaje, de a n bits por componente de color, en la imagen apuntada por img
* parámetro img: Apuntador a una imagen en cuyos pixeles se almacenará el mensaje.
* parámetro mensaje: Apuntador a una cadena de caracteres con el mensaje.
* parámetro n: Cantidad de bits del mensaje que se almacenarán en cada componente de color de cada pixel. 0 < n <= 8.
*/
// DESARROLLAR EN ENSAMBLADOR, *NO* SE PUEDEN USAR NOMBRES SIMBOLICOS
void insertarMensaje(Imagen* img, unsigned char mensaje[], int n) {
	// Variable que representa la longitud del mensaje
	int longitudMensaje = strlen(mensaje);

	// Variable que contiene la información del mensaje.
	char* caracteresMensaje = mensaje;

	// Variable que contiene la información de la imagen
	unsigned char* informacionImagen = img->informacion;

	// Variable que representa el número de bytes que tiene la imagen
	int numeroBytesImagen = img->alto * img->ancho;

	// Variable que indica si ya se terminó de escribir el mensaje
	int seTermina = 1;
	__asm {
		/*Anotación: No se incluyen los comandos de salvaguardar registros dado que las variables se declararon antes de la
		porción de ensamblador y creo que Visual Studio designa el espacio que va a utilizar para las variables. Sin embargo,
		se incluye lo que hubiera sido la asignación de las variables de manera comentada. Se incluyen las palabras de
		dword ptr y byte ptr dado que si no se especifica, en mi versión de Visual Studio, salen excepciones del estilo de
		Access violation reading location. Adicionalmente, se incluye en los comentarios el código en C correspondiente que
		se está traduciendo.
		*/

		// Variable que representa la longitud del mensaje
		//int longitudMensaje = strlen(mensaje);
		// Esta no estoy seguro de que funcione
		//mov eax, dword ptr[mensaje]
		//push eax
		//add         esp, 4
		//mov         dword ptr[longitudMensaje], eax

		//// Variable que contiene la información del mensaje.
		////char* caracteresMensaje = mensaje;
		//mov         eax, dword ptr[mensaje]
		//mov         dword ptr[caracteresMensaje], eax

		//// Variable que contiene la información de la imagen
		////unsigned char* informacionImagen = img->informacion;
		//mov         eax, dword ptr[img]
		//mov         ecx, dword ptr[eax + 8]
		//mov         dword ptr[informacionImagen], ecx

		//// Variable que representa el número de bytes que tiene la imagen
		////int numeroBytesImagen = img->alto * img->ancho;
		//mov         eax, dword ptr[img]
		//mov         ecx, dword ptr[img]

		//// Variable que representa el número de bytes que tiene la imagen
		////int numeroBytesImagen = img->alto * img->ancho;
		//mov         edx, dword ptr[eax + 4]
		//imul        edx, dword ptr[ecx]
		//mov         dword ptr[numeroBytesImagen], edx

		//// Variable que indica si ya se terminó de escribir el mensaje
		////int seTermina = 1;
		//mov         dword ptr[seTermina], 1


		// Se itera sobre la información de la imagen
		//for (int i = 0; i < numeroBytesImagen && seTermina; i++)
		mov dword ptr[ebp - 68], 0
		jmp primeraIteracionInsertar
		inicioCiclo :
		mov eax, dword ptr[ebp - 68]

			add eax, 1
			mov dword ptr[ebp - 68], eax
			primeraIteracionInsertar :
		mov eax, dword ptr[ebp - 68]
			cmp eax, dword ptr[numeroBytesImagen]
			jge seAcabaCicloInsertar
			cmp dword ptr[seTermina], 0
			je seAcabaCicloInsertar

			// Variable que almacena el valor del caracter actual
			//unsigned char caracterActual = informacionImagen[i];
			mov eax, dword ptr[informacionImagen]
			add eax, dword ptr[ebp - 68]
			mov cl, byte ptr[eax]
			mov byte ptr[ebp - 77], cl

			/* Corrimiento hacia la derecha para remover los bits menos significativos dependiendo de la
			variable n*/
			//caracterActual = caracterActual >> n;
			movzx eax, byte ptr[ebp - 77]
			mov ecx, dword ptr[n]
			sar eax, cl
			mov byte ptr[ebp - 77], al

			/*Corrimiento hacia la izquierda para poner los bits significativos en su lugar original y
			dejar con un valor de 0 los bits menos significativos (lugar en el que va a ir el mensaje)*/
			//caracterActual = caracterActual << n;
			movzx eax, byte ptr[ebp - 77]
			mov ecx, dword ptr[n]
			shl eax, cl
			mov byte ptr[ebp - 77], al

			// Revisa que el valor del bit sea correcto
			//if (!(i * n >= longitudMensaje * 8) || !(((i * n) + n) >= longitudMensaje * 8))
			mov eax, dword ptr[ebp - 68]
			imul eax, dword ptr[n]
			mov ecx, dword ptr[longitudMensaje]
			shl ecx, 3
			cmp eax, ecx
			jl condicionInicial
			mov eax, dword ptr[ebp - 68]
			imul eax, dword ptr[n]
			add eax, dword ptr[n]
			mov ecx, dword ptr[longitudMensaje]
			shl ecx, 3
			cmp eax, ecx
			jge otraCondicion

			condicionInicial :
		// Variable a la que se le asigna los bits que se van a insertar en el mensaje
		//unsigned char bitsParaInsertar = sacarNbits(caracteresMensaje, i * n, n);
		// Salvarguardar registros para llamar al método de sacarNBits
		mov eax, dword ptr[n]
			push eax
			mov ecx, dword ptr[ebp - 68]
			imul ecx, dword ptr[n]
			push ecx
			mov edx, dword ptr[caracteresMensaje]
			push edx
			call sacarNbits
			add esp, 0Ch
			mov byte ptr[ebp - 89], al

			// Se realiza un "or" de bit por bit que permite insertar los bits del mensaje en la imagen.
			//informacionImagen[i] = caracterActual | bitsParaInsertar;
			movzx eax, byte ptr[ebp - 77]
			movzx ecx, byte ptr[ebp - 89]
			or eax, ecx
			mov edx, dword ptr[informacionImagen]
			add edx, dword ptr[ebp - 68]
			mov byte ptr[edx], al

			jmp inicioCiclo

			//seTermina = 0;
			otraCondicion :
		mov dword ptr[seTermina], 0

			jmp inicioCiclo

			// Se actualiza la información de la imagen.
			//img->informacion = informacionImagen;
			seAcabaCicloInsertar :
		mov eax, dword ptr[img]
			mov ecx, dword ptr[informacionImagen]
			mov dword ptr[eax + 8], ecx

			// Recuperar registros	
			pop edi
			pop esi
			pop ebx
			add esp, 300
			mov esp, ebp
			pop ebp
			ret
	}
}

/**
* Extrae un mensaje de tamanio l, guardado de a n bits por componente de color, de la imagen apuntada por img
* parámetro img: Apuntador a una imagen que tiene almacenado el mensaje en sus pixeles.
* parámetro msg: Apuntador a una cadena de caracteres donde se depositará el mensaje.
* parámetro l: Tamanio en bytes del mensaje almacenado en la imagen.
* parámetro n: Cantidad de bits del mensaje que se almacenan en cada componente de color de cada pixel. 0 < n <= 8.
*/
// DESARROLLAR EN ENSAMBLADOR, SE PUEDEN USAR NOMBRES SIMBOLICOS
void leerMensaje(Imagen * img, unsigned char msg[], int l, int n) {
	// Se declaran las variables fuera del ensamblador para mantener los nombres de estas mismas.
	// Variable que contiene la información de la imagen
	unsigned char* informacionImagen = img->informacion;

	// Variable que contiene el número de bytes en el que se encuentra el mensaje
	int tamMensaje = ((l * 8) / n) + 1;

	// Variable que indica el número de bits que se han ingresado en un caracter del mensaje
	int numeroBitsMetidos = 0;

	// Variable que indica el byte del mensaje en el que se ingresa la información
	int byteActual = 0;

	__asm {
		/*Anotación: No se incluyen los comandos de salvaguardar registros dado que las variables se declararon antes de la
		porción de ensamblador y creo que Visual Studio designa el espacio que va a utilizar para las variables. Sin embargo,
		se incluye lo que hubiera sido la asignación de las variables de manera comentada. Se incluyen las palabras de
		dword ptr y byte ptr dado que si no se especifica, en mi versión de Visual Studio, salen excepciones del estilo de
		Access violation reading location. Adicionalmente, se incluye en los comentarios el código en C correspondiente que
		se está traduciendo.
		*/

		//// Mover valores de variable que contiene la información de la imagen
		//mov eax, dword ptr[img]
		//mov ecx, dword ptr[eax + 8]
		//mov dword ptr[informacionImagen], ecx

		//// Se asigna la variable que contiene el número de bytes en el que se encuentra la imagen
		//// Se utilizan los nombres de las variables pasados por el programa en C
		//mov eax, dword ptr[l]
		//// Se multiplica por 8
		//shl eax, 3
		//// Se divide por n
		//cdq
		//idiv dword ptr[n]
		//// Se suma 1
		//add eax, 1
		//mov dword ptr[tamMensaje], eax

		//// Variable que indica el número de bits que se han ingresado en un caracter del mensaje
		//mov dword ptr[numeroBitsMetidos], 0

		//// Variable que indica el byte del mensaje en el que se ingresa la información
		//mov dword ptr[byteActual], 0

		// Se itera sobre el tamaño de la imagen.
		// Se asigna un contador de 32 bits para iterar.
		mov dword ptr[ebp - 56], 0
		// Se salta porque se necesita empezar en cero para la primera iteración
		jmp primeraIteracion
		elCicloLeer :
		// Se asigna el valor del contador a eax y luego se le suma uno por cada iteración.
		mov eax, dword ptr[ebp - 56]
			add eax, 1
			mov dword ptr[ebp - 56], eax
			primeraIteracion :
		// Se pone el valor actual del contador en eax y se compara con el tamaño del mensaje para ver si ya se leyó todo.
		mov eax, dword ptr[ebp - 56]
			cmp eax, dword ptr[tamMensaje]
			// Si ya se leyó se acaba el método
			jge seAcaba

			// Variable que almacena el valor del caracter actual, se guarda en la posición -65 de ebp
			mov eax, dword ptr[informacionImagen]
			add eax, dword ptr[ebp - 56]
			mov cl, byte ptr[eax]
			mov byte ptr[ebp - 65], cl

			// Corrimiento hacia la izquierda que quita los bits que no hacen parte del mensaje 

			movzx eax, byte ptr[ebp - 65]
			mov ecx, 8
			sub ecx, dword ptr[n]
			shl eax, cl
			mov byte ptr[ebp - 65], al

			/*Caso en el que ya se completa un caracter del mensaje a retornar, y todavía quedan bits
			por escribir del caracter actual.*/
			//if ((numeroBitsMetidos + n) > 8)
			mov eax, dword ptr[numeroBitsMetidos]
			add eax, dword ptr[n]
			cmp eax, 8
			jle elseLeer

			// Se crea un caracter auxiliar que contiene la misma información del otro caracter
			//unsigned char caracterAuxiliar = caracterActual;
			mov al, byte ptr[ebp - 65]
			mov byte ptr[ebp - 77], al

			/* Se mira el byte del mensaje que se va a insertar y se realiza un "or" de bit por bit
			con los bits que siguen del mensaje contenido en el caracterActual (se realiza un
			corrimiento hacia la derecha por el número de bits que ya estaban ocupados en el mensaje).
			*/
			// caracterActual = caracterActual >> numeroBitsMetidos;
			movzx eax, byte ptr[ebp - 65]
			mov ecx, dword ptr[numeroBitsMetidos]
			sar eax, cl
			mov byte ptr[ebp - 65], al
			//msg[byteActual] = msg[byteActual] | caracterActual;
			mov eax, dword ptr[msg]
			add eax, dword ptr[byteActual]
			movzx ecx, byte ptr[eax]
			movzx edx, byte ptr[ebp - 65]
			or ecx, edx
			mov eax, dword ptr[msg]
			add eax, dword ptr[byteActual]
			mov byte ptr[eax], cl
			// Se actualiza el valor de la variable debido a que ya se llenó un byte
			//byteActual++;
			mov eax, dword ptr[byteActual]
			add eax, 1
			mov dword ptr[byteActual], eax
			/* Se mira el byte siguiente del mensaje que se va a insertar  y se realiza un "or" de bit
			por bit con los bits que faltaban por insertar del mensaje contenido en el caracterActual
			(se realiza un corrimiento hacia la izquierda por el número de bits que ya se insertaron).
			*/
			// caracterAuxiliar = caracterAuxiliar << (8 - numeroBitsMetidos);
			movzx eax, byte ptr[ebp - 77]
			mov ecx, 8
			sub ecx, dword ptr[numeroBitsMetidos]
			shl eax, cl
			mov byte ptr[ebp - 77], al
			// msg[byteActual] = msg[byteActual] | caracterAuxiliar;
			mov eax, dword ptr[msg]
			add eax, dword ptr[byteActual]
			movzx ecx, byte ptr[eax]
			movzx edx, byte ptr[ebp - 77]
			or ecx, edx
			mov eax, dword ptr[msg]
			add eax, dword ptr[byteActual]
			mov byte ptr[eax], cl

			jmp salirCondicion
			/* Caso en el que los bits codificados, los del mensaje a descifrar, caben en el byte correspondiente
			del mensaje a retornar*/

			// Corrimiento hacia la derecha dependiendo del número de bits ya ocupados en el byte a insertar
			// caracterActual = caracterActual >> numeroBitsMetidos;
		elseLeer:
		movzx eax, byte ptr[ebp - 65]
			mov ecx, dword ptr[numeroBitsMetidos]
			sar eax, cl
			mov byte ptr[ebp - 65], al
			// msg[byteActual] = msg[byteActual] | caracterActual;
			mov eax, dword ptr[msg]
			add eax, dword ptr[byteActual]
			movzx ecx, byte ptr[eax]
			movzx edx, byte ptr[ebp - 65]
			or ecx, edx
			mov eax, dword ptr[msg]
			add eax, dword ptr[byteActual]
			mov byte ptr[eax], cl
			// Se modifica la variable para indicar el número de bits insertados.
			// numeroBitsMetidos += n;
			salirCondicion :
		mov eax, dword ptr[numeroBitsMetidos]
			add eax, dword ptr[n]
			mov dword ptr[numeroBitsMetidos], eax

			/* Se pone la variable en un valor que es congruente con 8, dado que en este caso los bytes son
			de tamaño 8.*/
			// numeroBitsMetidos = numeroBitsMetidos % 8;
			mov eax, dword ptr[numeroBitsMetidos]
			// Se realiza un and bit a bit para sacar el módulo del número con respecto al 8.
			and eax, 80000007h
			jns yaEstaModulo
			dec eax
			or eax, 0FFFFFFF8h
			inc eax
			yaEstaModulo :
		mov dword ptr[numeroBitsMetidos], eax
			// Se revisa si ya se completó de llenar un byte
			// if (numeroBitsMetidos == 0)
			cmp dword ptr[numeroBitsMetidos], 0
			jne elCicloLeer
			// byteActual++;
			mov eax, dword ptr[byteActual]
			add eax, 1
			mov dword ptr[byteActual], eax
			jmp elCicloLeer

			seAcaba :
		// Recurperar registros 
		pop edi
			pop esi
			pop ebx
			add esp, 276
			mov esp, ebp
			pop ebp
			ret
	}
}

/**
* Extrae n bits a partir del bit que se encuentra en la posición bitpos en la secuencia de bytes que
* se pasan como parámetro
* parámetro secuencia: Apuntador a una secuencia de bytes.
* parámetro n: Cantidad de bits que se desea extraer. 0 < n <= 8.
* parámetro bitpos: Posición del bit desde donde se extraerán los bits. 0 <= n < 8*longitud de la secuencia
* retorno: Los n bits solicitados almacenados en los bits menos significativos de un unsigned char
*/
// DESARROLLAR EN ENSAMBLADOR, SE PUEDEN USAR NOMBRES SIMBOLICOS
unsigned char sacarNbits(unsigned char secuencia[], int bitpos, int n) {
	// DESARROLLO OPCIONAL: Puede ser útil para el desarrollo de los procedimientos obligatorios.
	// Variable que contiene la información de la secuencia
	unsigned char* informacionSecuencia = secuencia;

	// Variable que representa el número del byte en el que empieza la secuencia
	// Se divide por 8 bitpos debido a que int redondea hacia abajo
	int bytePosicionSecuencia = bitpos / 8;

	// Variable que representa el número del bit en el que se empieza la secuencia.
	// Se realiza módulo ocho para obtener el desplazamiento en el byte.
	int bitPosicionSecuencia = bitpos % 8;

	// Variable que obtiene la información del byte actual
	unsigned char informacionByte = informacionSecuencia[bytePosicionSecuencia];

	/* Corrimiento hacia la izquierda que deja únicamente los bits que nos interesan del mensaje.
	Lo demás lo deja en 0.*/
	informacionByte = informacionByte << bitPosicionSecuencia;

	__asm {
		/*Anotación: No se incluyen los comandos de salvaguardar registros dado que las variables se declararon antes de la
		porción de ensamblador y creo que Visual Studio designa el espacio que va a utilizar para las variables. Sin embargo,
		se incluye lo que hubiera sido la asignación de las variables de manera comentada. Se incluyen las palabras de
		dword ptr y byte ptr dado que si no se especifica, en mi versión de Visual Studio, salen excepciones del estilo de
		Access violation reading location. Adicionalmente, se incluye en los comentarios el código en C correspondiente que
		se está traduciendo.
		*/

		// Variable que contiene la información de la secuencia
		//unsigned char* informacionSecuencia = secuencia;
		//mov eax, dword ptr[secuencia]
		//mov dword ptr[informacionSecuencia], eax

		//// Variable que representa el número del byte en el que empieza la secuencia
		//// Se divide por 8 bitpos debido a que int redondea hacia abajo
		////int bytePosicionSecuencia = bitpos / 8;
		//mov eax, dword ptr[bitpos]
		//cdq
		//and edx, 7
		//add eax, edx
		//sar eax, 3
		//mov dword ptr[bytePosicionSecuencia], eax

		//// Variable que representa el número del bit en el que se empieza la secuencia.
		//// Se realiza módulo ocho para obtener el desplazamiento en el byte.
		////int bitPosicionSecuencia = bitpos % 8;
		//mov eax, dword ptr[bitpos]
		//	and eax, 80000007h
		//	dec eax
		//	or eax, 0FFFFFFF8h
		//	inc eax

		//	// Variable que representa el número del bit en el que se empieza la secuencia.
		//	// Se realiza módulo ocho para obtener el desplazamiento en el byte.
		//	//int bitPosicionSecuencia = bitpos % 8;
		//	mov dword ptr[bitPosicionSecuencia], eax

		//	// Variable que obtiene la información del byte actual
		//	//unsigned char informacionByte = informacionSecuencia[bytePosicionSecuencia];
		//	mov eax, dword ptr[informacionSecuencia]
		//	add eax, dword ptr[bytePosicionSecuencia]
		//	mov cl, byte ptr[eax]
		//	mov byte ptr[informacionByte], cl

		//	/* Corrimiento hacia la izquierda que deja únicamente los bits que nos interesan del mensaje.
		//	Lo demás lo deja en 0.*/
		//	//informacionByte = informacionByte << bitPosicionSecuencia;
		//	movzx eax, byte ptr[informacionByte]
		//	mov ecx, dword ptr[bitPosicionSecuencia]
		//	shl eax, cl
		//	mov byte ptr[informacionByte], al

		// Caso que revisa si la secuencia se encuentra en más de un byte
		//if ((bitPosicionSecuencia + n) > 8)
		mov eax, dword ptr[bitPosicionSecuencia]
		add eax, dword ptr[n]
		cmp eax, 8
		jle elseSacarNBits

		/* Variable que representa el número de bits a extraer que se encuentran en el primer byte
		de la secuencia empezando desde bytePosicionSecuencia.*/
		//int numeroBitsPrimerByte = 8 - bitPosicionSecuencia;
		mov eax, 8
		sub eax, dword ptr[bitPosicionSecuencia]
		mov dword ptr[ebp - 56], eax

		/* Variable que representa el número de bits a extraer que se encuentran en el segundo byte
		de la secuencia empezando desde bytePosicionSecuencia.*/
		//	int numeroBitsSegundoByte = n - numeroBitsPrimerByte;
		mov eax, dword ptr[n]
		sub eax, dword ptr[ebp - 56]
		mov dword ptr[ebp - 68], eax

		/* Corrimiento hacia la derecha que pone los bits que nos interesan en las posiciones más
		significativas.*/
		//	informacionByte = informacionByte >> (8 - n);
		movzx eax, byte ptr[informacionByte]
		mov ecx, 8
		sub ecx, dword ptr[n]
		sar eax, cl
		mov byte ptr[informacionByte], al

		/* Variable que obtiene la información del byte siguiente en el que se encuentra el resto de la
		información*/
		//	unsigned char informacionByteSiguiente = informacionSecuencia[bytePosicionSecuencia + 1];
		mov eax, dword ptr[informacionSecuencia]
		add eax, dword ptr[bytePosicionSecuencia]
		mov cl, byte ptr[eax + 1]
		mov byte ptr[ebp - 77], cl

		/* Corrimiento hacia la derecha que pone los bits que nos interesan en las posiciones menos significativas.*/
		//	informacionByteSiguiente = informacionByteSiguiente >> (8 - numeroBitsSegundoByte);
		movzx eax, byte ptr[ebp - 77]
		mov ecx, 8
		sub ecx, dword ptr[ebp - 68]
		sar eax, cl
		mov byte ptr[ebp - 77], al

		// Se hace un "or" bit a bit para concatenar los valores de la información del byte.
		//	informacionByte = informacionByte | informacionByteSiguiente;
		movzx eax, byte ptr[informacionByte]
		movzx ecx, byte ptr[ebp - 77]
		or eax, ecx
		mov byte ptr[informacionByte], al

		jmp seAcabaSacarNBits
		// Caso en el que la secuencia se encuentre en un único byte

		/* Corrimiento hacia la derecha que pone los bits que nos interesan en las posiciones menos
		significativas.*/
		//informacionByte = informacionByte >> (8 - n);
	elseSacarNBits:
		movzx eax, byte ptr[informacionByte]
			mov ecx, 8
			sub ecx, dword ptr[n]
			sar eax, cl
			mov byte ptr[informacionByte], al

			seAcabaSacarNBits :
		mov al, byte ptr[informacionByte]

			// Recuperar registros
			pop edi
			pop esi
			pop ebx
			add esp, 276
			mov esp, ebp
			pop ebp
			ret

	}
}

// Lee un archivo en formato BMP y lo almacena en la estructura img
// NO MODIFICAR
void cargarBMP24(Imagen * imagen, char* nomArchivoEntrada) {
	// bmpDataOffset almacena la posición inicial de los datos de la imagen. Las otras almacenan el alto y el ancho
	// en pixeles respectivamente
	int bmpDataOffset, bmpHeight, bmpWidth;
	int y;
	int x;
	int	residuo;

	FILE* bitmapFile;
	bitmapFile = fopen(nomArchivoEntrada, "rb");
	if (bitmapFile == NULL) {
		printf("No ha sido posible cargar el archivo: %s\n", nomArchivoEntrada);
		exit(-1);
	}

	fseek(bitmapFile, 10, SEEK_SET); // 10 es la posición del campo "Bitmap Data Offset" del bmp	
	fread(&bmpDataOffset, sizeof(int), 1, bitmapFile);

	fseek(bitmapFile, 18, SEEK_SET); // 18 es la posición del campo "height" del bmp
	fread(&bmpWidth, sizeof(int), 1, bitmapFile);
	bmpWidth = bmpWidth * 3;

	fseek(bitmapFile, 22, SEEK_SET); // 22 es la posición del campo "width" del bmp
	fread(&bmpHeight, sizeof(int), 1, bitmapFile);

	residuo = (4 - (bmpWidth) % 4) & 3; // Se debe calcular los bits residuales del bmp, que surjen al almacenar en palabras de 32 bits

	imagen->ancho = bmpWidth;
	imagen->alto = bmpHeight;
	imagen->informacion = (unsigned char*)calloc(bmpWidth * bmpHeight, sizeof(unsigned char));

	fseek(bitmapFile, bmpDataOffset, SEEK_SET); // Se ubica el puntero del archivo al comienzo de los datos

	for (y = 0; y < bmpHeight; y++) {
		for (x = 0; x < bmpWidth; x++) {
			int pos = y * bmpWidth + x;
			fread(&imagen->informacion[pos], sizeof(unsigned char), 1, bitmapFile);
		}
		fseek(bitmapFile, residuo, SEEK_CUR); // Se omite el residuo en los datos
	}
	fclose(bitmapFile);
}

// Esta función se encarga de guardar una estructura de Imagen con formato de 24 bits (formato destino) en un archivo binario
// con formato BMP de Windows.
// NO MODIFICAR
void guardarBMP24(Imagen * imagen, char* nomArchivoSalida) {
	unsigned char bfType[2];
	unsigned int bfSize, bfReserved, bfOffBits, biSize, biWidth, biHeight, biCompression, biSizeImage, biXPelsPerMeter, biYPelsPerMeter, biClrUsed, biClrImportant;
	unsigned short biPlanes, biBitCount;
	FILE* archivoSalida;
	int y, x;
	int relleno = 0;

	int residuo = (4 - (imagen->ancho) % 4) & 3; // Se debe calcular los bits residuales del bmp, que quedan al forzar en palabras de 32 bits


	bfType[2];       // Tipo de Bitmap
	bfType[0] = 'B';
	bfType[1] = 'M';
	bfSize = 54 + imagen->alto * ((imagen->ancho) / 3) * sizeof(unsigned char);       // Tamanio total del archivo en bytes
	bfReserved = 0;   // Reservado para uso no especificados
	bfOffBits = 54;    // Tamanio total del encabezado
	biSize = 40;      // Tamanio del encabezado de informacion del bitmap	
	biWidth = (imagen->ancho) / 3;     // Ancho en pixeles del bitmap	
	biHeight = imagen->alto;    // Alto en pixeles del bitmap	
	biPlanes = 1;    // Numero de planos	
	biBitCount = 24;  // Bits por pixel (1,4,8,16,24 or 32)	
	biCompression = 0;   // Tipo de compresion
	biSizeImage = imagen->alto * imagen->ancho;   // Tamanio de la imagen (sin ecabezado) en bits
	biXPelsPerMeter = 2835; // Resolucion del display objetivo en coordenada x
	biYPelsPerMeter = 2835; // Resolucion del display objetivo en coordenada y
	biClrUsed = 0;       // Numero de colores usados (solo para bitmaps con paleta)	
	biClrImportant = 0;  // Numero de colores importantes (solo para bitmaps con paleta)	

	archivoSalida = fopen(nomArchivoSalida, "w+b"); // Archivo donde se va a escribir el bitmap
	if (archivoSalida == 0) {
		printf("No ha sido posible crear el archivo: %s\n", nomArchivoSalida);
		exit(-1);
	}

	fwrite(bfType, sizeof(char), 2, archivoSalida); // Se debe escribir todo el encabezado en el archivo. En total 54 bytes.
	fwrite(&bfSize, sizeof(int), 1, archivoSalida);
	fwrite(&bfReserved, sizeof(int), 1, archivoSalida);
	fwrite(&bfOffBits, sizeof(int), 1, archivoSalida);
	fwrite(&biSize, sizeof(int), 1, archivoSalida);
	fwrite(&biWidth, sizeof(int), 1, archivoSalida);
	fwrite(&biHeight, sizeof(int), 1, archivoSalida);
	fwrite(&biPlanes, sizeof(short), 1, archivoSalida);
	fwrite(&biBitCount, sizeof(short), 1, archivoSalida);
	fwrite(&biCompression, sizeof(int), 1, archivoSalida);
	fwrite(&biSizeImage, sizeof(int), 1, archivoSalida);
	fwrite(&biXPelsPerMeter, sizeof(int), 1, archivoSalida);
	fwrite(&biYPelsPerMeter, sizeof(int), 1, archivoSalida);
	fwrite(&biClrUsed, sizeof(int), 1, archivoSalida);
	fwrite(&biClrImportant, sizeof(int), 1, archivoSalida);

	// Se escriben en el archivo los datos RGB de la imagen.
	for (y = 0; y < imagen->alto; y++) {
		for (x = 0; x < imagen->ancho; x++) {
			int pos = y * imagen->ancho + x;
			fwrite(&imagen->informacion[pos], sizeof(unsigned char), 1, archivoSalida);
		}
		fwrite(&relleno, sizeof(unsigned char), residuo, archivoSalida);
	}
	fclose(archivoSalida);
}