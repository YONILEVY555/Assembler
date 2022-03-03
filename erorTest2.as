 mov r1,r2
 d1: .data 9,,9
 d2: .data 9,,
 d3: .data 9,9,,
 d4: .data ,,9
 d5: .data ,9,
 d6: .data --9
 d7: .data 9++
 d7: .data t*t
 ex1: .extern 9,,  9
 ex2: .extern 9,,
 ex3: .extern 9,9,,
 ex4: .extern ,,9
 ex5: .extern ,9,
 mov r1,r2
 ex6: .extern --9
 ex7: .extern 9++
 ex7: .extern 9,--9,8
 en1: .entry 9,,9
 en2: .entry 9,,
 en3: .entry 9,9,,
 en4: .entry ,,9
 en5: .entry ,9,
 en6: .entry --9
 en7: .entry 9++
 .entry 9++
 .extern 9++
 .data --9
x: .data
y: .extern
z: .entry
t: .string
.data 
.extern
.entry
.string
