import { Component, OnInit, Inject } from '@angular/core';
import { DatoDialogo } from '../procesos/procesos.component';
import { MAT_DIALOG_DATA } from '@angular/material/dialog';

@Component({
  selector: 'app-dialogo',
  templateUrl: './dialogo.component.html',
  styleUrls: ['./dialogo.component.scss']
})
export class DialogoComponent implements OnInit {

  nodes = [];

  constructor(
    @Inject(MAT_DIALOG_DATA) public data: DatoDialogo
  ) {
    const children = [];
    for (let i = 0; i < data.procesos.length; i++) {
      children.push({
        id: i,
        name: `${data.procesos[i].pid} - ${data.procesos[i].nombre}`,
        children: []
      })
    }
    this.nodes.push({
      id: data.procesos.length,
      name: `${data.proceso.pid} - ${data.proceso.nombre}`,
      children
    })
  }

  ngOnInit(): void {
  }

}
