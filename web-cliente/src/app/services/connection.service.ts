import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class ConnectionService {

  constructor(private http: HttpClient) { }

  cpu() {
    return this.http.get('http://localhost:10000/cpu');
  }

  memory() {
    return this.http.get('http://localhost:10000/memory', {
      responseType: 'text'
    });
  }

  procs() {
    return this.http.get('http://localhost:10000/procs', {
      responseType: 'text'
    });
  }

  kill(pid) {
    return this.http.get(`http://localhost:10000/kill/${pid}`, {
      responseType: 'text'
    });
  }

}
