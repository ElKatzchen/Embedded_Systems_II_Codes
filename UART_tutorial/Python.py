import time
import serial as sl

ser1 = sl.Serial("/dev/ttyACM0",19200)
ser2 = sl.Serial("/dev/ttyUSB0",9600)
ser1.reset_input_buffer()
ser2.reset_input_buffer()

while(True):
	try:
	#----------RECIEVE DATA FROM TIVA---------
		if ser1.in_waiting > 0:
			print("----------TIVA SAYS----------")
			recievetiva = ser1.readline().decode('utf-8').rstrip()
			print(recievetiva)

			#----------SEND DATA TO ESP32----------
			valuetiva = None
			if (recievetiva == "TURNING LED ON"):
				valuetiva = "ON"
			if (recievetiva == "TURNING LED OFF"):
				valuetiva = "OFF"
			ser2.write(bytearray(f"{valuetiva}\n",encoding='utf-8'))
		
		#----------RECIEVE DATA FROM ESP32----------
		if ser2.in_waiting > 0:
			print("----------ESP32 SAYS----------")
			recieveesp32 = ser2.readline().decode('utf-8').rstrip()
			print(recieveesp32)
			print("SWITCHING TIVA LEDS")

			#----------SEND DATA TO TIVA----------
			if (recieveesp32 == "LED TURNED ON"):
				valueesp32 = "PN"
			if (recieveesp32 == "LED TURNED OFF"):
				valueesp32 = "PF"
			ser1.write(bytearray(f"{valueesp32}\n",encoding='utf-8'))
			
		time.sleep(0.1)

	except Exception as e:
		print(e)