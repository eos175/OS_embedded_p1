# Proyecto 1 | The Bootloader


Inicialmente se iba a utilizar [Pure64](https://github.com/ReturnInfinity/Pure64) sin embargo a pesar que funcionaba no se estaba del todo de acuerdo debido a muchisimas cosas como ejemplo: usa [VESA](https://wiki.osdev.org/VESA_Video_Modes) como salida de video, q actualmente se considera obsoleto... mas basura

Como bootloader vamos a utilizar [Limine](https://github.com/limine-bootloader/limine), un bootloader moderno, para x86/x86_64 BIOS/UEFI. Este bootloader soporta multiples protocolos como `Multiboot 1`, `Chainloading` entre otros, sin embargo se va a iniciar con el protocolo [stivale 2](https://github.com/stivale/stivale)...


La decision de este bootloader de debe a las siguiente [discucion](https://forum.osdev.org/viewtopic.php?f=11&t=37455).

Es usado por [skiftOS](https://github.com/skiftOS/skift) un OS bastante desarollado... mas basura



### Instalar

me faltan alguno, pero ahi se agregan

```bash
sudo apt install nasm gcc xorriso
```

### Build / Run

```bash
make clean all run
```


### Otros // ** dar nombre a esto **

Para Pixel art una buena opcion es usar [piskel](https://www.piskelapp.com)

las imagenes se embeben ***(buscar el termino correcto para embeben)*** en el codigo y una copia png se guarda en la carpeta `/res` 

los bmp se puede comprimir usando [RLC Encoding](https://es.wikipedia.org/wiki/Run-length_encoding) hay una implemtacion ya escrita para esto, buscar mirar `main.c / files.h` sin embargo no es obligatorio, solo para reducir el binario, q visual ande mejor....


rutinas de video de alto nivel **(agregar ejemplos y doc de esto)**

**queria pasar elto a camel case Video_FillRect...** pero sera luego :(

```c++
void video_refresh();

void video_fill_rect(const rect_t rect, const color_t color);

void video_draw_rect(const rect_t rect, const color_t color);

void video_draw_bmp(const rect_t rect, const color_t *data);

void video_blit_bmp(const rect_t dst, const rect_t src, const color_t *data);
```


### Notas 

si hay dudas con algo, siempre se puede hacer un archivo c/c++, python y compilar en la pc *no qemu, virtualbox...*, para probar, tambien se puede desabilitar `main.c` desde `kernel.c`, poner algun `sleep(10000000);` y sino ultimadamente usar gdb q de todas formas somos expertos. 

**cada vez q se llama a `video_refresh()` borra todos los `printf`**


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

