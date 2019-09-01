#ifndef webchars_h
#define webchars_h

const char * htmlHeader = "";


const char askpage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                            <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                            <title> Fictional Systems </title> \n\
                            <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                            <h1 style=\"text-align:center; color:white\">Upload a file, please!</h1>  \n\
                            <div align=\"center\" style=\"text-align:center; color:white\"><br><br><br> \n\
                            <form action=\"/filepost\" method=\"post\" enctype=\"multipart/form-data\"> \n\
                            <input name=\"file\" type=\"file\" color=\"#006666\"> \n\
                            <input type=\"submit\" value=\" Send \"></form></div><br><br><br>  \n\
                            <img src=\"https://svgsilh.com/svg/1294806-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\">  \n\
                            <br><br><br><p style=\"text-align:center; color:white\"> There are %u clients uploading at the moment.</p>  \n\
                            </body></html>";

const char busypage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                            <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                            <title> Fictional Systems </title> \n\
                            <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                            <h1 style=\"text-align:center; color:white\">This server is busy, please try again later.</h1> \n\
                            <br><br><br><img src=\"https://svgsilh.com/svg/151342-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                            <br><br><br><p style=\"text-align:center; color:white\"> More information about the error </p> \n\
                            </body></html>";

const char completepage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">The upload has been completed.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/459230-ff9800.svg\" style=\"width:300px;height:400px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> Go back to send more files </p> \n\
                                </body></html>"; 

const char errorpage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">This doesn't seem to be right.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/2061132-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> More information about the error </p> \n\
                                </body></html>"; 

const char servererrorpage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">Invalid request.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/146613-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> More information about the error </p> \n\
                                </body></html>"; 

const char fileexistspage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">This file already exists.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/309065-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> More information about the error </p> \n\
                                </body></html>"; 

const char fileioerror_html[] =  "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">IO error writing to disk.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/2061132-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> More information about the error </p> \n\
                                </body></html>"; 

const char const postprocerror_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">Error processing POST data.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/297169-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> More information about the error </p> \n\
                                </body></html>"; 


#endif