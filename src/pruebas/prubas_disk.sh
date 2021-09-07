# Creando disco
MKDISK -PATH=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -U=K -SIZE=1000
# Creando primera particion
Fdisk -size = 100 -u=K -PATH=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -name =Primaria1 
# Creando segunda particion
Fdisk -size = 100 -u=K -PATH=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -name =Primaria2 
# Creando tercera particion
Fdisk -size = 200 -u=K -PATH=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -name =Primaria3
# Creando una particion extendida
Fdisk -size = 500 -type=E -u=K -PATH=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -name =Extendida1

# Creando primera logica
Fdisk -size = 100 -type = L -u=K -PATH=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -name =Logica1
# Creando segunda logica
Fdisk -size = 100 -type = L -u=K -PATH=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -name =Logica2
# Creando tercera logica
Fdisk -size = 100 -type = L -u=K -PATH=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -name =Logica3
# Creando cuarta logica
Fdisk -size = 100 -type = L -u=K -PATH=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -name =Logica4


mount -path=/home/erick/Clases/Archivos/Laboratorio/Pruebas/Disk.dk -name=Primaria1 #071a


pause

REP -name=disk -path=/home/erick/Clases/Archivos/Laboratorio/Pruebas/disk.svg -id =071a -ruta=/home/erick/archivos/fase2/reportes
REP -name=mbr -path=/home/erick/Clases/Archivos/Laboratorio/Pruebas/disk.svg -id =071a -ruta=/home/erick/archivos/fase2/reportes