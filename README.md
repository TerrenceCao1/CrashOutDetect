# Crash Out Detector (Seismometer)
### Intro 
This thing detects desk slams and plots them on the Richter Scale watch my video if you want!
### Accelerometers
I will use an accelerometer (the ADXL345)  to gather data on how much the stuff on my desk moves during a "crash-out". This device essentially tracks acceleration in 3 dimensions (x,y,z) and will send it back to the Arduino using i2c, which parses and processes the data using my ADXL345 library.

![ADXL345 Photo](https://imgs.search.brave.com/pfdjHP7BA4OfJhQRRepcQ20IkJfKMUj_Gy-8__wMJEc/rs:fit:860:0:0:0/g:ce/aHR0cHM6Ly93d3cu/ZWxlY3Ryb2tpdC5j/b20vcmVzb3VyY2Uv/dVNYSi84RmsvYWpS/NEdwQTdRTy9wcm9k/dWN0LzQxMDE2LzQx/MDE2MjM0LzQxMDE2/MjM0LmpwZw)
### LED "Crash-out" Visualizer
It's essentially a vertical array of LED's. In real time, the LED's will light up based on the intensity of the desk slam. Each LED indicates a level on the Mercalli Scale - going up from 3, 4, 5, 6, up to 10. I didn't include 1 or 2 because the accelerations are so miniscule that our accelerometer literally cannot distinguish between accelerataions at that scale. 

 

### Outro
This was an ultra fun project to get my feet wet in embedded so thank you for checking it out!
