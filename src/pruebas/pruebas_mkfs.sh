#Contenido de calificacion.sh
#Crea 2 discos

#CREANDO DISCOS ----------------------------------------------------------------------------------------
mkdisk -size=75 -u=M -path=/home/erick/archivos/fase2/Disco1.dk -f=FF
mkdisk -u=K -size=51200 -path=/home/erick/archivos/fase2/Disco2.dk -f=FF

#CREANDO PARTICIONES ----------------------------------------------------------------------------------
#Crear particiones Disco1.dk
fdisk -type=P -u=M -name=Part1 -size=20 -path=/home/erick/archivos/fase2/Disco1.dk -f=BF
fdisk -type=P -u=M -name=Part2 -size=15 -path=/home/erick/archivos/fase2/Disco1.dk -f=BF
fdisk -type=P -u=M -name=Part3 -size=20 -path=/home/erick/archivos/fase2/Disco1.dk -f=BF

#Crear particiones Disco2.dk
fdisk -type=P -u=M -name=Part1D2 -size=20 -path=/home/erick/archivos/fase2/Disco2.dk -f=BF
fdisk -type=P -u=M -name=Part2D2 -size=10 -path=/home/erick/archivos/fase2/Disco2.dk -f=BF
fdisk -type=P -u=M -name=Part3D2 -size=10 -path=/home/erick/archivos/fase2/Disco2.dk -f=BF

#Monta las particiones 


mount -path=/home/erick/archivos/fase2/Disco1.dk -name=Part1 #071a
mount -path=/home/erick/archivos/fase2/Disco1.dk -name=Part2 #071b
mount -path=/home/erick/archivos/fase2/Disco1.dk -name=Part3 #071c

mount -path=/home/erick/archivos/fase2/Disco2.dk -name=Part1D2 #072a
mount -path=/home/erick/archivos/fase2/Disco2.dk -name=Part2D2 #072b
mount -path=/home/erick/archivos/fase2/Disco2.dk -name=Part3D2 #072c

#Crea el sistema de archivos en todas las particiones primarias
#fast reescribe el superbloque 
#full poner /0 y luego reescribir el superbloque

mkfs -type=fast -id=071a -fs=3fs
mkfs -type=full -id=072b
mkfs -type=fast -id=073c -fs=3fs