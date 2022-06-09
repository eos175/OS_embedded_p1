# Proyecto 1 | The Bootloader

### Introducción:

Este proyecto consiste en poder utilizar el bootloader para cargar un sistema operativo, en este caso el kernel es un video juego basado en el siguiente video [LEAD](https://www.youtube.com/watch?v=pJuJIqd1Uhw), la idea general es aprender como el bootloader hace toda una serie de pasos para darle el control al kernel y este con todas sus herramientas pre cargadas, de paso a lo que queres ver en nuestro computador. 

[![Video result](https://i.imgur.com/AwE7bzZ.png)](https://www.youtube.com/watch?v=EwG3dfR_G10 "Video result - Click to Watch!"

### Investigación del bootloader:

Inicialmente se iba a utilizar [Pure64](https://github.com/ReturnInfinity/Pure64) sin embargo, a pesar que funcionaba no se estaba del todo de acuerdo debido a muchisimas cosas como ejemplo: usa [VESA](https://wiki.osdev.org/VESA_Video_Modes) como salida de video, que actualmente se considera obsoleto, además de que presentaba incompatibilidad con los drivers de USB por ende teniamos que buscar la forma de crear este apartado por nuestra cuenta, por lo que añadia complejidad al proyecto, por ende se toma la decision de no utilizarlo a pesar de que nos permitia trabajar en QEMU por ejemplo.

En el proceso encontramos al bootloader [Limine](https://github.com/limine-bootloader/limine), un bootloader moderno, para x86/x86_64 BIOS/UEFI. Este bootloader soporta multiples protocolos como `Multiboot 1`, `Chainloading` entre otros, sin embargo se va a iniciar con el protocolo [stivale 2](https://github.com/stivale/stivale), esto debido a que logra compensar las deficiencias del protocolo `Multiboot 1`. De manera resumida para el uso de `Stivale` se necesitan dos archivos `kernel.c` y `linker.ld`, donde se debe definir una etiqueta para que el sector de arranque la encuentre, además de la pila, buffer, puntos de entrada y modos de texto. Todo esto se puede ver en el siguiente [ejemplo](https://wiki.osdev.org/Stivale_Bare_Bones) en el cual se muestra lo mínimo para poder configuar el mismo. La decision final de utilizar este bootloader, es debido a la siguiente [discucion](https://forum.osdev.org/viewtopic.php?f=11&t=37455). Donde se menciona que Limine es utilizado en varios OS bastante desarrollados como los son [skiftOS](https://github.com/skiftOS/skift) y [managarm](https://github.com/managarm/managarm), esto genero la confianza suficiente para ser utilizado en este proyecto.

### Seguridad de la arquitectura x_86:

No solo las amanezas del exterior pueden alterar el comportamiento de los programas que se diseñan, tambien lo pueden hacer los del propio sistema, es por eso que la seguridad interna juega un papel fundamental en los OS, ya que un programa puede invadir memoria de la cual no debería de tener acceso y corromper informacion o incluso ejecutar instrucciones del CPU que no debería de poder tener acceso. La seguridad de bajo nivel es lo que se tratara en este apartado. Los anillos son los encargados de dar acceso a los recursos de los diversos procesos que se generan a la hora de ejecutar un programa. En la arquitecuta x_86 tiene solo dos anillos, el anillo 0 y 3. Por supuesto, hay más niveles de seguridad en el OS, como lo son la paginacion y segmentacion que se encargan con el acceso a la memoria.

#### Visualizacion de los anillos:

![Anillos](https://github.com/eos175/OS_embedded_p1/blob/master/res/rings.png)

#### Anillo 0:
Aquí se encuentra el kernel puro, se le conoce como el modo supervisor, este modo posee la menor seguridad posible, pero el mayor acceso a los recusos, ya que aquí se manejan las interrupciones o modificar los registros para las diferentes tablas de descripcion. El OS, empieza en este modo.

#### Anillo 3:
Este es el llamado Userspace, aquí viven las aplicaciones con las que interactua el usuario, posee la mayor porteccion y por supuesto el menor acceso a los diferentes recursos del sistema. Para poder interactuar con el kernel desde esta capa de abstraccion se hace uso de los `syscalls`. 

#### Modo real:

Este es el principio de todo, aquí el procesador inicia en 16 bits, para lograr que el procesador se levante en este modo hay que seguir una serie de instrucciones a nivel de ensamblador. Aquí la longitud es de 16 bits como antes se menciono, eso quiere decir que a nivel de instrucciones se debe de usar la parte baja de los registros para operar. Por otra parte aquí se controlan los dispositivos y manejo de las instrucciones. Aquí trabajaremos con la pila y los modos de direccionamiento, además aquí no hay proteccion de la GDT para el hardware ni memoria virtual, ya que esta nos permite indicar los rangos de memoria con los que se trabajara.


#### Modo protegido:

En este modo se trabaja con diferente modos virtuales de memoria, los espacios alcanzan valores de 4GB, por otra parte, aquí hay proteccion de I/O de hardware y memoria, y como es sabido a la hora de brindar los anillos al sistema, las instrucciones a ejecutar se ven restringidas en este modo. Aquí se carga la GDT, se habilita la línea A20 y se deshabilita las interrupciones como lo manda el manual de desarrolladores de Intel.



### Instalar:

Necesitara tener instalado `xorriso`, ejecute el siguiente comando

```bash
sudo apt install nasm gcc xorriso
```

### Build / Run:

Para una emulacion en QEMU o similares con el siguiente comando es suficiente para ver la implementacion:

```bash
make clean all run
```

### Correr en hardware real:

Si desea cargar el diseño en una pc común y corriente, ubiquese en la carpeta del proyecto y verifique que se encuentra el archivo `disk.iso`, inserte una USB en la PC y ejecute el siguiente comando para verificar el nombre de su dispositivo USB:


```bash
sudo fdisk -l
```
Una vez verificado el nombre de la USB, ejecute el siguiente comando, en este caso el nombre que se obtuvo del comando anterior fue `/dev/sdb`:

```bash
sudo dd if=disk.iso         of=/dev/sdb         bs=4096 && sync
```


Listo, ahora su USB esta lista para bootear como un OS, que te diviertas!


### Graficos:

La herramienta [piskel](https://www.piskelapp.com) es de gran ayuda para poder crear las imagenes que desea cargar en su programa, esto le permitira tener un entorno más emocionante.


Para la utilizacion de las imagenes puede utilizar el archivo `main.py` para cargar la data-uri para poder generar el archivo `file.h` que es ahí donde estará la informacion o data que necesitará de las imagenes, estas fueron comprimidas usando [RLC Encoding](https://es.wikipedia.org/wiki/Run-length_encoding).


### Rutinas de alto nivel


#### Video

```c++
void video_refresh();

void video_fill_rect(const rect_t rect, const color_t color);

void video_draw_rect(const rect_t rect, const color_t color);

void video_draw_bmp(const rect_t rect, const color_t *data);

void video_blit_bmp(const rect_t dst, const rect_t src, const color_t *data);
```

#### Random

```c++
int64_t randint(int64_t a, int64_t b); // randint(0, 10) -> 0 .. 10
```

### Notas 

si hay dudas con algo, siempre se puede hacer un archivo c/c++, python y compilar en la pc *no qemu, virtualbox...*, para probar, tambien se puede desabilitar `main.c` desde `kernel.c`, poner algun `sleep(10000000);` y sino ultimadamente usar gdb q de todas formas somos expertos. 

**cada vez q se llama a `video_refresh()` borra todos los `printf`**

- como generador pseudo aleatorio se va usar [MTwister](https://github.com/ESultanik/mtwister)





### Referencia

https://github.com/limine-bootloader/limine-barebones

https://wiki.osdev.org/Stivale_Bare_Bones

https://devse.wiki/x86_64/premiers-pas/01-hello-world.html

https://github.com/MandelbrotOS/MandelbrotOS

https://github.com/ReturnInfinity/Pure64

https://github.com/includeos/IncludeOS

https://github.com/cfenollosa/os-tutorial

https://cs.lmu.edu/~ray/notes/nasmtutorial/

https://github.com/mpaland/printf

https://github.com/ESultanik/mtwister

