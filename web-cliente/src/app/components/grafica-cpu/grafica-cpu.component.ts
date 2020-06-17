import { Component, OnInit } from '@angular/core';
import { ConnectionService } from 'src/app/services/connection.service';

@Component({
  selector: 'app-grafica-cpu',
  templateUrl: './grafica-cpu.component.html',
  styleUrls: ['./grafica-cpu.component.scss']
})
export class GraficaCpuComponent implements OnInit {

  usado: number;
  multi = [];
  view = [600, 300];
  constructor(private connection: ConnectionService) {
    this.usado = 0;
    this.multi.push({
      name: "Porcentaje", series: []
    });
  }

  ngOnInit(): void {
    setInterval(() => {
      this.connection.cpu().subscribe((dato: number) => {
        const valor = Math.round(dato);
        this.usado = valor;
        const arr = [...this.multi];
        this.multi = [];
        const h = new Date();
        if (arr[0].series.length === 20) {
          arr[0].series.shift();
        }
        arr[0].series.push({
          "name": `${h.getHours()}:${h.getMinutes()}:${h.getSeconds()}`,
          "value": valor
        });
        this.multi = arr;
      });
    }, 1000);
  }

}
