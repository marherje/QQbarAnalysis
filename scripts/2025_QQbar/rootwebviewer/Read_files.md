####### First, copy locally whatever file you want to see #######
####### We need to download and decompress the visualizer #######
wget https://github.com/root-project/jsroot/archive/refs/tags/7.9.1.tar.gz -O JSRoot.791.tar.gz 
tar -xzf JSRoot.791.tar.gz

####### Open a server #######
python3 -m http.server 8080

####### Then use the interface in the web browser #######
####### Go to: "http://localhost:8080/jsroot-7.9.1/" #######