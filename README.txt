------------PARCIAL 2-------------

Grupo colaborativo COIL

Notas: 

-El programa se puede ejecutar de 2 maneras, la version menu interno posee un main.cpp donde se llamara una
 funcion menu creada en el programa, donde se mostrara un menu eficiente para utilizar las funciones del programa, la segunda manera es por cmd donde se ejucutara de la siguiente forma:
	1- Incluir el path del archivo a la cmd --> cd "ubicacion de los archivos"
	2- Compilar el archivo --> g++ -o Inventario main.cpp Inventario.h
	3- Ejecutar menu de funciones tecleando lo siguiente --> Inventario.exe InventariO.csv

-El archivo csv debe llamarse "InventariO.csv" y debe estar dentro de la carpeta con los demas archivos para funcionar 

									
								//IMPORTANTE//

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-El programa hace uso de una Lista especial llamada ListaV, Lista que usa nodo tipo <vector>, donde su funcion es crear Una lista bidimensional y dinamica
	ListaV falla en funciones, minstock, maxstock, shellsort y binarysearch --> fallas que se escapan de nuestra comprension, en estos casos usamos un
	Vector de vectores de string (en este caso), ya que la sobrecarga del operador [] esta bien optimizada y libre de errores, a diferencia de la 
	sobrecarga del operador () de la ListaV, que posee errores que no pudimos solucionar en el lapso de tiempo dado, claro ejemplo de esto es la funcion
	adicional datos_xgrupos(), donde a veces funciona y otras veces no, esto se debe a que si son muchos los datos (ejemplo: grupo 7 --> griferias varias)
	que eson un total de 61 articulos, ListaV puede no funcionar, en estos casos volver iniciar el programa hasta que funcione, aqui radica nuestro problema
	con las estructuras dadas en clase, ya que se traban, o fallan en cosas internas que son muy complicadas en solucionar, por eso mismo utilizamos
	vector de la libreria c++, nos provee las sobrecargas necesitadas, sin errores internos. Al igual, ListaV puede variar en los errores segun el sistema, compañero de 
	trabajo directamente no le funciona ListaV, si ese fuera el caso, porfavor informarnos, ya que las funciones andan bien, sin contar las anomalias que
	ListaV puede llegar a producir en diferentes dispositivos.

-Las funciones GetCantidad() y GetDepositos() funcionan usualmente con ListaV, pero pueden estar sujetas a errores en otros dispositivos
	resultando en que la mayoria de funciones no anden, por esta misma razon decidimos crear una version sin ListaV, utilizando solo vectores de vectores
	en caso de que sea afectado por el problema.

-Para mas info sobre ListaV, ingresar a ListaV.h dentro de la carpeta Lista
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-Leer dentro de los archivos file.h y Inventario.h para mas informacion acerca de las funciones usadas en el programa.