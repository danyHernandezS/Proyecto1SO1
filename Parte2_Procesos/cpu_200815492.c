#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/sched/signal.h>

#define BUFSIZE 150

MODULE_AUTHOR("Dany Hernandez 200815492");
MODULE_DESCRIPTION("Mostrar informacion de Procesos.");
MODULE_LICENSE("GPL");

static int escribir_archivo(struct seq_file * archivo, void *v)
{
    
    seq_printf(archivo, "*****************************************************************************************************************\n");
    seq_printf(archivo, "* ************************************************************************************************************* *\n");
    seq_printf(archivo, "* *                                           Sistemas Operativos 1                                           * *\n");
    seq_printf(archivo, "* *                                       Vacaciones 1er Semestre 2020                                        * *\n");
    seq_printf(archivo, "* *                               Dany Gabriel Hernandez Santos      200815492                                * *\n");
    seq_printf(archivo, "* *                               Jorge David Lopez Yool             201314761                                * *\n");
    seq_printf(archivo, "* *                                                                                                           * *\n");
    seq_printf(archivo, "* *                                     PROYECTO 1 MODULO LISTADO PROCESOS                                    * *\n");
    seq_printf(archivo, "* *                                                                                                           * *\n");
    seq_printf(archivo, "* ************************************************************************************************************* *\n");
    seq_printf(archivo, "*****************************************************************************************************************\n");
        
    struct task_struct *task;
	struct task_struct *childtask;
	struct list_head *list;

    seq_printf(archivo, "Nombre\t\t\tPID\t\t\tUsuario\t\t\t\tESTADO\t\t\tPID_PADRE\n");
    seq_printf(archivo, "-----------------------------------------------------------------------------------------------------------------\n");
    for_each_process(task){
        if(strlen(task->comm)< 8){
             seq_printf(archivo, "%s\t\t\t",task->comm);
        }
        if((strlen(task->comm)> 7) && (strlen(task->comm)< 16)){
             seq_printf(archivo, "%s\t\t",task->comm);
        }
        if(strlen(task->comm)> 15){
             seq_printf(archivo, "%s\t",task->comm);
        }
        seq_printf(archivo, "%d\t\t\t", task->pid);
        seq_printf(archivo, "%d\t\t\t", task->cred);
        
        if(task->state == 0) {
            seq_printf(archivo,"Ejecucion\n");
        }
        if(task->state == 1){
            seq_printf(archivo,"Dormido\n");
        }
        if(task->state == 2){
            seq_printf(archivo,"Listo\n");
        }
        if(task->state == 4){
            seq_printf(archivo,"Zombie\n");
        }
        if(task->state == 8){
            seq_printf(archivo,"Detenido\n");
        }
        if(task->state == 32){
            seq_printf(archivo,"Espera Exclusiva\n");
        } 
        if(task->state == 260){
            seq_printf(archivo,"Detenido\n");
        }
        if(task->state == 1026)  {
            seq_printf(archivo,"idle\n");
        }
        if(&task->children>0){
            
            list_for_each(list, &task->children){
                childtask = list_entry(list, struct task_struct, sibling); 
                if(strlen(childtask->comm)< 8){
                    seq_printf(archivo, "%s\t\t\t",childtask->comm);
                }
                if((strlen(childtask->comm)> 7) && (strlen(childtask->comm)< 16)){
                    seq_printf(archivo, "%s\t\t",childtask->comm);
                }
                if(strlen(childtask->comm)> 15){
                    seq_printf(archivo, "%s\t",childtask->comm);
                }
                seq_printf(archivo, "%d\t\t\t", childtask->pid);
                seq_printf(archivo, "%d\t\t\t", childtask->cred);
                
                if(childtask->state == 0) {
                    seq_printf(archivo,"Ejecucion\t\t");
                }
                if(childtask->state == 1){
                    seq_printf(archivo,"Dormido\t\t\t");
                }
                if(childtask->state == 2){
                    seq_printf(archivo,"Listo\t\t\t");
                }
                if(childtask->state == 4){
                    seq_printf(archivo,"Zombie\t\t\t");
                }
                if(childtask->state == 8){
                    seq_printf(archivo,"Detenido\t\t\t");
                }
                if(childtask->state == 32){
                    seq_printf(archivo,"Espera Exclusiva\t\t\t");
                } 
                if(childtask->state == 260){
                    seq_printf(archivo,"Detenido\t\t\t");
                }
                if(childtask->state == 1026)  {
                    seq_printf(archivo,"idle\t\t\t");
                }

                seq_printf(archivo, "%d\n", task->pid);

            }
            
        }
    }    
	
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
 * Prints carnets id
 */
 int iniciar_modulo(void)
{
    proc_create("cpu_200815492_201314761", 0, NULL, &procedures);
    printk(KERN_INFO "Carnets: 200815492 201314761");
    return 0;
}

/*
 * Function called when unloading the kernel module.
 * Prints course name.
 */
 void salir_modulo(void)
{
    remove_proc_entry("cpu_200815492_201314761", NULL);
    printk(KERN_INFO "Sistemas Operativos 1.\n");
}

module_init(iniciar_modulo);
module_exit(salir_modulo);
