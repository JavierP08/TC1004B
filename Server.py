from http.server import BaseHTTPRequestHandler, HTTPServer

class MyServer(BaseHTTPRequestHandler):
    def set_response(self):
        self.send_response(200)
        self.send_header("Content type", "text/html")
        self.end_headers()
    
    def do_GET(self):
        print("Hola desde el get")
        if "/sensor1_distancia" in self.path:
            sensor1_distancia = self.path.split("=")[1]
            print("La distancia es {}".format(sensor1_distancia))
            if "sensor2_humedadTemp" in self.path:
                sensor2_humedadTemp = self.path.split("=")[1]
                print("La humedad y la temperatura son {}".format(sensor2_humedadTemp))
                if "sensor3_nivelLuz" in self.path:
                    sensor3_nivelLuz = self.path.split("=")[1]
                    print("El porcentaje de nivel de luz es {}".format(sensor3_nivelLuz))        
        self.set_response()
        self.wfile.write("Hola este es mi super server. GET request for {}".format(self.path).encode("utf-8"))

port = 8080
server_address = ("",port)
httpd = HTTPServer(server_address, MyServer)
httpd.serve_forever()