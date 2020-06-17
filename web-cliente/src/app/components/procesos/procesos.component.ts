import { Component, OnInit, ViewChild, Inject } from '@angular/core';
import { MatSort } from '@angular/material/sort';
import { MatTableDataSource } from '@angular/material/table';
import { MatPaginator } from '@angular/material/paginator';
import { ConnectionService } from 'src/app/services/connection.service';
import { MatDialog } from '@angular/material/dialog';
import { DialogoComponent } from '../dialogo/dialogo.component';

@Component({
  selector: 'app-procesos',
  templateUrl: './procesos.component.html',
  styleUrls: ['./procesos.component.scss']
})
export class ProcesosComponent implements OnInit {

  ejecucion: number = 0;
  suspendido: number = 0;
  detenido: number = 0;
  zombie: number = 0;
  total: number = 0;
  displayedColumns = ['pid', 'nombre', 'usuario', 'estado', 'ram', 'matar', 'detalle'];
  dataSource = new MatTableDataSource([]);
  @ViewChild(MatSort, { static: true }) sort: MatSort;
  @ViewChild(MatPaginator, { static: true }) paginator: MatPaginator;

  constructor(private connection: ConnectionService, public dialog: MatDialog) {
  }

  async ngOnInit() {
    this.dataSource.sort = this.sort;
    this.dataSource.paginator = this.paginator;
    setInterval(async () => {
      this.connection.procs().subscribe(async (data) => {
        const arr = data.split('\n');
        arr.shift()
        arr.pop()
        const datos = [];
        this.total = arr.length;
        this.ejecucion = 0;
        this.suspendido = 0;
        this.detenido = 0;
        this.zombie = 0;
        for (let i = 0; i < arr.length; i++) {
          const arr2 = await arr[i].trim().split(" ").filter(x => x !== "");
          const pid = arr2[0];
          const nombre = arr2[1];
          const usuario = arr2[2];
          const state = arr2[3];
          const estado = this.formatearEstado(state);
          const ram = arr2[4];
          const ppid = arr2[5];
          datos.push({
            ppid,
            pid,
            nombre,
            usuario,
            estado,
            ram,
            matar: false,
            detalle: false
          });
        }
        this.dataSource.data = datos;
      });
    }, 1000);
  }

  formatearEstado(state): string {
    if (state === 'R') {
      this.ejecucion++;
      return 'Ejecucion';
    } else if (state === 'T') {
      this.detenido++;
      return 'Detenido';
    } else if (state === 'Z') {
      this.zombie++;
      return 'Zombie';
    } else {
      this.detenido++;
      return 'Detenido';
    }
  }

  detalle(proceso: Proceso) {
    const generada = [];
    for (let i = 0; i < this.dataSource.data.length; i++) {
      const dato = this.dataSource.data[i];
      if (dato.ppid === proceso.pid) {
        generada.push(dato);
      }
    }
    this.dialog.open(DialogoComponent, {
      width: '500px',
      height: '500px',
      data: { proceso, procesos: generada }
    });
  }

  matar(proceso: Proceso) {
    this.connection.kill(proceso.pid).subscribe((data) => { });
  }

  applyFilter(event: Event) {
    const filterValue = (event.target as HTMLInputElement).value;
    this.dataSource.filter = filterValue.trim().toLowerCase();
  }

}

export interface Proceso {
  ppid: string;
  pid: string;
  nombre: string;
  usuario: string;
  estado: string;
  ram: string;
  matar: boolean;
  detalle: boolean;
}

export interface DatoDialogo {
  proceso: Proceso;
  procesos: Proceso[];
}
