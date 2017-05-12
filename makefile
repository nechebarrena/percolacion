lista = percolacion.c funciones.c percolacion.h
all: $(lista)
	#gcc -std=c99 $(lista) -O3  -lm  -I"C:/Program Files (x86)/GnuWin32/include" -L"C:/Program Files (x86)/GnuWin32/lib" -lconfig -o percolacion #-fopenmp
	gcc -std=c99 $(lista) -O0  -lm -lconfig -o percolacion #-fopenmp
	#gcc $(lista) -O3  -lm -L(C:\Program Files (x86)\GnuWin32\lib) -I(C:\Program Files (x86)\GnuWin32\include) -lconfig -o percolacion #-fopenmp


 
   

clean:
	rm -f *.o

