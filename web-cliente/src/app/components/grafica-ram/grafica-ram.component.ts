import { Component, OnInit } from '@angular/core';
import { ConnectionService } from 'src/app/services/connection.service';

@Component({
  selector: 'app-grafica-ram',
  templateUrl: './grafica-ram.component.html',
  styleUrls: ['./grafica-ram.component.scss']
})
export class GraficaRamComponent implements OnInit {

  usado: number;
  total: number;
  consumido: number;
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
      this.connection.memory().subscribe((dato) => {
        const vals = dato.split('\n');
        const memtotal = parseInt(vals[0].replace(' kB', '').replace('MemTotal:', '').trim());
        const active = parseInt(vals[1].replace(' kB', '').replace('Active:', '').trim());

        this.total = memtotal;
        this.consumido = active;
        this.usado = Math.round((active / memtotal) * 100);

        const arr = [...this.multi];
        this.multi = [];
        const h = new Date();
        if (arr[0].series.length === 20) {
          arr[0].series.shift();
        }
        arr[0].series.push({
          "name": `${h.getHours()}:${h.getMinutes()}:${h.getSeconds()}`,
          "value": this.usado
        });
        this.multi = arr;
      });
    }, 1000);
  }

}
