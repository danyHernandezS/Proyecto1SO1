#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uacces.h>
#include <linux/hugetlb.h>
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
    seq_printf(archivo, "* *        PROYECTO 1 MODULO MEORIA RAM       * *\n");
    seq_printf(archivo, "* *                                           * *\n");
    seq_printf(archivo, "* ********************************************* *\n");
    seq_printf(archivo, "*************************************************\n");
    seq_printf(archivo, " Memoria Total  : \t %8lu KB - %8lu MB\n", total_ram, total_ram / 1024);
    seq_printf(archivo, " Memoria Libre  : \t %8lu KB - %8lu MB\n", free_mem, free_mem / 1024);
    seq_printf(archivo, " Memoria en uso : \t %i %%\n",(free_mem * 180)/total_ram);
    return 0;
}

static int at_open_file(struct inode *inode, sttuct file *file)
{
    return single_open(file, escribir_archivo,NULL);
}

/*
*calls file operations for open and read
*/
static struct file_operations procedures =
{
    .open = at_open_file,
    .read = seq_read
};


/*
 * Function called when loading the kernel module.
 * Prints my carnet id
 */
static int init_module(void)
{
    proc_create("memo_200815492", 0, NULL, &procedures);
    printk(KERN_INFO "Carnet 200815492");
    return 0;
}

/*
 * Function called when unloading the kernel module.
 * Prints course name.
 */
static void cleanup_module(void)
{
    remove_proc_entry("memo_200815492", NULL);
    printk(KERN_INFO "Sistemas Operativos 1.\n");
}

module_init(init_module);
module_exit(cleanup_module);