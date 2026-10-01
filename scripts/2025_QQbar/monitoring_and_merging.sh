#!/bin/bash
# monitor_and_merge.sh

echo "=== Monitoreando trabajos de HTCondor ==="

# Función para contar trabajos activos
count_jobs() {
    local job_count=$(condor_q $(whoami) 2>/dev/null | grep -c "$(whoami)")
    
    echo "$job_count"
}

# Esperar a que terminen todos los trabajos
echo "Esperando a que terminen todos los trabajos..."
while true; do
    job_count=$(count_jobs)
    if [ "$job_count" -eq 0 ]; then
        sleep 30  # Esperar por si acaso
    fi
    job_count2=$(count_jobs)
    if [ "$job_count2" -eq 0 ]; then
        sleep 10  # Esperar un poco más para asegurar que todos los trabajos han finalizado
        echo "✓ Todos los trabajos han terminado"
       break
    else
        echo "$(date): $job_count trabajos aún ejecutándose..."
        sleep 600  # Verificar cada 3600 segundos
    fi
done

# Esperar un poco más para asegurar transferencia de archivos
echo "Esperando transferencia de archivos..."
sleep 60

# EJECUTAR COMANDOS POST-PROCESAMIENTO
echo "=== Iniciando post-procesamiento ==="

# 1. Mover archivos
echo "Moviendo NTuples y limpiando carpeta..."
./move_samples.sh
