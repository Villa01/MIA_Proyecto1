# MIA_Proyecto1
**Desarrollado por:<br/>** 
Erick José André Villatoro Revolorio<br/>
201900907

El proyecto consta de una aplicación de comandos por consola que permite la simulación de un sistema de archivos EXT2 y EXT3, desde la creación de un disco duro, hasta la creación de archivos y carpetas. 

## Sintáxis de comandos
El proyecto es case insensitive y no importa el orden en el que se escriban los parámetros de los comandos.
### Comando sin parametros
 [Comando] 
### Comando con parametros
 [Comando] [Lista de parametros]

### Lista de parametros
[lista de parametros] [parametro] 
<br/>| [parametro]

### Parametro 
-[nombre del parametro] = [atributo]

Toda la aplicación tienen una lista de comandos predefinidos que pueden tener argumentos. 

## Lista de Comandos
### Mkdisk
Este comando crea un archivo binario que simula un disco duro, estos archivos binarios tienen la extensión dk y su contenido al inicio será 0. Cada archivo ocupa físicamente el tamaño indicado por los parámetros. Recibirá el nombre del archivo que simulará el disco duro y tendrá los siguientes parámetros:

| Parámetro | Categoría | Atributos | Valor por defecto|
|-----------|-----------|-------------|------------------|
| Size      | Obligatorio | Indica el tamaño del disco a crear. Debe ser positivo y mayor que cero. |
| f| Opcional| Indica el tipo de ajuste que se usa para crear las particiones del disco. Y puede contener los valores: 1. BF: Best Fit 2. WF: Worst Fit3. FF: Fisrt Fit.| FF |
| u | Opcional | Indica las unidades que utiliza para el parametro size. Sus valores pueden ser: 1. K: Kylobytes 2. M: Megabytes. | K | 
| Path | Obligatorio | Contiene la ruta en donde se crea el archivo binario que representa al disco. | 

#### Ejemplos de uso
>Mkdisk -Size=3000 –u=K -path=/home/user/Disco1.dk
>
>mkdisk –size=5 –u=M –path="/home/mis discos/Disco3.dk"
### Rmdisk
Este comando elimina el archivo binario que representa el disco duro. Tendrá los siguientes parámetros:

| Parámetro | Categoría | Atributos | Valor por defecto|
|-----------|-----------|-------------|------------------|
| Path | Obligatorio | Contiene la ruta en donde se crea el archivo binario que representa al disco. | 

#### Ejemplos de uso
>mDisk -path="/home/mis discos/Disco4.dk"
### Fdisk
Este comando maneja todas las operaciones de las particiones. Puede crear, eliminar y cambiarles tamaño. 
| Parámetro | Categoría | Atributos | Valor por defecto|
|-----------|-----------|-------------|------------------|
| size | Obligatorio | Indica el tamaño de la partición a crear y debe ser positivo.  | |
| u | Opcional | Indica las unidades que utiliza para el parametro size. Sus valores pueden ser: 1. K: Kylobytes 2. M: Megabytes. | K | 
| path | Obligatorio | Contiene la ruta en donde se encuentra el archivo binario que representa al disco. | 
| type | Opcional | Indica qué tipo de partición se creará. Puede contener los valores: 1. P: primaria 2. E: extendida 3. L: lógica | P | 
| f| Opcional| Indica el tipo de ajuste que se usa para asignar espacio en la partición. Y puede contener los valores: 1. BF: Best Fit 2. WF: Worst Fit3. FF: Fisrt Fit.| FF |
| delete | Opcional | Indica que se eliminará la partición y puede contener los atributos : 1. FAST: elimina la particion forma superficial 2. FULL: Elimina completamente el contenido de la partición. | FAST |
| name | Obligatorio | Indica el nombre que se le asigna a la partición. | 
| add | Opcional | Este parámetro se utiliza para agregar o quitar espacio a una partición, dependiendo si el número es positivo o negativo. 

#### Ejemplos de uso
>fdisk –Size=300 –path=/home/Disco1.disk –name=Particion1
>
>fdisk -delete=fast -name="Particion1"-path=/home/Disco1.dk
>
>fdisk -add=-500 –size=10 -u=K -path="/home/misdiscos/Disco4.disk" -name=Particion4

### Mount
Este comando montará una partición del disco en el sistema e imprime un resumen de las particiones montadas. A cada partición se le crea un identificador único. 
| Parámetro | Categoría | Atributos | Valor por defecto|
|-----------|-----------|-------------|------------------|
| path | Obligatorio | Contiene la ruta en donde se encuentra el archivo binario que representa al disco. | 
| name | Obligatorio | Indica el nombre de la partición. | 

#### Ejemplos de uso
> mount -path=/home/Disco1.disk -name=Part1
> 
> mount -path=/home/Disco2.disk -name=Part1 
### Umount
Este comando desmonta una partición del disco en el sistema. 

| Parámetro | Categoría | Atributos | Valor por defecto|
|-----------|-----------|-------------|------------------|
| id | Obligatorio | Especifica el id de la partición que se desea desmontar | 

#### Ejemplos de uso
> umount -id=071a
> 
> umount -id=072a

### Mkfs
Este comando realiza el formateo de una partición con el sistema de archivos ext2 o ext3. 
| Parámetro | Categoría | Atributos | Valor por defecto|
|-----------|-----------|-------------|------------------|
| id | Obligatorio | Especifica el id de la partición que se desea formatear | 
| type | Opcional | Indica que tipo de formateo se realiza. Puede contener los siguientes atributos: 1. Fast: formateo rápido 2. Full Formateo completo. | Full
| fs | Opcional | Indica qué sistema de archivos se utiliza. Sus valores pueden ser: 1. 2fs: EXT2 2. 3fs: EXT3.| 2fs |

#### Ejemplos de uso
> mkfs -type=fast -id=581A
>
> mkfs -id=582A
### Exec 
Este comando permite la ejecución de archivos .sh, que pueden contener todos los comandos descritos. 
| Parámetro | Categoría | Atributos | Valor por defecto|
|-----------|-----------|-------------|------------------|
| path | Obligatorio | Especifica la ruta donde se encuentra el archivo a ejecutar | 

### Ejemplos de uso 
> exec -path=/home/Desktop/calificacion.sh

### Rep
Este comando permite generar una serie de reportes del sistema. Se genera por medio de graphviz en una carpeta existente. 
| Parámetro | Categoría | Atributos | Valor por defecto|
|-----------|-----------|-------------|------------------|
| name | Obligatorio | Indica el nombre del reporte que se desea generar. Sus valores pueden ser: 1. MBR 2. DISK 3. SB 4. JOURNALING | |
| path | Obligatorio | Indica el la carpeta y el nombre del archivo del reporte.| |
| id | Obligatorio | Indica el id de la partición que se utiliza para generar los reportes| | 
| ruta | Opcional | Indica el nombre del archivo o carpeta del que se se muestra el reporte. | | 
| root | Opcional | Indica el índice del inodo que se utiliza como raíz para el reporte tree | 0 |

#### Ejemplos de uso
> rep –id=561A -Path=/home/user/reports/reporte1.jpg -name=mbr
> 
> rep -id=562A -Path=/home/user/reports/report2.pdf -
name=disk

### Pause 
Este parametro se utiliza en un archivo .sh para dar una pausa durante la ejecución y continuar tocando una tecla. 

#### Ejemplos de uso
> Pause