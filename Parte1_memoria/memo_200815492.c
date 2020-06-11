#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define BUFSIZE 150

MODULE_AUTHOR("Dany Hernandez 200815492");
MODULE_DESCRIPTION("Mostrar informacion de memoria RAM.");
MODULE_LICENSE("GPL");

struct sysinfo meminf;

static int escribir_archivo(struct seq_file * archivo, void *v)
{
    si_meminfo(&meminf);
    long total_ram = (meminf.totalram *4);
    long free_mem  = (meminf.freeram *4);
    seq_printf(archivo, "*************************************************\n");
    seq_printf(archivo, "* ********************************************* *\n");
    seq_printf(archivo, "* * Sistemas Operativos 1                     * *\n");
    seq_printf(archivo, "* * Vacaciones 1er Semestre 2020              * *\n");
    seq_printf(archivo, "* * Dany Gabriel Hernandez Santos             * *\n");
    seq_printf(archivo, "* *                                           * *\n");
    seq_printf(archivo, "* *                                           * *\n");
    seq_printf(archivo, "* *        PROYECTO 1 MODULO MEMORIA RAM      * *\n");
    seq_printf(archivo, "* *                                           * *\n");
    seq_printf(archivo, "* ********************************************* *\n");
    seq_printf(archivo, "*************************************************\n");
    seq_printf(archivo, " Memoria Total  : \t %8lu KB - %8lu MB\n", total_ram, total_ram / 1024);
    seq_printf(archivo, " Memoria Libre  : \t %8lu KB - %8lu MB\n", free_mem, free_mem / 1024);
    seq_printf(archivo, " Memoria en uso : \t %i %%\n",(free_mem * 100)/total_ram);
    return 0;
}

static int al_abrir(struct inode *inode, struct file *file)
{
    return single_open(file, escribir_archivo, NULL);
}

/*
*calls file operations for open and read
*/
static struct file_operations procedures =
{
    .open = al_abrir,
    .read = seq_read
};


/*
 * Function called when loading the kernel module.
 * Prints my carnet id
 */
 int iniciar_modulo(void)
{
    proc_create("memo_200815492", 0, NULL, &procedures);
    printk(KERN_INFO "Carnet 200815492");
    return 0;
}

/*
 * Function called when unloading the kernel module.
 * Prints course name.
 */
 void salir_modulo(void)
{
    remove_proc_entry("memo_200815492", NULL);
    printk(KERN_INFO "Sistemas Operativos 1.\n");
}

module_init(iniciar_modulo);
module_exit(salir_modulo);
