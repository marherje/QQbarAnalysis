#!/bin/bash

# Uso: ./comentar_lineas.sh archivo.txt 10 20
# Comentará de la línea 10 a la 20 (inclusive)

archivo="$1"
inicio="$2"
fin="$3"

sed -i "${inicio},${fin} s/^/#/" "$archivo"
