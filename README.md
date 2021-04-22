# CDIoT
Repo para el PFA de PHR. Un sistema de control domótico con una FPGA y un ESP32

# Materiales
 · [Basys 3 Artix-7](https://www.xilinx.com/products/boards-and-kits/1-54wqge.html)

 · [ESP32](https://www.espressif.com/en/products/socs/esp32) 

 · [VEML7700](https://www.vishay.com/docs/84286/veml7700.pdf)

 · [HC-SR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
 
 · [SHT21](http://www.farnell.com/datasheets/1780639.pdf)


# Esquema
La FPGA se va a encargar de recoger los datos de los sensores y mandar
órdenes a los actuadores, que en nuestro caso estarán representados por 
LEDs.
La ESP32 la utilizaremos para actuar como intermediario entre la FPGA y el
usuario (para conectarse a Thingsboard o a la API de Telegram)
