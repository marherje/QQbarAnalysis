####### First, copy locally whatever file you want to see #######
####### We need to decompress the file: #######
tar -xzf JsRoot791.tar.gz 

####### Open a server #######
python3 -m http.server 8080

####### Then use the interface in the web browser #######
####### If it doesn't open automatically, it's in "http://localhost:8080/" #######