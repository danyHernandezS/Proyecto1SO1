# Proyecto1SO1
## Proyecto 1 sistemas operativos 1 vacaciones 2020

**Para genera los archivos de carga del modulo correr el comando:**

make all

**Realizar la carga del modulo con el comando:**

sudo insmod cpu_200815492.ko

**Verificar la escritura del archivo ubicado en:**

/proc/cpu_200815492_201314761


**Realizar la descarga del modulo con el comando**

sudo rmmod memo_200815492

**Verificar que en listado de modulos se encuentra el nuestro con el comando**

lsmod

**Consultar mensajes de los modulos**

dmesg

Para obtener el listado de procesos se utilizó el struct **task_struct**
Para obener los atributos pid, nombre y los hijos
