# Proyecto1SO1
## Proyecto 1 sistemas operativos 1 vacaciones 2020

**Para genera los archivos de carga del modulo correr el comando:**

make all

**Realizar la carga del modulo con el comando:**

sudo insmod memo_200815492.ko

**Verificar la escritura del archivo ubicado en:**

/proc/memo_200815492_201314761

**Realizar la descarga del modulo con el comando**

sudo rmmod memo_200815492

**Verificar que en listado de modulos se encuentra el nuestro con el comando**

lsmod

**Consutlar Mensajes de los modulos**

dmesg

Se utilizó el **struct sysinfo meminf** para obener la información de la memoria RAM

Con las propiedades **totalram** y **freeram** se logran obtener el total de RAM y la memoria dispoible.
