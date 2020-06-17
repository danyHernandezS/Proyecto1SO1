import { BrowserModule } from '@angular/platform-browser';
import { NgModule, NO_ERRORS_SCHEMA } from '@angular/core';

import { AppComponent } from './app.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import { MaterialModule } from './material.module';

import { NgxChartsModule } from '@swimlane/ngx-charts';
import { GraficaCpuComponent } from './components/grafica-cpu/grafica-cpu.component';
import { GraficaRamComponent } from './components/grafica-ram/grafica-ram.component';
import { InicioComponent } from './components/inicio/inicio.component';
import { ProcesosComponent } from './components/procesos/procesos.component';

import { TreeModule } from 'angular-tree-component';
import { HttpClientModule } from '@angular/common/http';
import { DialogoComponent } from './components/dialogo/dialogo.component';

@NgModule({
  declarations: [
    AppComponent,
    GraficaCpuComponent,
    GraficaRamComponent,
    InicioComponent,
    ProcesosComponent,
    DialogoComponent
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    MaterialModule,
    NgxChartsModule,
    TreeModule.forRoot(),
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent],
  schemas: [NO_ERRORS_SCHEMA],
  entryComponents: [DialogoComponent]
})
export class AppModule { }
