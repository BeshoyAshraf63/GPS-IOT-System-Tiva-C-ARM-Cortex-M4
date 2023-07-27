# GPS Embedded Systems Project - Milestone 1

Till now the project can display any data on the 7-segment. It works in an asynchronous way.
Using Systick timer interrupt, We can put as much as delays as we want and still can multiplex between segments in parallel with the code. This is due to the fact the 4-digit 7 segment has only 7 pins for showing digits and 4 pins for enables which mean multiplexing is necessary to shuffle very fast between segments so they appear to be all on at the same time
This wasn't possible without interrupts because any delays in the code would delay the multiplexing

## Features

- Calculating the distance between any two points on Earth using haversine formula
- displaying the distance on the 7-segment dynamically without needing to call any functions due to using interrupts
- Delay function using Systick timer which is very accurate

## Milestone 1 Video Link - the video is in the google drive link

-[https://drive.google.com/drive/folders/1meHJXxR7G9u8Ix5Ae7IydJRoFLhzxYVj?usp=sharing](https://drive.google.com/drive/folders/1meHJXxR7G9u8Ix5Ae7IydJRoFLhzxYVj?usp=sharing)


## Actual distances used in the code from Google maps

The points in the code are hard coded and these are the points from google maps with the actual distance
![distance 1 = 70 m](https://drive.google.com/uc?export=view&id=1fX6pj1rbF3kSjeLXN-UF39tad5kuO_Ze) \
This distance = 70 m displayed as 71 m\
![distance 2 = 150 m](https://drive.google.com/uc?export=view&id=1SXyK8B0Fn1jJiQevjKttXPJ_zPpqPyif) \
This distance = 150 m displayed as 153 m

this small error is of course due to these points are selection of the points on google maps

# GPS Embedded Systems Project - Milestone 2

This project is not just an embedded systems project. It’s an IOT device (Internet Of Things). A GPS tracker system that measures the distance moved very accurately and can give an indication when reaching the destination point. Not only that, but it also send the data fetched from the GPS module to a live web server through esp8266 Wi-Fi module and POST requests and can be tracked through a website that communicate with the same server from anywhere on the Earth in real time.

## Technologies used in the website

- Front end  => HTML, Css, Js, Bootstrap, Ajax
- Back end   => nodejs, express

## Features
- Calculating the distance between any two points on Earth using haversine formula 
- displaying the distance on the 7-segment dynamically without needing to call any functions due to using interrupts
- Delay function using Systick timer which is very accurate 
- Distance can be calculated in non-straight line paths with a very high accuracy
- Sends the calculated distance and also the received data (including Latitude, Longitude, Real time, Date, Speed in m/s) to a live webserver that can be accessed from a website anywhere on the Earth. 
- Wi-Fi communications are done using Uart interrupt which run in the background in order not to delay the main code and functionality (Reading GPS data).
- Wi-Fi communications can handle the case if any error happened during connection (like if the server took too long to respond or the connection is poor) by trying again and again. 
- Distance can be calculated on the 7-segment display for up to 9999m (10km) and beyond that distance can still be calculated and sent to the website and the 7-segment will show 1 on the rightmost segment indicating overflow.  


## Milestone 2 Video Link - the video is in the google drive link

-[https://drive.google.com/drive/folders/16MSDlXN5nF6K6GrqkvRkKz80mx3kMstn?usp=sharing](https://drive.google.com/drive/folders/16MSDlXN5nF6K6GrqkvRkKz80mx3kMstn?usp=sharing)

## Website link

-[https://gps-embedded-project.herokuapp.com/](https://gps-embedded-project.herokuapp.com/)

## Website Github repo

-[https://github.com/kirollosashrafsedky/GPS-Project-website](https://github.com/kirollosashrafsedky/GPS-Project-website)

## Google maps distance test

![distance = 220 m](https://drive.google.com/uc?export=view&id=17CagpQ1zxV63AW_p7KCFMnB77a1L3Q7A)

## Circuit Schematic

![schematic](https://drive.google.com/uc?export=view&id=1lK2VsDdq5iyBMMCHbsX9TxOLgeESZa4i)


## Team members and IDs

كيرلس اشرف صدقي داود => 1807624
انجى فايق اديب => 1806935
مارك أمجد سليم => 1701082
سوسنة ميشيل فهيم وهبه => 1809355
بيشوى اشرف فهيم => 1805453
كيرلس سمير عزيز سدرة => 1807526
