# Basics of DSA



---
## General formula to calculate address of particular element in Row major order 

### Suppose We have matrix in m*n order so ( 'm' for row and 'n' for coloumn) -
``` a[i][j] = Base + ((i*n) + j) * size [ // which is '4' given in question or int has '4' bytes of 'memory' ] ```

### if base index started from 1 so
``` a[i][j] = Base + (((i-1) * n) + j-1) * size [ // which is '4' given in question or int has '4' bytes of 'memory'] ```

---
## General formula to calculate address of particular element in column major order

### Suppose We have matrix in m*n order so ( 'm' for row and 'n' for coloumn) -
```a[i][j] = B + ((j*m) + i) * size ```

### if base index started form 1. then,
```a[i][j] = B + (((j-1) * m) + i-1) * size ```