import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class ConnectionService {
  private port: string;
  private ip: string;

  constructor() { }

  setPort(Port: string){
    this.port = Port;
  }
  getPort(){
    return this.port;
  }
  setIP(IP: string){
    this.ip = IP;
  }
  getIP(){
    return this.ip;
  }

}
