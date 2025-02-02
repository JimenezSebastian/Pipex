#!/bin/bash

# ============================================================
# Script de prueba para el proyecto pipex (42).
# ============================================================
# Este script ejecuta algunos tests, comparando la salida de
# tu ./pipex con la salida de la shell "real" (bash).
#
# Si un test difiere, verás "DIFF ENCONTRADA" y se mostrará
# el diff exacto.
# Si no hay diffs, verás "OK".
# ============================================================

# 1. Comprobamos que existe el binario ./pipex
if [ ! -f ./pipex ]; then
  echo "[ERROR] No encuentro el ejecutable ./pipex. Compílalo antes de correr este script."
  exit 1
fi

# 2. Preparamos archivos de prueba
echo "Preparando archivos de prueba..."

# - infile con algo de texto (si no existe)
if [ ! -f infile ]; then
  echo "Linea 1: Hola 42"       > infile
  echo "Linea 2: Este es un test" >> infile
  echo "Linea 3: 42 es la respuesta" >> infile
  echo "Linea 4: Fin de fichero" >> infile
fi

# - Archivo sin permisos de lectura
touch perm_in
chmod 000 perm_in 2>/dev/null

# - Archivo sin permisos de escritura
touch perm_out
chmod 444 perm_out 2>/dev/null

# - Limpieza previa de resultados antiguos
rm -f outfile_pipex outfile_shell
rm -f *.diff 2>/dev/null

# 3. Función auxiliar para testear
# Paráme:
#   $1 -> nombre del test (texto)
#   $2 -> comando completo a ejecutar con pipex (sin ./pipex delante)
#   $3 -> comando shell "equivalente"
#
# Ejemplo de uso:
#  test_cmd "ls -l -> wc -l" \
#           'infile "ls -l" "wc -l" outfile_pipex' \
#           '< infile ls -l | wc -l > outfile_shell'
test_cmd() {
  local test_name="$1"
  local pipex_cmd="$2"
  local shell_cmd="$3"

  echo "-----------------------------------"
  echo "Test: $test_name"

  # 1) Ejecutamos PIPEX
  echo "[PIPEX]: ./pipex $pipex_cmd"
  eval "./pipex $pipex_cmd" 2>/dev/null

  # 2) Ejecutamos shell nativa
  echo "[SHELL]: $shell_cmd"
  eval "$shell_cmd" 2>/dev/null

  # 3) Obtener los nombres de los archivos de salida
  #    - Asumimos que, para pipex, el último token del comando es el outfile
  #    - Igual para el shell_cmd
  local outfile_pipex=$(echo "$pipex_cmd" | awk '{print $NF}')    # último token => outfile_pipex
  local outfile_shell=$(echo "$shell_cmd" | awk '{print $NF}')    # último token => outfile_shell

  # 4) Comparar con diff
  if [ -f "$outfile_pipex" ] && [ -f "$outfile_shell" ]; then
    diff -q "$outfile_pipex" "$outfile_shell" > /dev/null
    if [ $? -eq 0 ]; then
      echo "Resultado: OK"
    else
      echo "Resultado: DIFF ENCONTRADA"
      echo "====== DIFERENCIAS (pipex vs shell) ======"
      diff "$outfile_pipex" "$outfile_shell"
      echo "========================================="
    fi
  else
    echo "[ERROR] Alguno de los archivos de salida no existe ($outfile_pipex o $outfile_shell)."
    echo "       Probablemente la ejecución falló."
  fi
}

# 4. Llamamos test_cmd para cada caso
# -----------------------------------------------------------

# a) Ejemplo sencillo: ls -l | wc -l
test_cmd "ls -l -> wc -l" \
  'infile "ls -l" "wc -l" outfile_pipex' \
  '< infile ls -l | wc -l > outfile_shell'

# b) cat -e | cat -e
test_cmd "cat -e -> cat -e" \
  'infile "cat -e" "cat -e" outfile_pipex' \
  '< infile cat -e | cat -e > outfile_shell'

# c) grep 42 | wc -l
test_cmd "grep 42 -> wc -l" \
  'infile "grep 42" "wc -l" outfile_pipex' \
  '< infile grep 42 | wc -l > outfile_shell'

# d) Comando inexistente
test_cmd "Comando inexistente -> wc -l" \
  'infile "comandoInexistente" "wc -l" outfile_pipex' \
  '< infile comandoInexistente 2>/dev/null | wc -l > outfile_shell'

# e) Archivo de entrada que no existe
test_cmd "No existe infileX -> ls -l | wc -l" \
  'infileX "ls -l" "wc -l" outfile_pipex' \
  '< infileX ls -l | wc -l > outfile_shell'

# f) head -n 5 -> sort
test_cmd "head -n 5 -> sort" \
  'infile "head -n 5" "sort" outfile_pipex' \
  '< infile head -n 5 | sort > outfile_shell'

# g) BONUS (3 o más comandos) - Ejemplo
#   Ajusta si tu bonus maneja sintaxis distinta.
test_cmd "BONUS: ls -l -> grep 42 -> wc -l" \
  'infile "ls -l" "grep 42" "wc -l" outfile_pipex' \
  '< infile ls -l | grep 42 | wc -l > outfile_shell'

echo "-----------------------------------"
echo "FIN de los tests."
