# Breaking Captchas
## Principle
### "Unwarping"
Warped captchas can be simply "unwarped" by removing the curvature of lines about both the axes. 
![original](https://i.imgur.com/rIUNcti.jpg "Orignal Captcha")
![unwarped](https://i.imgur.com/6DYqqr5.jpg "Unwarped Captcha")

### Grid Removal 
Grid lines (which are now nearly horizontal/vertical) can be removed in a similar fashion by following them from the end to end. Since a grid line can be thicker than one pixel, a maximum thickness has to be defined in order to remove thicker lines while preserving the lettering.      
The remaining noise is removed by thresholding contours by a minimum area.       
![original](https://i.imgur.com/TPkwjH2.jpg "With Grid")
![ungrid](https://i.imgur.com/H6ArbaU.jpg "Without Grid")

## Operation
![operation](https://i.imgur.com/09Lkx6s.png "Operation")
1. Python script is executed, and the image file name is passed as a command line argument.
2. The script calls the C++ program and passes the file name also as a command line argument.
3. The C++ program does bulk of the work and seperates the text, saving it as another image (result.jpeg). 
4. This image is then processed with the pytesseract OCR library to obtain the text.   

## Dependencies 
* OpenCV (C++), 2.4+
* pytesseract (Python)


