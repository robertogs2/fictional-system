import { Component, OnInit } from '@angular/core';
import {HttpClient} from '@angular/common/http';
import { FormBuilder, FormGroup } from '@angular/forms';
import { ConnectionService } from '../home/connection.service';
import {Router} from '@angular/router';


@Component({
  selector: 'app-tasks',
  templateUrl: './tasks.page.html',
  styleUrls: ['./tasks.page.scss']
})
export class TasksPage implements OnInit {
  SERVER_URL = 'http://' + this.connectionService.getIP() + ':' + this.connectionService.getPort() + '/filepost';
  uploadForm: FormGroup;
  statusCode: number;


  constructor(
    public http: HttpClient,
    private formBuilder: FormBuilder,
    private connectionService: ConnectionService,
    private router: Router) { }

  ngOnInit() {
    this.uploadForm = this.formBuilder.group({
      profile: ['']
    });
  }

  onFileSelect(event) {
    if (event.target.files.length > 0) {
      const file = event.target.files[0];
      this.uploadForm.get('profile').setValue(file);
    }
  }
  onSubmit() {
    console.log(this.SERVER_URL);
    const formData = new FormData();
    formData.append('file', this.uploadForm.get('profile').value);

    this.http.post<any>(this.SERVER_URL, formData).subscribe(
      (res) => console.log(res),
      (err) => console.log(err));
    this.router.navigate(['/success']);
  }

}
