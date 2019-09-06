/**
  This header defines webpages that the server sends as an answer to the
clients requests.

  All webpages were designed in HTML without extra libraries and modified to be
processable by C (printing with printf generates valid HTML code).

  All images used in these HTMLs are from SVG Silh and released under Creative Commons
*/

#ifndef _WEBCHARS_H
#define _WEBCHARS_H

    /* Asks the page for the file to send */
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

    /* The server is unavailable */
const char busypage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                            <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                            <title> Fictional Systems </title> \n\
                            <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                            <h1 style=\"text-align:center; color:white\">This server is busy, please try again later.</h1> \n\
                            <br><br><br><img src=\"https://svgsilh.com/svg/151342-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                            <br><br><br><p style=\"text-align:center; color:white\"> Too many clients are sending data at this point in time </p> \n\
                            </body></html>";

    /* File transfer has completed satisfactorily */
const char completepage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">The upload has been completed.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/459230-ff9800.svg\" style=\"width:300px;height:400px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> Go back to send more files </p> \n\
                                </body></html>";

    /* Unkown error page */
const char errorpage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">This doesn't seem to be right.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/2061132-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> More information about the error </p> \n\
                                </body></html>";

    /* Invalid request error page */
const char servererrorpage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">Invalid request.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/146613-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> The action you are trying to execute is not possible in this server </p> \n\
                                </body></html>";

    /* The file the client is attempting to send already exists */
const char fileexistspage_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">This file already exists.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/309065-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> The file has already been sent to this server </p> \n\
                                </body></html>";

    /* The file cannot be read or cannot be written to the specified folder */
const char fileioerror_html[] =  "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">IO error writing to disk.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/2061132-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> The file cannot be read or cannot be written to the specified folder </p> \n\
                                </body></html>";

    /* File couldn't be properly processed by the POST functions */
const char const postprocerror_html[] = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n\
                                <style>img {display: block; margin-left: auto; margin-right: auto; } </style> </head> \n\
                                <title> Fictional Systems </title> \n\
                                <body style=\"background-color:#006666;\"> <br><br><br><br><br><br> \n\
                                <h1 style=\"text-align:center; color:white\">Error processing POST data.</h1> \n\
                                <br><br><br><img src=\"https://svgsilh.com/svg/297169-ff9800.svg\" style=\"width:200px;height:200px;\" class=\"center\"> \n\
                                <br><br><br><p style=\"text-align:center; color:white\"> File couldn't be properly processed by the POST </p> \n\
                                </body></html>";


#endif
