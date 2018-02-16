spin_bash() {
   local -a marks=( '/' '-' '\' '|' )
   while [[ 1 ]]; do
     printf '%s\r' "${marks[i++ % ${#marks[@]}]}"
     sleep 1
   done
 }

spin_without_printf() {
    local -a marks=( '/' '-' '\' '|' );
    while [[ 1 ]]; do
      echo -ne "${marks[i++ % ${#marks[@]}]}";
      sleep 1;
      echo -ne "\b";
    done;  
}

spin_sh() {
  i=0
  marks='/ - \ |'
  while true; do
    if [ $# -lt 4 ]; then
      set -- "$@" $marks
    fi
    shift $(( (i+1) % $# ))
    printf '%s\r' "$1"
    sleep 1
  done
}

while true; do
    spin_bash
done
