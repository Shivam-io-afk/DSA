# Basic
# of 
# DSA




# General formula to calculate address of particular element by Row major order */

# Suppose We have matrix in m*n order so ( 'm' for row and 'n' for coloumn) -
``` a[i][j] = Base + ((i*n) + j) * size [ // which is '4' given in question or int has '4' bytes 'memory' ] ```

# if base index started from 1 so
``` a[i][j] = Base + (((i-1)*n) + j-1) * size [ // which is '4' given in question or int has '4' bytes 'memory'] ```



