#!/bin/bash

# Uso: ./descomentar_lineas.sh archivo.txt 10 20
# Quita el # del principio de las líneas 10 a 20 (si lo tienen)

archivo="$1"
inicio="$2"
fin="$3"

sed -i "${inicio},${fin} s/^#//" "$archivo"
