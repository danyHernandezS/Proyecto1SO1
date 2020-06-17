import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { GraficaCpuComponent } from './grafica-cpu.component';

describe('GraficaCpuComponent', () => {
  let component: GraficaCpuComponent;
  let fixture: ComponentFixture<GraficaCpuComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ GraficaCpuComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(GraficaCpuComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
