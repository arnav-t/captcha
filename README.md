# captcha
## Testing weaknesses in Captchas
### "Unwarping"
Warped captchas can be simply "unwarped" by removing the curvature of lines about both the axes. 
![original](https://i.imgur.com/rIUNcti.jpg "Orignal Captcha")
![unwarped](https://i.imgur.com/6DYqqr5.jpg "Unwarped Captcha")

### Grid Removal 
Grid lines (which are now nearly horizontal/vertical) can be removed in a similar fashion by following them from the end to end. Since a grid line can be thicker than one pixel, a maximum thickness has to be defined in order to remove thicker lines while preserving the lettering.                                     
![original](https://i.imgur.com/TPkwjH2.jpg "With Grid")
![ungrid](https://i.imgur.com/w9ki7rU.jpg "Without Grid (Work in Progress)")
