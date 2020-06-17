import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { GraficaRamComponent } from './grafica-ram.component';

describe('GraficaRamComponent', () => {
  let component: GraficaRamComponent;
  let fixture: ComponentFixture<GraficaRamComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ GraficaRamComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(GraficaRamComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
