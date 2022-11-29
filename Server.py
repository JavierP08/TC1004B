from http.server import BaseHTTPRequestHandler, HTTPServer
import firebase_admin
from firebase_admin import firestore
from firebase_admin import credentials
import time
from datetime import datetime

cred = credentials.Certificate('serviceAccount.json')
app = firebase_admin.initialize_app(cred)
db = firestore.client()

class MyServer(BaseHTTPRequestHandler):
    def set_response(self):
        self.send_response(200)
        self.send_header("Content type", "text/html")
        self.end_headers()
    
    def do_GET(self):
        print("Hola desde el get")

#----------------- Sensor 1 -------------------------------
        if "sensor1_distancia" in self.path:
            sensor1_distancia = self.path.split("=")[1]
            print("La distancia es {}".format(sensor1_distancia))
            print("Sending data")
            current_date = datetime.now()
            date = current_date.strftime('%Y-%m-%d')
            hour = current_date.strftime('%H')
            collectionName = u'sensor_1_{0}'.format(date)

            hour_ref = db.collection(collectionName).document(hour)
            hour_doc = hour_ref.get()
            hour_data = hour_doc.to_dict()

            hour_ref.set({
                u'Distancia': sensor1_distancia
            })
                    

#---------------- Sensor 2 -------------------------------
        elif "sensor2_humedadTemp" in self.path:
            sensor2_humedadTemp = self.path.split("=")[1]
            Valores = sensor2_humedadTemp.split(";")
            print(Valores)
            print("La humedad y la temperatura son {}".format(sensor2_humedadTemp))
            print("Sending data")
            current_date = datetime.now()
            date = current_date.strftime('%Y-%m-%d')
            hour = current_date.strftime('%H')
            collectionName = u'sensor_2_{0}'.format(date)

            hour_ref = db.collection(collectionName).document(hour)
            hour_doc = hour_ref.get()
            hour_data = hour_doc.to_dict()

            hour_ref.set({
                u'Humedad y Temperatura': sensor2_humedadTemp
            })
            

#--------------- Sensor 3 --------------------------------
        elif "sensor3_nivelLuz" in self.path:
            sensor3_nivelLuz = self.path.split("=")[1]
            print("El porcentaje de nivel de luz es {}".format(sensor3_nivelLuz))
            print("Sending data")

            current_date = datetime.now()
            date = current_date.strftime('%Y-%m-%d')
            hour = current_date.strftime('%H')
            collectionName = u'sensor_3_{0}'.format(date)

            hour_ref = db.collection(collectionName).document(hour)
            hour_doc = hour_ref.get()
            hour_data = hour_doc.to_dict()

            hour_ref.set({
                u'% Luz': sensor3_nivelLuz
            })

            


        self.set_response()
        self.wfile.write("Hola este es mi super server. GET request for {}".format(self.path).encode("utf-8"))

port = 8080
server_address = ("",port)
httpd = HTTPServer(server_address, MyServer)
httpd.serve_forever()